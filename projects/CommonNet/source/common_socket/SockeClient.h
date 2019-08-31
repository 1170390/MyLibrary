
#ifndef __SOCKET_CLINT_H_
#define __SOCKET_CLINT_H_

#include "SocketBase.h"

class Socket_client :
    public SocketBase
{
public:
    /** ���캯��
    */
    Socket_client();

    /** ��������
    */
    virtual ~Socket_client();

public:
    /** ���ӵ� [��������]
    param [in] socketAddr ������ip�Ͷ˿�
    @return �Ƿ�ɹ�
    */
    bool Connect(const SOCKADDR& socketAddr);

    /** ���ӵ� [��������]
    param [in] address ip��ַ
    param [in] port �˿�
    @return �Ƿ�ɹ�
    */
    bool Connect(const std::string& address, unsigned short port);
};

#endif //__SOCKET_CLINT_H_
