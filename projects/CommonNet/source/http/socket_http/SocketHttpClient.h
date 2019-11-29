
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

class SocketHttpClient
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
    @return �Ƿ�ɹ�
    */
    bool Get(const DogStringA& urlStr);

    /** post ����
    @param [in] urlStr
    @return �Ƿ�ɹ�
    */
    bool Post(const DogStringA& urlStr);

private:
    /** ����
    @param [in] urlStr
    @param [method] ���󷽷�
    @return �Ƿ�ɹ�,�ú�������ȥ��鷵�������Ƿ���Ч���Ƿ�������ֻҪ�����ݷ��أ���Ϊtrue
    */
    bool MakeRequest(const DogStringA& urlStr, const DogStringA& method);

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

    /** ���Գ�ʱʱ�䣬�ӽ��뺯����ʼ�����˳���������ȴ�ʱ�䣬����һ�����Գ�ʱʱ�䣬����㲻ϣ�����ܵ�����ֻ����һ��ͽ����ˣ�������Ϊ0
    @note: Ĭ��0
    @note: Ϊ0ʱ��Ϊ������ʱ
    @param [in] timeOut: ��ʱʱ�� (ms)
    */
    void SetGTimeOut(u32 timeOut);

    /** ���ݳ�ʱʱ�䣬ָ������һ�����ݵ���һ������֮�����ȴ�ʱ��
    @note: Ĭ��15000ms
    @note: Ϊ0ʱ��Ϊ������ʱ
    @param [in] timeOut: ��ʱʱ�� (ms)
    */
    void SetDataTimeOut(u32 timeOut);

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

    /** (ms) ���Գ�ʱʱ�䣬�ӽ��뺯����ʼ�����˳���������ȴ�ʱ�䣬����һ�����Գ�ʱʱ�䣬����㲻ϣ�����ܵ�����ֻ����һ��ͽ����ˣ�������Ϊ0
    @note: Ϊ0ʱ��Ϊ������ʱ
    */
    u32 m_gTimeOut;

    /** (ms) ���ݳ�ʱʱ�䣬ָ������һ�����ݵ���һ������֮�����ȴ�ʱ��
    @note: ��Ȼ�������ȼ�����m_gTimeOut
    */
    u32 m_dataTimeOut;
};


#endif // _SOCKET_HTTP_CLIENT_H__
