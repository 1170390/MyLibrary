
#ifndef __SOCKET_TCP_CLIENT_H_
#define __SOCKET_TCP_CLIENT_H_

#include "SocketTcpBase.h"

class SocketTcpClient :
    public SocketTcpBase
{
public:
    /** ���캯��
    @param [in] ip ������ip��ַ
    @param [in] port �����������˿�
    */
    SocketTcpClient(const std::string& ip, unsigned short port);

    /** ��������
    */
    virtual ~SocketTcpClient();

public:
    /** ���ӵ� [��������]
        ��ʼ��socket -> ����
    @return �Ƿ�ɹ�
    */
    bool Connect();
};

#endif // __SOCKET_TCP_CLIENT_H_


