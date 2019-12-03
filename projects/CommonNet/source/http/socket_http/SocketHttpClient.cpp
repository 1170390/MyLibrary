
#include "SocketHttpClient.h"
#include "socket_common/SocketUtils.h"
#include "socket_tcp/SocketTcpClient.h"

#include <assert.h>

/** ���ݳ�ʱʱ�� (ms)
*/
static int DATA_TIME_OUT = 15000;

SocketHttpClient::SocketHttpClient():
    m_gTimeOut(0),
    m_dataTimeOut(DATA_TIME_OUT),
    m_stop(false)
{
}

SocketHttpClient::~SocketHttpClient()
{
}

void SocketHttpClient::SetRequest(const SPRequest & request)
{
    m_spRequest = request;
}

void SocketHttpClient::SetResponse(const SPResponse& response)
{
    m_spReponse = response;
}

bool SocketHttpClient::MakeRequest()
{
    if (m_spRequest == NULL || !m_spRequest->Isvalid())
    {
        return false;
    }

    m_stop = false;

    // ��ʱ��¼
    m_gTimer.ReSet();

    // ���ip
    std::vector<DogStringA> ips;
    SocketUtils::GetIpByHostName(m_spRequest->GetUrl().m_host, ips);

    if (ips.size() == 0)
    {
        return false;
    }

    SocketTcpClient* pClient = new(std::nothrow) SocketTcpClient(ips[0], m_spRequest->GetUrl().m_port);

    if (pClient == NULL || !pClient->Connect())
    {
        return false;
    }

    SPSocketClient spClient(pClient);

    // ���SSL?
    bool isSafe = m_spRequest->SupportSSL();

    // ����ͷ��
    DogStringA strHttpHead;
    m_spRequest->Str(strHttpHead);

    if (::send(spClient->GetSocketBean().GetSocket(), strHttpHead.c_str(), (int)strHttpHead.length(), 0)
        != strHttpHead.length())
    {
        return false;
    }

    // ����body
    if (m_spRequest->GetMethod() == HttpRequest::POST && m_spRequest->GetStream() != NULL)
    {
        if (!SendBody(spClient))
        {
            return false;
        }
    }

    // ����
    DogStringA responseHead;
    if (!RecvResponse(spClient))
    {
        return false;
    }

    return true;
}

SPSocketClient SocketHttpClient::CreateSocketClient(const DogStringA& urlStr, const DogStringA& method, DogUrl& url)
{
    ParseUrl(urlStr, url);

    if (!url.IsValid())
    {
        return NULL;
    }

    // ������httpЭ��
    if (!(url.m_scheme.length() >= 4) &&
        (url.m_scheme[0] == 'h' || url.m_scheme[0] == 'H') &&
        (url.m_scheme[1] == 't' || url.m_scheme[1] == 'T') &&
        (url.m_scheme[2] == 't' || url.m_scheme[2] == 'T') &&
        (url.m_scheme[3] == 'p' || url.m_scheme[3] == 'P'))
    {
        return NULL;
    }

    DogCharA s = url.m_scheme[url.m_scheme.length() - 1];
    bool isSafe = (s == 's' || s == 'S');

    // ���ip
    std::vector<DogStringA> ips;
    SocketUtils::GetIpByHostName(url.m_host, ips);
    if (ips.size() == 0)
    {
        return NULL;
    }

    SocketTcpClient* pClient = new(std::nothrow) SocketTcpClient(ips[0], url.m_port);

    if (pClient == NULL || !pClient->Connect())
    {
        return false;
    }

    return SPSocketClient(pClient);
}

