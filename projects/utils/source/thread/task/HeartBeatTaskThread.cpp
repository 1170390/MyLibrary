
#include "HeartBeatTaskThread.h"

/** ���������һ���װ
*/
struct HeartBeatTaskWraper
{
    /** ���캯��
    @param [in] spHeartBeatTask ������������û�Ӧ�ñ�֤��Ϊ�գ����ļ��ڲ�����ȥ�жϿ�
    */
    HeartBeatTaskWraper(const SPHeartBeatTask& spHeartBeatTask) :
        m_spHeartBeatTask(spHeartBeatTask)
    {
        auto dur = std::chrono::high_resolution_clock::now().time_since_epoch();
        m_preExecuteTime = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    }

    /** �Ƿ����ִ���ˣ�����trueʱ������ʱ���
    @return �Ƿ����ִ��
    */
    bool CanExecute()
    {
        auto dur = std::chrono::high_resolution_clock::now().time_since_epoch();
        long long nowTime = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

        if (nowTime - m_preExecuteTime >= m_spHeartBeatTask->GetTimeOut())
        {
            m_preExecuteTime = nowTime;
            return true;
        }

        return false;
    }

    /** ���������ָ��
    */
    SPHeartBeatTask m_spHeartBeatTask;

    /** �ϴ�ִ��ʱ�䣬���һ�ζ�û��ִ�й�Ϊ����ʱ��
    */
    long long m_preExecuteTime;
};

//////////////////////////////////////////////////////////////////////////

HeartBeatTaskThread::HeartBeatTaskThread():
    m_pThread(nullptr),
    m_stop(false)
{
}

HeartBeatTaskThread::~HeartBeatTaskThread()
{
    if (m_pThread != nullptr)
    {
        StopAll();
        m_pThread->join();
        delete m_pThread;
        m_pThread = nullptr;
    }
}

bool HeartBeatTaskThread::Start()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (m_pThread != nullptr)
    {
        return true;
    }

    m_pThread = new (std::nothrow) std::thread(&HeartBeatTaskThread::ThreadCallBack, this);
    return (m_pThread != nullptr);
}

void HeartBeatTaskThread::StopAll()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (!m_stop)
    {
        ClearAll();
        m_stop = true;
    }
}

void HeartBeatTaskThread::StopCurrent()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (m_currentTask != nullptr)
    {
        m_currentTask->m_spHeartBeatTask->Stop();
    }
}

void HeartBeatTaskThread::ClearAll()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    StopCurrent();
    ClearQueue();
}

void HeartBeatTaskThread::ClearQueue()
{
    std::list<SPHeartBeatTaskWraper > tmp = std::list<SPHeartBeatTaskWraper >();

    {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);
        m_taskList.swap(tmp);
    }
}

void HeartBeatTaskThread::PushTask(const SPHeartBeatTask& task)
{
    if (task == nullptr || m_stop)
    {
        return;
    }

    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    SPHeartBeatTaskWraper tmp(new(std::nothrow) HeartBeatTaskWraper(task));

    if (tmp != nullptr)
    {
        m_taskList.push_back(tmp);
    }
}

void HeartBeatTaskThread::PushTask(const std::function<bool()>& task, uint32_t timeOut, int32_t times)
{
    PushTask(SPHeartBeatTask(new (std::nothrow) HeartBeatFunTask(task, timeOut, times)));
}

size_t HeartBeatTaskThread::GetTaskCount()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    return m_taskList.size() + (m_currentTask != nullptr ? 1 : 0);
}

void HeartBeatTaskThread::ThreadCallBack()
{
    std::list<SPHeartBeatTaskWraper > tmpList;

    while (true)
    {
        {
            std::lock_guard<std::recursive_mutex> lock(m_mutex);

            if (m_stop)
            {
                break;
            }

            for (auto it : tmpList)
            {
                m_taskList.push_back(it);
            }

            tmpList.clear();

            m_taskList.swap(tmpList);
        }

        // ���������ȫ��ִ�е�
        auto it = tmpList.begin();
        while (it != tmpList.end())
        {
            auto tmpIt = it++;
            if (tmpList.empty() || m_stop)
            {
                break;
            }

            {
                std::lock_guard<std::recursive_mutex> lock(m_mutex);
                m_currentTask = *tmpIt;
            }

            if (m_currentTask == nullptr)
            {
                tmpList.erase(tmpIt);
                continue;
            }

            // ִ������
            if (m_currentTask->CanExecute())
            {
                m_currentTask->m_spHeartBeatTask->DoTask();

                if (m_currentTask->m_spHeartBeatTask->RemoveAfterExcute())
                {
                    tmpList.erase(tmpIt);
                }
            }

            // �����Ҫ��Ϊ�˷�ֹ���������г�ʱ��ִ��ռ��mutex
            SPHeartBeatTaskWraper tmp = m_currentTask;

            {
                std::lock_guard<std::recursive_mutex> lock(m_mutex);
                m_currentTask = nullptr;
            }
        }

        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}
