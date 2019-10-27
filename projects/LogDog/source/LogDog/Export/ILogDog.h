
#ifndef __ILOGDOG_H_
#define __ILOGDOG_H_

#include "LogDogDef.h"
#include "task/ISimpleTask.h"
#include "noncopyable.h"

#include <assert.h>
#include <functional>
#include <memory>

class ILogDogConfig :
    public NonCopyable

{
public:
    /** ��������
    */
    virtual ~ILogDogConfig(){}

    /** ��ʼ��
    @param [in] path �����ļ�·��
    */
    virtual void ReLoad(const std::wstring& path, const std::wstring& name) = 0;

    /* ���������ļ��Ƿ��д���
    @return ������ ����LDC_NO_ERROR��ʾ�ɹ�
    */
    virtual LogDogConfigErrorCode GetErrorCode() = 0;

    /** �����־����
    @return ��־����
    */
    virtual LogDogConfigEntry& GetLogDogConfigEntry() = 0;

    /** ����
    @param [in] path �����ļ�·��
    @param [in] name �������в��ҵ���־����
    */
    static std::shared_ptr<ILogDogConfig> Create(const std::wstring & path, const std::wstring & name);
};

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
    virtual void DoTask() = 0;

    /** ֹͣ����
    */
    virtual void Stop()
    {
        // ɾ��
    };

    inline void SetLogConfig(const std::shared_ptr <ILogDogConfig>& logConfig)
    {
        m_spConfig = logConfig;
    }

private:
    /** ��־�е�������Ϣ
    */
    std::shared_ptr <ILogDogConfig> m_spConfig;
};

/** ��־��¼ִ����
*/
class ILogDog :
    public NonCopyable
{
public:
    /** ��������
    */
    virtual ~ILogDog(){}

    /** ѹ����־
    @param [in] log ��־ʵ��
    */
    virtual void Push(std::shared_ptr<ILog>& log) = 0;

    /** ����������־����
    @return ��־����
    */
    static std::shared_ptr<ILogDog> Create(const DogString& path, const DogString& name);
};


#endif //__ILOGDOG_H_
