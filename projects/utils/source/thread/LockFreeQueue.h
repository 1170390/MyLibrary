
#ifndef __LOCKFREE_QUEUE_H_
#define __LOCKFREE_QUEUE_H_

#include "LockFreeData.h"

#include <new>
#include <atomic>

/** ��������
*/
template<class ty>
class LockFreeQueue
{
public:
    /** ����/��������
    */
    LockFreeQueue() :
        m_size(0),
        m_head(nullptr),
        m_tail(nullptr)
    {
        // �����ʱ�򲻻����̰߳�ȫ����
        m_head = new(std::nothrow) LockFreeData();
        m_tail = m_head;
    }

    ~LockFreeQueue()
    {
        // ������ʱ�򲻻����̰߳�ȫ����
        m_tail = nullptr;

        while (m_head != nullptr)
        {
            ILockFreeData* pTmp = m_head;
            m_head = m_head->m_pNext;
            delete pTmp;
        }
    }

public:
    /** ��������
    @param [out] data����
    @return ʧ�ܷ���NULL�����򷵻ض��ף������һ�ݸ���
    */
    template<class ty>
    bool Pop(ty& out)
    {
        if (m_head == nullptr)
        {
            return false;
        }

        LockFreeData* p = nullptr;

        do
        {
            p = m_head;

            if (p->m_pNext == NULL)
            {
                return false;
            }

        } while (m_head.compare_exchange_strong(p, p->m_pNext));

        --m_size;
        out = p->m_pNext->m_val;
        delete p;
    }

    /** ѹ���β
    @param [in] data����
    @return �Ƿ�ɹ�
    */
    template<class ty>
    bool Push(const ty& data)
    {
        LockFreeData* q = new(std::nothrow) LockFreeData(data);

        if (q == nullptr)
        {
            return false;
        }

        LockFreeData* p = m_tail;
        LockFreeData* rawTail = p;
        int i = 0;

        do
        {
            if (i == 2)
            {
                while (p->next != nullptr)
                {
                    p = p->next;
                }
            }
            else
            {
                ++i;
                p = m_tail;
            }
        } while (p->m_pNext.compare_exchange_strong(nullptr, q));
        
        m_tail.compare_exchange_strong(i == 2 ? rawTail : p, q);
        ++m_size;
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
    LockFreeData* m_head;

    /** ����β��
    */
    LockFreeData* m_tail;
};

#endif //__LOCKFREE_QUEUE_H_
