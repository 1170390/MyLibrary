#include "LogDog.h"

LogDog::LogDog()
{
}

LogDog::~LogDog()
{
}

bool LogDog::Init(const DogString& path, const DogString & name)
{
    // ���������ļ�����Ҫȥ�ж��Ƿ���سɹ����������ʧ���ˣ�m_configֻ����·�������ƣ��Ա��������
    m_config.ReLoad(path, name);

    // ��ʼ���������
    m_taskque.reset(new(std::nothrow) SimpleTaskQueue());

    if (m_taskque == NULL)
    {
        return false;
    }

    if (!m_taskque->Start())
    {
        return false;
    }



    return true;
}
