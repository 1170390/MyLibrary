
#ifndef __SOCKET_SERVER_H_
#define __SOCKET_SERVER_H_

#include "SocketBase.h"

class SocketServer :
    public SocketBase
{
public:
    /** ���캯��
    */
    SocketServer();

    /** ���캯��
    */
    virtual ~SocketServer();

public:
    /** ��
    param [in] socketAddr ������ip�Ͷ˿�
    @return �Ƿ�ɹ�
    */
    bool Bind(const SOCKADDR& socketAddr);

    /** �� INADDR_ANY 
    param [in] address ip��ַ
    param [in] port �˿�
    @return �Ƿ�ɹ�
    */
    bool Bind(const std::string& address, unsigned short port);

    /** listen
    param [in] backlog ���ڽ�������������������Ŀ �����ϵͳ��������Ŀ��20����Ҳ��������Ϊ5��10��
    @return �Ƿ�ɹ�
    */
    bool Listen(unsigned int backlog);

    /** ���������client���ڲ�����SocketBase����Ҫ�Լ��ͷ�
    @return �ɹ������µ�socket��ʧ�ܷ���NULL
    */
    SocketBase* Accept();
};

#endif //__SOCKET_SERVER_H_
