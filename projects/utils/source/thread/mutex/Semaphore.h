
#ifndef __SEMAPHORE_H_
#define __SEMAPHORE_H_

#include "noncopyable/noncopyable.h"

#include <mutex>

class Semaphore :
    public NonCopyable
{
public:
    /** �ȴ�һ���źţ����ѣ�
    @note �����Wait()ǰ�Ѿ����ź��ˣ���ôwait������ȴ�
    */
    void Wait()
    {
        std::unique_lock<std::mutex> lck(m_mutex);

        if (m_count <= 0)
        {
            // �������������ǣ�
            // 1��m_mutex.unlock();
            // 2��wait()
            // 3��m_mutex.lock();
            // wait(lck) �൱�ڽ�1��2�����ŵ�һ��cpu������
            m_con.wait(lck);
        }

        --m_count;

        // ��ֹNotifyAll�����m_count����Ϊ0
        if (m_count < 0)
        {
            m_count = 0;
        }
    }

    /** ����һ���źţ�������
    */
    void Signal()
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        ++m_count;
        m_con.notify_one();
    }

    /** �������У����ã�
    */
    void NotifyAll()
    {
        m_count = 0;
        std::unique_lock<std::mutex> lck(m_mutex);
        m_con.notify_all();
    }

private:
    /** ������
    */
    std::mutex m_mutex;

    /** condition_variable
    */
    std::condition_variable m_con;

    /** �Ƿ����ź�
    @note ��Ҫ��Ϊ���ȵ���SetEvent()��Ȼ�����wait() ���ᱻ���ѵ��������ν�ġ���ٻ��ѡ���������Wait()ǰ����::Sleep(1000);
    */
    long m_count = 0;
};



#endif //__SEMAPHORE_H_
