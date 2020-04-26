
#include <atomic>

namespace lockfree
{

/** ��������Ҳ����::Sleep(0)��~~
*/
#define cpu_pause() __asm {pause}

/** ������
@note ���ֻ�ܵ����������ˣ�����Ч�ʲ�����mutex��
@note �о�������̣�����õ�ѭ�����ƵĻ��������ڳ����ˣ���Ϊmutex windows��ʵ��Ҳ��ѭ�����ƣ�����
@note ���Ļ�������٣�
@note �����еĵط�����ʹ��CAS����Ч�ʵ���������
*/
class spin_mutex
{
public:
    /** ���캯��
    */
    spin_mutex()
    {
    }

    ~spin_mutex()
    {

    }

    /** ����������
    */
    spin_mutex(spin_mutex&&) = delete;
    spin_mutex(const spin_mutex&) = delete;
    spin_mutex& operator=(const spin_mutex&&) = delete;

public:
    void lock()
    {
        // test_and_set ����m_falg������ǰ��ֵ
        while (m_flag.test_and_set() != false)
        {
           // cpu_pause()
        }
    }

    void unlock()
    {
        m_flag.clear();
    }

private:
    /** ���������
    */
    std::atomic_flag m_flag = ATOMIC_FLAG_INIT;
};
}