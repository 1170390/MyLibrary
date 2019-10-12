
#ifndef __LOCKFREE_DATA_H_
#define __LOCKFREE_DATA_H_

template<class ty>
class LockFreeData
{
public:
    /** ���캯��
    */
    LockFreeData(const ty& val) :
        m_val(val),
        m_pNext(NULL)
    {

    }

    /** ���캯��
    */
    LockFreeData() :
        m_pNext(NULL)
    {

    }

    /** ��������
    */
    LockFreeData(const LockFreeData&) = delete;
    LockFreeData(LockFreeData&&) = delete;
    LockFreeData& operator =(const LockFreeData&) = delete;

    ~LockFreeData()
    {
        m_pNext = NULL;
    }

public:
    /** ����
    */
    ty m_val;

    /** ��һ��ָ��
    */
    LockFreeData* m_pNext;
};

#endif //__LOCKFREE_DATA_H_
