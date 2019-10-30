
//////////////////////////////////////////////////////////////////////////
// �ṩһ����־ʵ����࣬�Լ�һЩ���õ�ʵ��                                     //
//////////////////////////////////////////////////////////////////////////

#ifndef __ILOG_H_
#define __ILOG_H_

#include "ILogExecutor.h"
#include "task/ISimpleTask.h"
#include "noncopyable.h"

#include <assert.h>
#include <memory>
#include <vector>

/** ��־ʵ��
*/
class ILog :
    public ITask,
    public NonCopyable
{
public:
    ILog()
    {
    }

    /** ִ������
    */
    virtual void DoTask()
    {
        Log();
    }

    /** ��־����
    */
    virtual void Log() = 0;

    /** ֹͣ����
    */
    virtual void Stop()
    {
        // ɾ��
    };
};

/** �ṩһ���򵥻��࣬����־�����Ϊ�����֣��ַ�����format���Դ������ַ��������ļ���¼�����紫��ȣ�
*/
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

    /** ��ʼ��
    @param [in] level ��־�ȼ�
    @param [in] config ��־����
    */
    inline void Init(LogDogConfigLevel level, const std::shared_ptr <LogDogConfig>& config)
    {
        m_level = level;
        m_spConfig = config;
    }

    inline void PushExecutor(const std::shared_ptr<ILogExecutor>& executor)
    {
        m_executors.push_back(executor);
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

    /** ����ִ����
    */
    std::vector<std::shared_ptr<ILogExecutor> > m_executors;
};

/** һ������־�����࣬����־���˻�����Ϣ���ļ�����������־�ȼ�����formate
*/
class SimpleLog :
    public ISimpleLog
{
public:
    /** ���캯��
    @param [in] logStr ��־��������
    */
    SimpleLog(const DogString& logStr) :
        m_logStr(logStr)
    {

    }

    /** ��������
    */
    ~SimpleLog()
    {

    }

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

#endif //__ILOG_H_
