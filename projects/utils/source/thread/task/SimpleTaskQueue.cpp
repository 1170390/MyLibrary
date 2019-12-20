
#include "SimpleTaskQueue.h"

/** ���¼�
*/
class SimpleEvent :
    public NonCopyable
{
public:
    /** �ȴ�һ���ź�
    */
    void Wait()
    {
        std::unique_lock<std::mutex> lck(m_mutex);

        if (!m_hasSignal)
        {
            // �������������ǣ�
            // 1��m_mutex.unlock();
            // 2��wait()
            // 3��m_mutex.lock();
            // wait(lck) �൱�ڽ�1��2�����ŵ�һ��cpu������
            m_con.wait(lck);
        }

        m_hasSignal = false;
    }

    /** ����һ���ź�
    */
    void SetEvent()
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_hasSignal = true;
        m_con.notify_all();
    }

private:
    /** ������
    */
    std::mutex m_mutex;

    /** condition_variable
    */
    std::condition_variable m_con;

    /** �Ƿ����źţ�ֻ�Ǽ�¼�Ƿ����źţ����ǲ���¼�źŴ���
    @note ��Ҫ��Ϊ���ȵ���SetEvent()��Ȼ�����wait�������������Wait()ǰ����::Sleep(1000);
    */
    bool m_hasSignal = false;
};

SimpleTaskQueue::SimpleTaskQueue() :
    m_stop(false),
    m_pThread(nullptr)
{
}

SimpleTaskQueue::~SimpleTaskQueue()
{
    if (m_pThread != nullptr)
    {
        StopAll();
        m_pThread->join();
        delete m_pThread;
        m_pThread = nullptr;
    }
}

bool SimpleTaskQueue::Start()
{
    m_pThread = new (std::nothrow) std::thread(&SimpleTaskQueue::ThreadCallBack, this);
    return m_pThread != NULL;
}

void SimpleTaskQueue::StopAll()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    ClearAll();
    m_stop = true;
    m_event.SetEvent();
}

void SimpleTaskQueue::StopCurrent()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (m_currentTask != nullptr)
    {
        m_currentTask->Stop();
    }
}

void SimpleTaskQueue::ClearAll()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    StopCurrent();
    ClearQueue();
}

void SimpleTaskQueue::ClearQueue()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    std::queue<std::shared_ptr<ITask> > tmp = std::queue<std::shared_ptr<ITask> >();
    m_taskQue.swap(tmp);
}

void SimpleTaskQueue::PushTask(const std::shared_ptr<ITask>& task)
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    m_taskQue.push(task);
    m_event.SetEvent();
}

void SimpleTaskQueue::PushTask(const std::function<void()>& task)
{
    PushTask(std::shared_ptr<ITask>(new SimpleFunTask(task)));
}

void SimpleTaskQueue::ThreadCallBack()
{
    while (true)
    {
        {
            std::lock_guard<std::recursive_mutex> lock(m_mutex);

            if (m_stop)
            {
                break;
            }
        }

        m_event.Wait();

        // ���������ȫ��ִ�е�
        while (true)
        {
            // ȡ������
            {
                std::lock_guard<std::recursive_mutex> lock(m_mutex);

                if (m_taskQue.empty())
                {
                    break;
                }

                m_currentTask = m_taskQue.front();
                m_taskQue.pop();

                if (m_currentTask == nullptr)
                {
                    continue;
                }
            }

            // ִ������
            m_currentTask->DoTask();

            // ׼������
            std::shared_ptr<ITask> tmp = m_currentTask;

            {
                std::lock_guard<std::recursive_mutex> lock(m_mutex);
                m_currentTask = nullptr;
            }
        }
    }
}
