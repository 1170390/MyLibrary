
#ifndef _LOGIMPL_H__
#define _LOGIMPL_H__

#include "ILog.h"
#include "LogDogDef.h"
#include <memory>

/** �����̵߳����ȼ�,�����һ���������־
*/
class DecreasePriority :
    public ILog
{
public:
    /** ��־
    */
    virtual void Log();
};

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
    static std::shared_ptr<ILog> Create(LogDogConfigLevel level, const DogChar* logStr);

    /** ���캯��
    @param [in] level ��־�Ȼ�
    @param [in] logStr ��־��������
    */
    SimpleLog(LogDogConfigLevel level, const DogString& logStr);

    /** ��������
    */
    ~SimpleLog();

public:
    /** ��־
    */
    virtual void Log();

private:
    /** ��־����
    */
    DogString m_logStr;

    /** ��־�ȼ�
    */
    LogDogConfigLevel m_level = LogDogConfigLevel::LDC_LEVEL_5;
};

#endif

