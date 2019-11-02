
#include "../LogDog.h"
#include "../LogDogDef.h"

#include <windows.h>

/** �����̵߳����ȼ�,�����һ���������־
*/
class DecreasePriority :
    public ILog
{
public:
    /** ��־
    */
    virtual void Log()
    {
        ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_BELOW_NORMAL);
    }
};

void LOG_INIT(const DogString& path, const DogString& name)
{
    if (!Singleton<LogDog>::GetInstance().Init(path, name))
    {
        return;
    }

    // ����־�̵߳����ȼ�����
    std::shared_ptr<ILog> log(new (std::nothrow)DecreasePriority());

    if (log != NULL)
    {
        Singleton<LogDog>::GetInstance().Push(log);
    }
}

void LOG_UNINIT()
{
    Singleton<LogDog>::GetInstance().UnInit();
}

void SIMPLE_LOG(LogDogConfigLevel level, const DogString & logStr)
{
    std::shared_ptr<ISimpleLog> log(new (std::nothrow)SimpleLog(level, logStr));

    if (log == NULL)
    {
        return;
    }

    log->PushExecutor(std::make_shared<DumpToFileExecutor>());
    log->PushExecutor(std::make_shared<UpLoadExecutor>());
    Singleton<LogDog>::GetInstance().Push(log);
}

LogDog::LogDog()
{

}

bool LogDog::Init(const DogString & path, const DogString & name)
{
    // ��ʼ���������
    m_spLogQue.reset(new(std::nothrow) SimpleTaskQueue());
    m_spLogQue->Start();

    // ��ʼ�������ļ�
    m_spConfig.reset(new(std::nothrow)LogDogConfig(path, name));

    return m_spLogQue != NULL;
}

void LogDog::Push(const std::shared_ptr<ILog>& log)
{
    if (m_spLogQue != NULL)
    {
        m_spLogQue->PushTask(log);
    }
}

std::shared_ptr<LogDogConfig> LogDog::GetConfig()
{
    assert(m_spConfig != NULL);
    return m_spConfig;
}

void LogDog::UnInit()
{
    m_spLogQue.swap(std::shared_ptr<SimpleTaskQueue>());
}
