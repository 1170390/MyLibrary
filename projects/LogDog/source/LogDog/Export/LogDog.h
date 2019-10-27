
/****************************************************************************/
/* �ṩһ��ʹ�õķ������û����Ը����������¸�д���ļ�                               */
/****************************************************************************/

#ifndef _LOGDOG_H__
#define _LOGDOG_H__

#include "ILogDog.h"
#include "LogImpl.h"
#include "singleton.h"
#include <unordered_map>
#include <functional>

/** className ��Ҫ�ṩһ����̬��std::shared_ptr<ILog> Create(...)����,���������������������,LOG���õ�ʱ��Ĳ���Ҫ�ϸ���ͬ
��������ʽǿ��ת������������char* ת��Ϊ std::string
*/
#define LOG_BIND(logType, className)\
{Singleton<LogDogManager>::GetInstance().Bind((int)logType, (void*)className::Create);}

/** ��־��������࣬�û����Ը����������¸�д
*/
class LogDogManager :
    public NonCopyable
{
protected:
    LogDogManager()
    {
        m_logDog = ILogDog::Create(_DogT(""), _DogT("test"));
    }

    LogDogManager(const LogDogManager&) = delete;
    LogDogManager& operator=(const LogDogManager&) = delete;

public:
    inline std::shared_ptr<ILogDog>& GetLodDog()
    {
        return m_logDog;
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

private:
    /** ����ֻ����һ����־���������Ҫ�Ļ���Ϊmap��ά�����
    */
    std::shared_ptr<ILogDog> m_logDog;

    /** ��־ʵ�崴����
    */
    std::unordered_map<int, void*> m_logCreators;
};

template <class ..._Types>
void LOG(int type, _Types... _Args)
{
    void* creator = Singleton<LogDogManager>::GetInstance().GetCreator(type);

    if (creator == NULL)
    {
        return;
    }

    std::shared_ptr<ILog> log = (((std::shared_ptr<ILog>(*)(_Types...))creator)(_Args...));

    if (log != NULL)
    {
        Singleton<LogDogManager>::GetInstance().GetLodDog()->Push(log);
    }
}

#endif