bool SocketHttpClient::RecvResponse(SPSocketClient spClient)
{
    // ����
    assert(spClient !=NULL && spClient->GetSocketBean().IsValidSocket());
    SOCKET sock = spClient->GetSocketBean().GetSocket();

    // �����첽����
    int iMode = 1;
    if (SOCKET_ERROR == ::ioctlsocket(sock, FIONBIO, (u_long FAR*)&iMode))
    {
        return false;
    }

    unsigned int buffSize = spClient->GetBuffSize();
    u8* pBuff = new (std::nothrow) u8[buffSize];

    if (NULL == pBuff)
    {
        return false;
    }

    // ��������Ӧ���𣿵���һ�����ݵ����ʱ����Ϊ��������Ӧ��
    bool hasResponse = false;
    bool success = true;

    // ��������ͷ���Ѿ�ȫ�������������
    bool hasGetAllResponseHead = false;

    DogStringA head;
    head.reserve(1024);

    // �Ѿ����ܵĴ�С
    u64 hasGetSize = 0;

    // �ܴ�С
    u64 allSize = 0;

    // ��¼��һ�����ݵ�����ʱ��
    TimerRecorder dataTimer;

    DogPercentCallBack& callback = m_spReponse->GetPercentCallBack();
    SPDogStream& stream = m_spReponse->GetStream();

    while (true)
    {
        if (m_stop)
        {
            success = false;
            break;
        }

        if (m_gTimeOut > 0)
        {
            if (m_gTimer.GetTimePass() >= m_gTimeOut)
            {
                success = false;
                break;
            }
        }

        if (m_dataTimeOut > 0)
        {
            if (dataTimer.GetTimePass() >= m_dataTimeOut)
            {
                success = false;
                break;
            }
        }

        int rcvSize = 0;
        ::memset(pBuff, 0, buffSize);
        rcvSize = ::recv(sock, (char*)pBuff, buffSize, 0);

        if (rcvSize > 0)
        {
            hasResponse = true;
            dataTimer.ReSet();

            // ����ͷ��,ͷ���� \r\n\r\n ����
            if (!hasGetAllResponseHead)
            {
                int i = 0;
                for (; i < rcvSize; ++i)
                {
                    if (pBuff[i] == '\r')
                    {
                        if (i + 3 < rcvSize &&
                            pBuff[i + 1] == '\n' &&
                            pBuff[i + 2] == '\r' &&
                            pBuff[i + 3] == '\n')
                        {
                            hasGetAllResponseHead = true;
                            i += 4;
                            head.append("\r\n\r\n");
                            break;
                        }
                    }

                    head.append(1, pBuff[i]);
                }

                if (!hasGetAllResponseHead || i >= rcvSize)
                {
                    continue;
                }
                else
                {
                    // ����ͷ��
                    m_spReponse->SetHead(head);
                    allSize = m_spReponse->GetContentLength();

                    // �����µ����
                    rcvSize -= i;
                    ::memcpy(pBuff, pBuff + i, rcvSize);
                    ::memset(pBuff + rcvSize, 0, buffSize - rcvSize);
                }
            }

            hasGetSize += rcvSize;
            if (callback)
            {
                callback(hasGetSize, allSize);
            }

            if (stream)
            {
                stream->Write(pBuff, rcvSize);
            }
        }
        else if (rcvSize == 0)
        {
            // ����0 ˵�����������
            break;
        }
        else
        {
            // ��������û����Ӧ ||
            // ��������æ WSAGetLastError �����Ǳ��߳��е�����socket�����Բ����ж��߳�����
            // �����ȵ���
            if (!hasResponse ||
                ::WSAGetLastError() == WSAEWOULDBLOCK)
            {
                ::Sleep(1);
                continue;
            }

            success = false;
            break;
        }
    }

    delete pBuff;
    pBuff = NULL;
    return success;
}

bool SocketHttpClient::SendBody(SPSocketClient spClient)
{
    assert(spClient != NULL && spClient->GetSocketBean().IsValidSocket());
    unsigned int buffSize = spClient->GetBuffSize();
    u8* pBuff = new (std::nothrow) u8[buffSize];
    SOCKET sock = spClient->GetSocketBean().GetSocket();

    if (NULL == pBuff)
    {
        return false;
    }

    DogPercentCallBack& callback = m_spRequest->GetPercentCallBack();
    SPDogStream& stream = m_spRequest->GetStream();

    // ��¼��һ�����ݵ�����ʱ��
    TimerRecorder dataTimer;
    bool success = true;
    u64 sendSize = 0;
    u64 allSize = stream->Size();
    
    while (true)
    {
        if (m_stop)
        {
            success = false;
            break;
        }

        if (m_gTimeOut > 0)
        {
            if (m_gTimer.GetTimePass() >= m_gTimeOut)
            {
                success = false;
                break;
            }
        }

        if (m_dataTimeOut > 0)
        {
            if (dataTimer.GetTimePass() >= m_dataTimeOut)
            {
                success = false;
                break;
            }
        }

        s32 readed = stream->Read(pBuff, buffSize);

        if (readed == 0)
        {
            break;
        }

        if (::send(sock, (char*)pBuff, (int)readed, 0) != readed)
        {
            success = false;
            break;
        }

        sendSize += readed;

        if (callback)
        {
            callback(sendSize, allSize);
        }

        dataTimer.ReSet();
    }

    return success;
}

void SocketHttpClient::SetGTimeOut(u32 timeOut)
{
    m_gTimeOut = timeOut;
}

void SocketHttpClient::SetDataTimeOut(u32 timeOut)
{
    m_dataTimeOut = timeOut;
}

void SocketHttpClient::Stop()
{
    m_stop = true;
}
