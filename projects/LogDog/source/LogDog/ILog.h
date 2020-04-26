
//////////////////////////////////////////////////////////////////////////
// �ṩһ����־ʵ����࣬�Լ�һЩ���õ�ʵ��                                     //
//////////////////////////////////////////////////////////////////////////

#ifndef __ILOG_H_
#define __ILOG_H_

#include "ILogExecutor.h"
#include "noncopyable/noncopyable.h"
#include "LogDogDef.h"

#include "thread/task/ITask.h"

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
    ILog();

    virtual ~ILog();

    /** ִ������
    */
    virtual void DoTask();

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
    ISimpleLog(LogDogConfigLevel level, const DogString& logStr);

    /** ��������
    */
    virtual ~ISimpleLog();

    /** ��־
    */
    virtual void Log();

    /** ���һ��ִ����
    @param [in] executor ִ����
    */
    void PushExecutor(const std::shared_ptr<ILogExecutor>& executor);

private:
    /** ��ʽ����־�ַ���
    @param [out] outLogStr ����ַ���
    @return �Ƿ�ɹ�
    */
    virtual bool MakeLogStr(DogString& outLogStr) = 0;

protected:
    /** ��־�ȼ�
    */
    LogDogConfigLevel m_level = LogDogConfigLevel::LDC_LEVEL_5;

    /** ��־����
    */
    DogString m_logStr;

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
    SimpleLog(LogDogConfigLevel level, const DogString& logStr);

    /** ��������
    */
    ~SimpleLog();

private:
    /** ��ʽ����־�ַ���
    @param [out] outLogStr ����ַ���
    @return �Ƿ�ɹ�
    */
    virtual bool MakeLogStr(DogString& outLogStr);
};

#endif //__ILOG_H_
