
#include "cpu_thread_count.h"
#include <thread>
#include <windows.h>

CpuCoreThreadCount::CpuCoreThreadCount() :
    m_cpuCoreThreadCount(0)
{
    // ͨ��std�ṩ�ķ�����ȡ
    m_cpuCoreThreadCount = std::thread::hardware_concurrency();

    if (m_cpuCoreThreadCount != 0)
    {
        return;
    }

    // �����ȡ�������ٵ���winapi���Ի�ȡ
    ::SYSTEM_INFO info;
    ::GetSystemInfo(&info);
    m_cpuCoreThreadCount = (unsigned int)info.dwNumberOfProcessors;

    // ������ǻ�ȡ���������� 
    // WMIC CPU Get NumberOfCores,NumberOfLogicalProcessors /Format:List > ./cpucore.txt 
    // �����ȡ�����������Ϊ����������Ҫ��ʼ��WMIC����Ҫ�漰�ļ���д�����������⣬���ԾͲ�ȥ������
}
