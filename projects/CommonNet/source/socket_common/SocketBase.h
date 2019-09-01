
#ifndef __SOCKETBASE_H_
#define __SOCKETBASE_H_

#include "SocketBean.h"

/** TODO:error_message
*/
class SocketBase
{
public:
    /** ���캯��
    */
    SocketBase();

    /** ��������
    */
    virtual ~SocketBase()
    {
        UnInit();
    }

    /** ��������
    */
    SocketBase(const SocketBase&) = delete;
    SocketBase& operator=(const SocketBase&) = delete;

protected:
    /** ��ʼ������Ҫ�ŵ����캯������
    @parma [in] type socket���ݴ�������
    @parma [in] ipProto Э��
    return �Ƿ�ɹ�
    */
    virtual bool Init(SocketType type, IpProtocolType ipProto);

    /** ������Դ
    return �Ƿ�ɹ�
    */
    bool UnInit();

public:
    inline unsigned int GetBuffSize()
    {
        return m_buffSize;
    }

    inline void SetBuffSize(unsigned int size)
    {
        m_buffSize = size;
    }

public:
    /** ���m_socketNode
    @return socket ������Ϣ
    */
    inline SocketBean& GetSocketBean()
    {
        return m_socketBean;
    }

private:
    /** socket ������Ϣ
    */
    SocketBean m_socketBean;

    /** �����С
    */
    unsigned int m_buffSize;
};

#endif //__ISOCKET_H_
