
#ifndef _LOGIMPL_H__
#define _LOGIMPL_H__

#include "ILog.h"
#include "LogDogConfig.h"
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

class ISimpleLog :
    public ILog
{
public:
    /** ���캯��
    @param [in] level ��־�Ȼ�
    @param [in] logStr ��־��������
    */
    ISimpleLog()
    {

    }

    virtual ~ISimpleLog()
    {
    }

    /** ��־
    */
    virtual void Log();

    /** ���õȼ�
    @param [in] level ��־�ȼ�
    @param [in] config ��־����
    */
    inline void Init(LogDogConfigLevel level, const std::shared_ptr <LogDogConfig>& config)
    {
        m_level = level;
        m_spConfig = config;
    }

private:
    /** ��ʽ����־�ַ���
    @param [out] outLogStr ����ַ���
    @return �Ƿ�ɹ�
    */
    virtual bool MakeLogStr(DogString& outLogStr) = 0;

protected:
    /** �����ļ�
    */
    std::shared_ptr <LogDogConfig> m_spConfig;

    /** ��־�ȼ�
    */
    LogDogConfigLevel m_level = LogDogConfigLevel::LDC_LEVEL_5;

};

class SimpleLog :
    public ISimpleLog
{
public:
    /** ���캯��
    @param [in] logStr ��־��������
    */
    SimpleLog(const DogString& logStr);

    /** ��������
    */
    ~SimpleLog();

private:
    /** ��ʽ����־�ַ���
    @param [out] outLogStr ����ַ���
    @return �Ƿ�ɹ�
    */
    virtual bool MakeLogStr(DogString& outLogStr);

private:
    /** ��־����
    */
    DogString m_logStr;
};

#endif

