
#include "SocketHttpClient.h"
#include "socket_common/SocketUtils.h"
#include "socket_tcp/SocketTcpClient.h"

#include <assert.h>

/** ���ݳ�ʱʱ�� (ms)
*/
static int DATA_TIME_OUT = 15000;

SocketHttpClient::SocketHttpClient():
    m_gTimeOut(0),
    m_dataTimeOut(DATA_TIME_OUT)
{
}

SocketHttpClient::~SocketHttpClient()
{
}

bool SocketHttpClient::Get(const DogStringA& urlStr)
{
    return MakeRequest(urlStr, "GET");
}

bool SocketHttpClient::Post(const DogStringA& urlStr)
{
    return MakeRequest(urlStr, "POST");
}

bool SocketHttpClient::MakeRequest(const DogStringA& urlStr, const DogStringA& method)
{
    // ��ʱ��¼
    TimerRecorder gTimer;

    // ����url������socket��װ��
    DogUrl url;
    SPSocketClient spClient = CreateSocketClient(urlStr, method, url);

    if (spClient == NULL)
    {
        return false;
    }

    // ���SSL?
    DogCharA s = url.m_scheme[url.m_scheme.length() - 1];
    bool isSafe = (s == 's' || s == 'S');

    // ����ͷ��
    DogStringA strHttpHead;
    CreateHead(url, method, strHttpHead);

    if (::send(spClient->GetSocketBean().GetSocket(), strHttpHead.c_str(), (int)strHttpHead.length(), 0) 
        != strHttpHead.length())
    {
        return false;
    }

    // ����body
    if (method == "POST" && m_upLoadStream != NULL)
    {
        if (!SendBody(spClient, gTimer))
        {
            return false;
        }
    }

    // ����
    DogStringA responseHead;
    if (!RecvResponse(spClient, gTimer, responseHead))
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

void SocketHttpClient::CreateHead(const DogUrl& url, const DogStringA& method, DogStringA& strHttpHead)
{
    // ƴ��
    strHttpHead = method;
    strHttpHead.append(" ");
    strHttpHead.append(url.m_path);

    if (url.m_query.length() > 0)
    {
        strHttpHead.append("?");
        strHttpHead.append(url.m_query);
    }

    if (url.m_fragment.length() > 0)
    {
        strHttpHead.append("#");
        strHttpHead.append(url.m_fragment);
    }

    strHttpHead.append(" ");
    DogStringA upperScheme = url.m_scheme;
    std::transform(upperScheme.begin(), upperScheme.end(), upperScheme.begin(), ::toupper);
    strHttpHead.append(upperScheme);
    strHttpHead.append("/1.1\r\n");

    //strHttpHead.append("Accept: */*\r\n");
    //strHttpHead.append("Accept-Language: cn\r\n");
    //strHttpHead.append("User-Agent: Mozilla/4.0\r\n");
    strHttpHead.append("Host: ");
    strHttpHead.append(url.m_host);
    strHttpHead.append("\r\n");
    strHttpHead.append("Connection: close\r\n");
    strHttpHead.append("Keep-Alive: timeout=5,max=500\r\n");

    if (method == "POST" && m_upLoadStream != NULL)
    {
        char len[64] = {0};
        ::sprintf_s(len, "%lld", m_upLoadStream->Size());
        strHttpHead.append("Content-Type: */*\r\n");
        strHttpHead.append("Content-Length: ");
        strHttpHead.append(len);
    }

    strHttpHead.append("\r\n\r\n");
}

bool SocketHttpClient::RecvResponse(SPSocketClient spClient, TimerRecorder& gTimer, DogStringA& head)
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

    head.clear();
    head.reserve(1024);

    // �Ѿ����ܵĴ�С
    u64 hasGetSize = 0;

    // �ܴ�С
    u64 allSize = 0;

    // ��¼��һ�����ݵ�����ʱ��
    TimerRecorder dataTimer;

    while (true)
    {
        if (m_gTimeOut > 0)
        {
            if (gTimer.GetTimePass() >= m_gTimeOut)
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

                    // �����µ����
                    rcvSize -= i;
                    ::memcpy(pBuff, pBuff + i, rcvSize);
                    ::memset(pBuff + rcvSize, 0, buffSize - rcvSize);
                }
            }

            hasGetSize += rcvSize;
            if (m_downLoadPercentCallBack)
            {
                m_downLoadPercentCallBack(hasGetSize, allSize);
            }

            if (m_downLoadLoadStream)
            {
                m_downLoadLoadStream->Write(pBuff, rcvSize);
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

bool SocketHttpClient::SendBody(SPSocketClient spClient, TimerRecorder& gTimer)
{
    assert(spClient != NULL && spClient->GetSocketBean().IsValidSocket());
    unsigned int buffSize = spClient->GetBuffSize();
    u8* pBuff = new (std::nothrow) u8[buffSize];
    SOCKET sock = spClient->GetSocketBean().GetSocket();

    if (NULL == pBuff)
    {
        return false;
    }

    // ��¼��һ�����ݵ�����ʱ��
    TimerRecorder dataTimer;
    bool success = true;

    while (true)
    {
        if (m_gTimeOut > 0)
        {
            if (gTimer.GetTimePass() >= m_gTimeOut)
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

        s32 readed = m_upLoadStream->Read(pBuff, buffSize);

        if (readed == 0)
        {
            break;
        }

        if (::send(sock, (char*)pBuff, (int)readed, 0) != readed)
        {
            success = false;
            break;
        }

        dataTimer.ReSet();
    }

    return success;
}

void SocketHttpClient::SetUploadPercentCallBack(const DogPercentCallBack& callback)
{
    m_upLoadPercentCallBack = callback;
}

void SocketHttpClient::SetDownloadPercentCallBack(const DogPercentCallBack& callback)
{
    m_downLoadPercentCallBack = callback;
}

void SocketHttpClient::SetUploadStream(const SPDogStream& stream)
{
    m_upLoadStream = stream;
}

void SocketHttpClient::SetDownloadStream(const SPDogStream& stream)
{
    m_downLoadLoadStream = stream;
}

void SocketHttpClient::SetGTimeOut(u32 timeOut)
{
    m_gTimeOut = timeOut;
}

void SocketHttpClient::SetDataTimeOut(u32 timeOut)
{
    m_dataTimeOut = timeOut;
}
