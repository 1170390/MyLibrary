
#ifndef __SOCKET_UDP_BASE_H_
#define __SOCKET_UDP_BASE_H_

#include "socket_common/SocketBase.h"


class SocketUdpBase :
    public SocketBase
{
public:
    /** ���캯��
    */
    SocketUdpBase();

    /** ��������
    */
    virtual ~SocketUdpBase();

public:
    /** ������Ϣ ��msg���ڴ�Լ 1Kʱ�򷵻ص�ֵ���ܲ�����msg��ֵ��һ���Է��Ͳ��ˣ�
    @param [in] ip Ŀ��ip
    @param [in] port Ŀ��port
    @param [in] msg ϣ�����͵���Ϣ
    @return �ɹ����ط��͵ĸ�����ʧ�ܷ���SOCKET_ERROR
    */
    virtual int SendMsg(const std::string& ip, unsigned short port, const std::string & msg);

    /** ������Ϣ ��msg���ڴ�Լ 1Kʱ�򷵻ص�ֵ���ܲ�����msg��ֵ��һ���Է��Ͳ��ˣ�
    @param [in] sockAddr Ŀ��sockAddr
    @param [in] msg ϣ�����͵���Ϣ
    @return �ɹ����ط��͵ĸ�����ʧ�ܷ���SOCKET_ERROR
    */
    virtual int SendMsg(const SOCKADDR& sockAddr, const std::string & msg);

    /** ������Ϣ
    @param [out] ip Ŀ��ip
    @param [out] port Ŀ��port
    @param [out] msg �յ�����Ϣ
    @return �ɹ����ؽ��ܵĸ�����ʧ�ܷ���SOCKET_ERROR
    */
    virtual int RcvMsg(std::string & msg, std::string& ip, unsigned short& port);

    /** ������Ϣ
    @param [out] sockAddr Ŀ��sockAddr
    @param [out] msg �յ�����Ϣ
    @return �ɹ����ؽ��ܵĸ�����ʧ�ܷ���SOCKET_ERROR
    */
    virtual int RcvMsg(std::string & msg, SOCKADDR& sockAddr);
};

#endif // __SOCKET_UDP_BASE_H_

