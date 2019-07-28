
#ifndef __CPU_THREAD_COUNT_H_
#define __CPU_THREAD_COUNT_H_

/** ���cpu�����ߴ�����,����һ������
*/
class CpuCoreThreadCount
{
protected:
    /** ���캯��
    */
    CpuCoreThreadCount();

    /** �������캯��ɾ����
    */
    CpuCoreThreadCount(const CpuCoreThreadCount&) = delete;

    /** ��ֵ���캯��ɾ����
    */
    CpuCoreThreadCount& operator= (const CpuCoreThreadCount&) = delete;

public:
    inline unsigned int GetCount()
    {
        return m_cpuCoreThreadCount;
    }

private:
    /** cpu����߼��߳�����Ϊ0��ʱ��˵����ȡʧ�ܣ��ⲿ�Լ�����
    */
    unsigned int m_cpuCoreThreadCount;
};

#endif // __CPU_THREAD_COUNT_H_


