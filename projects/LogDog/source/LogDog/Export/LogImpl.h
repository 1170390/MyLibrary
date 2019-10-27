
#ifndef _LOGIMPL_H__
#define _LOGIMPL_H__

#include "ILogDog.h"

enum class LOGTYPE
{
    /** ����־
    */
    LOGTYPE_SIMPLE_LOG = 0,
};

class SimpleLog :
    public ILog
{
public:
    /** ����һ��ʵ��
    @param [in] level ��־�Ȼ�
    @param [in] logStr ��־��������
    */
    static std::shared_ptr<ILog> Create(LogDogConfigLevel level, const DogChar* logStr)
    {
        std::shared_ptr<ILog> log(new (std::nothrow)SimpleLog(level, logStr));
        return log;
    }

    /** ���캯��
    @param [in] level ��־�Ȼ�
    @param [in] logStr ��־��������
    */
    SimpleLog(LogDogConfigLevel level, const DogString& logStr) :
        m_level(level),
        m_logStr(logStr)
    {

    }

    ~SimpleLog()
    {
    }

public:
    /** ִ������
    */
    virtual void DoTask()
    {
    }

private:
    /** ��־����
    */
    DogString m_logStr;

    /** ��־�ȼ�
    */
    LogDogConfigLevel m_level = LogDogConfigLevel::LDC_LEVEL_5;
};

static std::shared_ptr<ILog> Create(LogDogConfigLevel level, const DogString& logStr)
{
    std::shared_ptr<ILog> log(new (std::nothrow)SimpleLog(level, logStr));
    return log;
}
#endif

