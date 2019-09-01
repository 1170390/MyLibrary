
#ifndef __SOCKET_TCP_BASE_H_
#define __SOCKET_TCP_BASE_H_

#include "socket_common/SocketBase.h"


class SocketTcpBase :
    public SocketBase
{
public:
    /** ���캯��
    */
    SocketTcpBase();

    /** ��������
    */
    virtual ~SocketTcpBase();

public:
    /** ������Ϣ ��msg���ڴ�Լ 1Kʱ�򷵻ص�ֵ���ܲ�����msg��ֵ��һ���Է��Ͳ��ˣ�
    @param [in] msg ϣ�����͵���Ϣ
    @return �ɹ����ط��͵ĸ�����ʧ�ܷ���SOCKET_ERROR
    */
    virtual int SendMsg(const std::string & msg);

    /** ������Ϣ
    @param [out] msg �յ�����Ϣ
    @return �ɹ����ؽ��ܵĸ�����ʧ�ܷ���SOCKET_ERROR
    */
    virtual int RcvMsg(std::string & msg);
};

#endif // __SOCKET_TCP_BASE_H_

