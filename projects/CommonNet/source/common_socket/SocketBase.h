
#ifndef __SOCKETBASE_H_
#define __SOCKETBASE_H_

#include "SocketNode.h"

/** TODO:error_message
*/
class SocketBase
{
public:
    /** 构造函数
    */
    SocketBase();

    /** 析构函数
    */
    virtual ~SocketBase()
    {
        UnInit();
    }

    /** 不允许拷贝
    */
    SocketBase(const SocketBase&) = delete;
    SocketBase& operator=(const SocketBase&) = delete;

public:
    /** 初始化，不要放到构造函数里面
    @parma [in] type socket数据传输类型
    @parma [in] ipProto 协议
    return 是否成功
    */
    virtual bool Init(SocketType type, IpProtocolType ipProto);

    /** 清理资源
    return 是否成功
    */
    bool UnInit();

    /** 发送消息 当msg大于大约 1K时候返回的值可能不等于msg的值（一次性发送不了）
        pToSocket::IsValidSocket返回false代表无连接的数据报[比如UDP]
    @param [in] toSocket 消息接受方
    @param [in] msg 希望发送的消息
    @return 成功返回发送的个数，失败返回SOCKET_ERROR
    */
    virtual int SendMsg(const SocketNode& toSocket, const std::string & msg);

    /** 接收消息
        pFromSocket::IsValidSocket返回false代表无连接的数据报[比如UDP]，此时pFromSocket将保存发送方的SOCKADDR
    @param [in] fromSocket 消息发送方
    @param [out] msg 收到的消息
    @return 成功返回接受的个数，失败返回SOCKET_ERROR
    */
    virtual int RcvMsg(SocketNode& fromSocket, std::string & msg);

public:
    /** 获得m_socketNode
    @return socket 数据信息
    */
    inline SocketNode& GetSocketNode()
    {
        return m_socketNode;
    }

    /** 获得连接流的另一端信息，很显然类似UDP的链接不需要使用这个
    @param [out] fromSocket 另一端信息
    return 是否成功
    */
    bool GetPeerName(SocketNode& fromSocket);

private:
    /** socket 数据信息
    */
    SocketNode m_socketNode;

    /** 缓存大小
    */
    unsigned int m_buffSize;
};

#endif //__ISOCKET_H_
