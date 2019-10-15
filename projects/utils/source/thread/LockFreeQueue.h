
#ifndef __LOCKFREE_QUEUE_H_
#define __LOCKFREE_QUEUE_H_

#include "LockFreeData.h"

#include <new>
#include <atomic>

/** ��ȫ��push
*/
//#define LOCKFREE_QUEUE_SAFEPUSH

/** ��������
*/
template<class ty>
class LockFreeQueue
{
    using tyData = LockFreeData<ty>;
public:
    /** ����/��������
    */
    LockFreeQueue() :
        m_size(0),
        m_head(nullptr),
        m_tail(nullptr)
    {
        // �����ʱ�򲻻����̰߳�ȫ����
        m_head = new(std::nothrow) tyData();
        m_tail = m_head;
    }

    ~LockFreeQueue()
    {
        // ������ʱ�򲻻����̰߳�ȫ����
        m_tail = nullptr;

        while (m_head != nullptr)
        {
            tyData* pTmp = m_head;
            m_head = m_head->m_pNext;
            delete pTmp;
        }
    }

public:
    /** ��������
    @param [out] data����
    @return ʧ�ܷ���NULL�����򷵻ض��ף������һ�ݸ���
    */
    bool Pop(ty& out)
    {
        if (m_head == nullptr)
        {
            return false;
        }

        tyData* p = nullptr;

        do
        {
            p = m_head;

            if (p->m_pNext == NULL)
            {
                return false;
            }

        } while (!__sync_bool_compare_and_swap(m_head, p, p->m_pNext));

        --m_size;
        out = p->m_pNext->m_val;
        delete p;
        return true;
    }

    /** ѹ���β
    @param [in] data����
    @return �Ƿ�ɹ�
    */
    bool Push(const ty& data)
    {
        if (m_tail == nullptr)
        {
            return false;
        }

        tyData* q = new(std::nothrow) tyData(data);

        if (q == nullptr)
        {
            return false;
        }

        tyData* p = m_tail;
#ifdef LOCKFREE_QUEUE_SAFEPUSH
        int i = 0;
#endif
        do
        {
#ifdef LOCKFREE_QUEUE_SAFEPUSH
            if (i == 3 && p->m_pNext != nullptr)
            {
                p = p->m_pNext;
                m_tail = p;
            }
            else
            {
                p = m_tail;
                ++i;
            }
#else
            p = m_tail;
#endif // LOCKFREE_QUEUE_SAFEPUSH
        } while (!__sync_bool_compare_and_swap(p->m_pNext, nullptr, q));
        
        __sync_bool_compare_and_swap(m_tail, p, q);
        ++m_size;
        return true;
    }

    /** ��ô�С
    */
    int Size()
    {
        return m_size;
    }

protected:
    /** �����Ĵ�С
    */
    std::atomic<int> m_size;

    /** ����ͷ�������ֻ�Ǳ��ͷ��������������
    */
    tyData* m_head;

    /** ����β��
    */
    tyData* m_tail;
};

#endif //__LOCKFREE_QUEUE_H_
