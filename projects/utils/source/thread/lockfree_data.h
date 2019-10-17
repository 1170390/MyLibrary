
#ifndef __LOCKFREE_DATA_H_
#define __LOCKFREE_DATA_H_

namespace lockfree
{
template<class ty>
class lockfree_data
{
public:
    /** ���캯��
    */
    lockfree_data(const ty& val) :
        m_val(val),
        m_pNext(NULL)
    {

    }

    /** ���캯��
    */
    lockfree_data() :
        m_pNext(NULL)
    {

    }

    /** ��������
    */
    lockfree_data(const lockfree_data&) = delete;
    lockfree_data(lockfree_data&&) = delete;
    lockfree_data& operator =(const lockfree_data&) = delete;

    ~lockfree_data()
    {
        m_pNext = NULL;
    }

public:
    /** ����
    */
    ty m_val;

    /** ��һ��ָ��
    */
    lockfree_data* m_pNext;
};
}
#endif //__LOCKFREE_DATA_H_
