
#ifndef __LOCKFREE_QUEUE_H_
#define __LOCKFREE_QUEUE_H_

#include "lockfree_data.h"
#include "spin_mutex.h"
namespace lockfree
{
/** ��������
*/
template<class ty>
class lockfree_queue
{
    using ty_data = lockfree_data<ty>;

public:
    /** ����/��������
    */
    lockfree_queue() :
        m_size(0),
        m_head(nullptr),
        m_tail(nullptr)
    {
        // �����ʱ�򲻻����̰߳�ȫ����
        m_head = new(std::nothrow) ty_data();
        m_tail = m_head;
    }

    ~lockfree_queue()
    {
        // ������ʱ�򲻻����̰߳�ȫ����
        m_spinLock.unlock();
        m_tail = nullptr;

        while (m_head != nullptr)
        {
            ty_data* pTmp = m_head;
            m_head = m_head->m_pNext;
            delete pTmp;
        }
    }

public:
    /** ��������
    @param [out] data����
    @return ʧ�ܷ���NULL�����򷵻ض��ף������һ�ݸ���
    */
    bool pop(ty& out)
    {
        m_spinLock.lock();

        if (m_head->m_pNext == nullptr)
        {
            m_spinLock.unlock();
            return false;
        }

        --m_size;
        ty_data* p = m_head;
        m_head = m_head->m_pNext;
        out = p->m_pNext->m_val;
        m_spinLock.unlock();
        delete p;
        return true;
    }

    /** ѹ���β
    @param [in] data����
    @return �Ƿ�ɹ�
    */
    bool push(const ty& data)
    {
        ty_data* q = new(std::nothrow) ty_data(data);

        if (q == nullptr)
        {
            return false;
        }

        m_spinLock.lock();
        m_tail->m_pNext = q;
        m_tail = q;
        ++m_size;
        m_spinLock.unlock();
        return true;
    }

    /** ��ô�С
    */
    int size()
    {
        return m_size;
    }

protected:
    /** �����Ĵ�С
    */
    int m_size;

    /** ����ͷ�������ֻ�Ǳ��ͷ��������������
    */
    ty_data* m_head;

    /** ����β��
    */
    ty_data* m_tail;

    /** ������
    */
    spin_mutex m_spinLock;
};
}
#endif //__LOCKFREE_QUEUE_H_
