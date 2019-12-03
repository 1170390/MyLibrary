
#ifndef _SOCKET_HTTP_CLIENT_H__
#define _SOCKET_HTTP_CLIENT_H__

#include "noncopyable/noncopyable.h"
#include "stream/IDogStream.h"
#include "timer_recorder/timer_recorder.h"
#include "typedef/DogInterger.h"
#include "typedef/DogString.h"
#include "Url/DogUrl.h"

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

/** socket ��װ������ָ��
*/
class SocketBase;
using SPSocketClient = std::shared_ptr<SocketBase>;

/** http��
*/
class SocketHttpClient:
    public NonCopyable
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
    @param [in] method ���󷽷�
    @return �Ƿ�ɹ�,�ú�������ȥ��鷵�������Ƿ���Ч���Ƿ�������ֻҪ�����ݷ��أ���Ϊtrue
    */
    bool MakeRequest(const DogStringA& urlStr, const DogStringA& method);

    /** ����socket client
    @param [in] urlStr
    @param [in] method ���󷽷�
    @param [out] url ����ɹ��Ļ����ص�url
    @return ������socket����ʧ�ܵĻ�Ϊ��
    */
    SPSocketClient CreateSocketClient(const DogStringA& urlStr, const DogStringA& method, DogUrl& url);

    /** ƴ������ͷ
    @param [in] url
    @param [method] method ���󷽷�
    @param [out] strHttpHead���
    */
    void CreateHead(const DogUrl& url, const DogStringA& method, DogStringA& strHttpHead);

    /** ��������
    @param [in] spClient tcp����������Ч��������жϣ������ڲ�����assert
    @param [in] gTimer ȫ�ֳ�ʱ
    @param [out] head ���ܵ�ͷ����������m_downLoadLoadStream�з���
    @return �Ƿ�ɹ�
    */
    bool RecvResponse(SPSocketClient spClient, TimerRecorder& gTimer, DogStringA& head);

    /** ����body��ĿǰֻPOST����
    @param [in] spClient tcp����������Ч��������жϣ������ڲ�����assert
    @param [in] gTimerȫ�ֳ�ʱ
    @return �Ƿ�ɹ�
    */
    bool SendBody(SPSocketClient spClient, TimerRecorder& gTimer);

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

    /** ֹͣ����
    */
    void Stop();

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

    /** �Ƿ�ֹͣ
    */
    bool m_stop;
};

#endif // _SOCKET_HTTP_CLIENT_H__
