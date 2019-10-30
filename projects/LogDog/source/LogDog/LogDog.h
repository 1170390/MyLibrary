
/****************************************************************************/
/* �ṩһ��ʹ�õķ������û����Ը����������¸�д���ļ�                               */
/****************************************************************************/

#ifndef _LOGDOG_H__
#define _LOGDOG_H__

#include "ILog.h"
#include "LogDogConfig.h"

#include "singleton.h"
#include "task/SimpleTaskQueue.h"
#include <functional>
#include <unordered_map>
#include <thread>

/** ��־��������࣬�û����Ը����������¸�д
*/
class LogDog :
    public NonCopyable
{
protected:
    LogDog()
    {
    }

public:
    /** ��ʼ��
    @param [in] path �����ļ�·��
    @param [in] name �����ļ��ж�Ӧ��secsion
    @return ��־�߳��Ƿ񴴽��ɹ�
    */
    inline bool Init(const DogString& path, const DogString& name)
    {
        // ��ʼ���������
        m_spLogQue.reset(new(std::nothrow) SimpleTaskQueue());
        m_spLogQue->Start();

        // ��ʼ�������ļ�
        m_spConfig.reset(new(std::nothrow)LogDogConfig(path, name));

        return m_spLogQue != NULL;
    }

    inline void Push(const std::shared_ptr<ILog>& log)
    {
        if (m_spLogQue != NULL)
        {
            m_spLogQue->PushTask(log);
        }
    }

    /** �ͷ���Դ����ʵ������������Ǻ���Ҫ����Ϊ�����ڳ����˳���ʱ����Լ��ͷŵģ�
    ֻ��Ϊ�˺�init���Ӧ
    */
    inline void UnInit()
    {
        m_spLogQue.swap(std::shared_ptr<SimpleTaskQueue>());
    }

    inline std::shared_ptr <LogDogConfig>& GetConfig()
    {
        return m_spConfig;
    }

private:
    /** �����ļ�
    */
    std::shared_ptr <LogDogConfig> m_spConfig;

    /** ��־�������
    */
    std::shared_ptr<SimpleTaskQueue> m_spLogQue;
};

/** �����̵߳����ȼ�,�����һ���������־
*/
#include <windows.h>
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

/** ��ʼ��
@param [in] path �����ļ�·��
@param [in] name �����ļ��ж�Ӧ��secsion
*/
inline void LOG_INIT(const DogString& path, const DogString& name)
{
    if (!Singleton<LogDog>::GetInstance().Init(path, name))
    {
        return;
    }

    {
        // ����־�̵߳����ȼ�����
        std::shared_ptr<ILog> log(new (std::nothrow)DecreasePriority());

        if (log != NULL)
        {
            Singleton<LogDog>::GetInstance().Push(log);
        }
    }
}

/** ����ʼ��
*/
inline void LOG_UNINIT()
{
    Singleton<LogDog>::GetInstance().UnInit();
}

/** ����־
@param [in] level ��־�ȼ�
@param [in] logStr ��־��������
*/
inline void SIMPLE_LOG(LogDogConfigLevel level, const DogString& logStr)
{
    // ����־�̵߳����ȼ�����
    std::shared_ptr<ISimpleLog> log(new (std::nothrow)SimpleLog(logStr));

    if (log == NULL)
    {
        return;
    }

    log->Init(level, Singleton<LogDog>::GetInstance().GetConfig());
    log->PushExecutor(std::make_shared<DumpToFileExecutor>());
    log->PushExecutor(std::make_shared<UpLoadExecutor>());
    Singleton<LogDog>::GetInstance().Push(log);
}

/** ������Ϣ
*/
#define LOG_DEBUG(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_6, logStr)

/** ��ͨ��Ϣ
*/
#define LOG_INFO(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_5, logStr)

/** ����
*/
#define LOG_WARNING(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_4, logStr)

/** assert �����п�/��ĸΪ0
*/
#define LOG_ASSERT(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_3, logStr)

/** ���صĴ��󣬱�����Դ�����˵�
*/
#define LOG_SERIOUS_ERROR(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_2, logStr)

/** �������صĴ����Ҳ�֪���ͱ�����ɶ����o_0
*/
#define LOG_VERY_SERIOUS_ERROR(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_1, logStr)

/** ����������󣬱�����Ϊʲô�ܹ�����־����ʵ��Ҳ��֪��
@note try catch�еı����ϱ�
*/
#define LOG_CRASH(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_0, logStr)

#endif

