
#ifndef _SOCKET_HTTP_CLIENT_H__
#define _SOCKET_HTTP_CLIENT_H__

#include "socket_tcp/SocketTcpClient.h"
#include "stream/IDogStream.h"
#include "typedef/DogInterger.h"

#include <functional>
#include <memory>

/** ���Ȼص�����
    @functional:
        @param [in] handledSize �Ѿ�������ܴ�С
        @param [in] allSize �ܴ�С
        @return ����falseʱ�򣬽������̽���
*/
using  DogPercentCallBack = std::function<bool(const u64 handledSize, const u64 allSize)>;

/** ��������ָ��
*/
using SPDogStream = std::shared_ptr<IDogStream>;

class SocketHttpClient :
    public SocketTcpClient
{
public:
    /** ���캯��
    */
    SocketHttpClient();

    /** ��������
    */
    ~SocketHttpClient();

public:
    /** get ����
    @param [in] urlStr 
    */
    bool Get(const DogStringA& urlStr);

    /** post ����
    @param [in] urlStr
    */
    bool Post(const DogStringA& urlStr);

public:
    /** �������ؽ��Ȼص�
    @param [in] callback: �ϴ����Ȼص�
    */
    void SetUploadPercentCallBack(const DogPercentCallBack& callback);

    /** �������ؽ��Ȼص�
    @param [in] callback: ���ؽ��Ȼص�
    */
    void SetDownloadPercentCallBack(const DogPercentCallBack& callback);

    /** �����ϴ���
    @param [in] stream: �ϴ���
    */
    void SetUploadStream(const SPDogStream& stream);

    /** ����������
    @param [in] stream: ������
    */
    void SetDownloadStream(const SPDogStream& stream);

protected:
    /** �ϴ����Ȼص�
    */
    DogPercentCallBack m_upLoadPercentCallBack;

    /** ���ؽ��Ȼص�
    */
    DogPercentCallBack m_downLoadPercentCallBack;

    /** �ϴ���
    */
    SPDogStream m_upLoadStream;

    /** ������
    */
    SPDogStream m_downLoadLoadStream;
};


#endif // _SOCKET_HTTP_CLIENT_H__
