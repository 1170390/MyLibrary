
#ifndef __SOCKET_TCP_SERVER_H_
#define __SOCKET_TCP_SERVER_H_

#include "SocketTcpBase.h"

class SocketTcpServer :
    public SocketTcpBase
{
public:
    /** ���캯��
    @param [in] ip ����������ip��ַ "0" ��ʾ����
    @param [in] port �����������˿�
    */
    SocketTcpServer(const std::string& ip, unsigned short port);

    /** ��������
    */
    virtual ~SocketTcpServer();

public:
    /** listen
    ��ʼ��socket -> bind -> listen
    param [in] backlog ���ڽ�������������������Ŀ �����ϵͳ��������Ŀ��20����Ҳ��������Ϊ5��10��
    @return �Ƿ�ɹ�
    */
    bool Listen(unsigned int backlog);

    /** ���������client���ڲ�����SocketBase����Ҫ�Լ��ͷ�
    @return �ɹ������µ�socket��ʧ�ܷ���NULL
    */
    SocketTcpBase* Accept();
};

#endif // __SOCKET_TCP_SERVER_H_


