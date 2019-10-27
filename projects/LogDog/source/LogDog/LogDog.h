
/****************************************************************************/
/* �ṩһ��ʹ�õķ������û����Ը����������¸�д���ļ�                               */
/****************************************************************************/

#ifndef _LOGDOG_H__
#define _LOGDOG_H__

#include "LogImpl.h"
#include "LogDogConfig.h"

#include "singleton.h"
#include "task/SimpleTaskQueue.h"
#include <functional>
#include <unordered_map>
#include <thread>

/** className ��Ҫ�ṩһ����̬��std::shared_ptr<ILog> Create(...)����,���������������������,LOG���õ�ʱ��Ĳ���Ҫ�ϸ���ͬ
��������ʽǿ��ת������������char* ת��Ϊ std::string
*/
#define LOG_BIND(logType, className)\
{Singleton<LogDog>::GetInstance().Bind((int)logType, (void*)className::Create);}

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

    inline void Bind(int type, void* creator)
    {
        if (creator != NULL)
        {
            m_logCreators[type] = creator;
        }
    }

    inline void* GetCreator(int type)
    {
        auto it = m_logCreators.find(type);

        if (it != m_logCreators.end())
        {
            return (it->second);
        }

        return NULL;
    }

    /** �ͷ���Դ����ʵ������������Ǻ���Ҫ����Ϊ�����ڳ����˳���ʱ����Լ��ͷŵģ�
    ֻ��Ϊ�˺�init���Ӧ
    */
    inline void UnInit()
    {
        m_spLogQue.swap(std::shared_ptr<SimpleTaskQueue>());
    }

private:
    /** �����ļ�
    */
    std::shared_ptr <LogDogConfig> m_spConfig;

    /** ��־�������
    */
    std::shared_ptr<SimpleTaskQueue> m_spLogQue;

    /** ��־ʵ�崴����
    */
    std::unordered_map<int, void*> m_logCreators;
};


/** ��ʼ��
@param [in] path �����ļ�·��
@param [in] name �����ļ��ж�Ӧ��secsion
*/
void LOG_INIT(const DogString& path, const DogString& name)
{
    if (!Singleton<LogDog>::GetInstance().Init(path, name))
    {
        return;
    }

    LOG_BIND(LOGTYPE::LOGTYPE_SIMPLE_LOG, SimpleLog);

    // ���������һ��ļ�����־�ķ�������Ȼ�����ṩ����LOG����
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
void LOG_UNINIT()
{
    Singleton<LogDog>::GetInstance().UnInit();
}

/** �ṩ����LOG����
@param [in] type �ο�LOGTYPE
@param [in] __Args Create�����Ĳ�����Ҫ�������ϸ���ͬ����������ʽǿ��ת������������char* ת��Ϊ std::string
*/
template <class ..._Types>
void LOG(int type, _Types... _Args)
{
    void* creator = Singleton<LogDog>::GetInstance().GetCreator(type);

    if (creator == NULL)
    {
        return;
    }

    std::shared_ptr<ILog> log = (((std::shared_ptr<ILog>(*)(_Types...))creator)(_Args...));

    if (log != NULL)
    {
        Singleton<LogDog>::GetInstance().Push(log);
    }
}

#endif

