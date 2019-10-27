
#include "Export/ILogDog.h"
#include "task/SimpleTaskQueue.h"
#include "typedef/DogString.h"

#include <map>

class LogDogImpl :
    public ILogDog
{
public:
    /** ���캯��
    @param [in] path �����ļ�·��
    @param [in] name ����־������
    */
    LogDogImpl(const DogString& path, const DogString& name)
    {
        // ���������ļ�����Ҫȥ�ж��Ƿ���سɹ����������ʧ���ˣ�m_configֻ����·�������ƣ��Ա��������
        m_spConfig = ILogDogConfig::Create(path, name);

        if (m_spConfig == NULL)
        {
            return;
        }

        // ��ʼ���������
        m_spLogQue.reset(new(std::nothrow) SimpleTaskQueue());

        if (m_spLogQue == NULL)
        {
            return;
        }

        if (!m_spLogQue->Start())
        {
            return;
        }

        return;
    }

    /** ��������
    */
    ~LogDogImpl()
    {
    }

    /** ѹ����־
    @param [in] log ��־ʵ��
    */
    virtual void Push(std::shared_ptr<ILog>& log)
    {
        if (log == NULL)
        {
            return;
        }

        log->SetLogConfig(m_spConfig);
        m_spLogQue->PushTask(log);
    }

private:
    /** �����ļ�
    */
    std::shared_ptr <ILogDogConfig> m_spConfig;

    /** ��־�������
    */
    std::shared_ptr<SimpleTaskQueue> m_spLogQue;
};

std::shared_ptr<ILogDog> ILogDog::Create(const DogString& path, const DogString& name)
{
    return std::shared_ptr<ILogDog>(new(std::nothrow) LogDogImpl(path, name));
}
