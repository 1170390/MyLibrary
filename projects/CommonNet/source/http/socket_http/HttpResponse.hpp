
#ifndef __HTTP_RESPONSE_H_
#define __HTTP_RESPONSE_H_

#include "HttpCommon.hpp"
#include "string_utils/string_utils_s.hpp"

/** �������ظ������ཫ�ظ���ŵ������棬����ֻ��ͷ�����д���
*/
class HttpResponse :
    public HttpAssister
{
public:

    HttpResponse():
        m_statusCode(0)
    {

    }

    /** ���ûظ�ͷ��
    @param [in] responseHead �ظ�ͷ��
    */
    void SetHead(const DogStringA& responseHead)
    {
        const DogCharA* beg = responseHead.c_str();

        // HTTP/1.1 200 OK
        const DogCharA* lf = stringutils_s::GetLine(beg);

        if (lf - beg <= 2)
        {
            return;
        }

        DogStringA line(beg, lf - beg - 2);
        std::vector<DogStringA> out;
        stringutils_s::StrSplit(line.c_str(), " ", out);

        if (out.size() != 3)
        {
            return;
        }

        m_statusCode = ::atoi(out[1].c_str());
        if (0 == m_statusCode)
        {
            return;
        }

        m_rawHead = line;
        beg = lf;

        while (1)
        {
            const DogCharA* lf = stringutils_s::GetLine(beg);

            if (*lf == 0)
            {
                break;
            }

            if (lf - beg <= 2)
            {
                continue;
            }

            DogStringA line(beg, lf - beg - 2);
            beg = lf;
            const DogCharA* sp = stringutils_s::StrFind(line.c_str(), ": ", 1);

            if (*sp == 0)
            {
                continue;
            }

            Set(DogStringA(line.c_str(), sp - line.c_str()), sp + 2);
        }

    }

    /** ���״̬��
    @return ״̬��
    */
    inline int GetStatusCode()
    {
        return m_statusCode;
    }

    /** ���ͷ��ԭʼ��Ϣ
    @return ͷ��ԭʼ��Ϣ
    */
    inline DogStringA& GetRawHead()
    {
        return m_rawHead;
    }

    /** ������ĳ���
    @reutrn ���ĳ���
    */
    inline s64 GetContentLength()
    {
        auto& it = m_keyVal.find("Content-Length");

        if (it == m_keyVal.end())
        {
            return 0;
        }

        return ::atoll(it->second.c_str());
    }

private:
    /** ״̬��
    */
    int m_statusCode;

    /** ԭʼͷ��
    */
    DogStringA m_rawHead;
};

#endif //__HTTP_RESPONSE_H_
