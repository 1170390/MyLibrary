
#ifndef __SOCKETBASE_H_
#define __SOCKETBASE_H_

#include "SocketNode.h"

/** socket���ݴ�������
*/
enum SocketType
{
    /** �ֽ���������TCP
    */
    SOCKET_STREAM = 1,

    /** ��ɢ���ݣ�����UDP
    */
    SOCKET_DGRAM  = 2
};

/** Э�飬Ŀǰֻ�ṩtcp��udp
*/
enum IpProtocolType
{
    IPPROTOCOL_TCP = 6,
    IPPROTOCOL_UDP = 17
};

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
    }

public:
    /** ��ʼ������Ҫ�ŵ����캯������
    @parma [in] type socket���ݴ�������
    @parma [in] ipProto Э��
    return �Ƿ�ɹ�
    */
    virtual bool Init(SocketType type, IpProtocolType ipProto);

    /** ������Դ����Ҫ�������е����麯�����мǣ��м�
    return �Ƿ�ɹ�
    */
    virtual bool UnInit();

    /** ������Ϣ ��msg���ڴ�Լ 1Kʱ�򷵻ص�ֵ���ܲ�����msg��ֵ��һ���Է��Ͳ��ˣ�
        pToSocket::IsValidSocket����false���������ӵ����ݱ�[����UDP]
    @param [in] toSocket ��Ϣ���ܷ�
    @param [in] msg ϣ�����͵���Ϣ
    @return �ɹ����ط��͵ĸ�����ʧ�ܷ���SOCKET_ERROR
    */
    virtual int SendMsg(const SocketNode& toSocket, const std::string & msg);

    /** ������Ϣ
        pFromSocket::IsValidSocket����false���������ӵ����ݱ�[����UDP]����ʱpFromSocket�����淢�ͷ���SOCKADDR
    @param [in] fromSocket ��Ϣ���ͷ�
    @param [out] msg �յ�����Ϣ
    @return �ɹ����ؽ��ܵĸ�����ʧ�ܷ���SOCKET_ERROR
    */
    virtual int RcvMsg(SocketNode& fromSocket, std::string & msg);

public:
    inline SocketNode& GetSocketNode()
    {
        return m_socketNode;
    }

    /** �������������һ����Ϣ������Ȼ����UDP�����Ӳ���Ҫʹ�����
    @param [out] fromSocket ��һ����Ϣ
    return �Ƿ�ɹ�
    */
    bool GetPeerName(SocketNode& fromSocket);

private:
    /** socket ������Ϣ
    */
    SocketNode m_socketNode;

    /** �����С
    */
    unsigned int m_buffSize;
};

#endif //__ISOCKET_H_
