
#ifndef __DOGURL_H_
#define __DOGURL_H_

#include "typedef/DogString.h"

/** url
һ����utf-8����
scheme:[//[user[:password]@]host[:port]] [/path] [?query] [#fragment]
*/
struct DogUrl
{
    /** ָ���Ͳ�ʹ�õ�Э��(���磺http, https, ftp)
    */
    DogStringA m_scheme;

    /** �û�����
    @note: [��ʡ��]
    */
    DogStringA m_user;

    /** ����
    @note: [��ʡ��]
    */
    DogStringA m_password;

    /** ��������ͨ��Ϊ��������ʱΪIP��ַ
    */
    DogStringA m_host;

    /** �˿ڡ������ַ�ʽ��ʾ,Ĭ��ֵ��:80��
    @note: [��ʡ��]
    */
    unsigned int m_port = 0;

    /** ·�����ԡ�/���ַ�����·���е�ÿһ��Ŀ¼����
    @note: [��ʡ��]
    */
    DogStringA m_path;

    /** ��ѯ��GETģʽ�Ĵ���������ԡ�?���ַ�Ϊ��㣬ÿ�������ԡ�&�����������ԡ�=���ֿ��������������ݣ�ͨ����UTF8��URL���룬�ܿ��ַ���ͻ������
    @note: [��ʡ��]
    */
    DogStringA m_query;

    /** Ƭ�Ρ��ԡ�#���ַ�Ϊ���
    @note: [��ʡ��]
    */
    DogStringA m_fragment;

    /** ���캯��
    */
    DogUrl()
    {

    }

    /** ���캯��
    @param [in] url �����url;
    */
    DogUrl(const DogStringA& constUrl)
    {
        Init(constUrl);
    }

    /** ��ʼ��
    @param [in] url �����url;
    */
    void Init(const DogStringA& constUrl)
    {
        // �� \ ת��Ϊ /
        DogStringA url = constUrl;
        for (size_t i = 0; i < url.length(); ++i)
        {
            if (url[i] == '\\')
            {
                url[i] = '/';
            }
        }

        size_t index = 0;
        size_t len = url.length();

        // ��scheme
        for (size_t i = index; i < len; ++i)
        {
            if (url[i] == ':')
            {
                m_scheme = url.substr(index, i - index);
                index = i + 1;
                break;
            }
        }

        if (m_scheme.empty())
        {
            return;
        }

        // �̶� //
        if (index + 1 >= len ||
            url[index++] != '/' ||
            url[index++] != '/')
        {
            return;
        }

        // [user[:password]@]host[:port] ��[/path] [?query] [#fragment]��
        // �ҵ���չ���� ��/ ? #��
        size_t hostPortEndIndex = len - 1;
        for (size_t i = index; i < len; ++i)
        {
            if (url[i] == '/' || url[i] == '?' || url[i] == '#')
            {
                hostPortEndIndex = i - 1;
                break;
            }
        }

        // ����Ϊ0
        if (hostPortEndIndex < index)
        {
            return;
        }

        // �ҵ�@���ţ�˵�����û�������
        {
            size_t userPswEndIndex = index - 1;
            for (size_t i = index; i <= hostPortEndIndex; ++i)
            {
                if (url[i] == '@')
                {
                    userPswEndIndex = i - 1;

                    // ���Ȳ�Ϊ0
                    if (userPswEndIndex >= index)
                    {
                        // Ѱ�� ��:��
                        size_t userEndIndex = userPswEndIndex;
                        for (size_t j = index; j <= userPswEndIndex; ++j)
                        {
                            if (url[j] == ':')
                            {
                                userEndIndex = j - 1;
                                break;
                            }
                        }

                        m_user = url.substr(index, userEndIndex - index + 1);

                        if (userEndIndex < userPswEndIndex - 2)
                        {
                            m_password = url.substr(userEndIndex + 2, userPswEndIndex - userEndIndex - 1);
                        }
                    }

                    index = userPswEndIndex + 2;
                    break;
                }
            }
        }

        // host �˿�
        {
            if (index <= hostPortEndIndex)
            {
                // Ѱ�� ��:��
                size_t hostEndIndex = hostPortEndIndex;
                for (size_t j = index; j <= hostPortEndIndex; ++j)
                {
                    if (url[j] == ':')
                    {
                        hostEndIndex = j - 1;
                        break;
                    }
                }

                // ����Ϊ0
                if (hostEndIndex < index)
                {
                    return;
                }

                m_host = url.substr(index, hostEndIndex - index + 1);

                if (hostEndIndex < hostPortEndIndex - 2)
                {
                    m_port = ::atoi(url.substr(hostEndIndex + 2, hostPortEndIndex - hostEndIndex - 1).c_str());
                }

                if (m_port == 0)
                {
                    m_port = 80;
                }

                index = hostPortEndIndex + 2;
            }
        }

        while (index < len)
        {
            // Ѱ����һ����չ����
            size_t extendEndIndex = len - 1;
            for (size_t i = index; i < len; ++i)
            {
                if (url[i] == '/' || url[i] == '?' || url[i] == '#')
                {
                    extendEndIndex = i - 1;
                    break;
                }
            }

            // �����һ�������� "/"������Ѱ����һ����չ���� ��? #��
            if (url[index - 1] == '/')
            {
                extendEndIndex = len - 1;
                for (size_t i = index; i < len; ++i)
                {
                    if (url[i] == '?' || url[i] == '#')
                    {
                        extendEndIndex = i - 1;
                        break;
                    }
                }

                m_path = url.substr(index, extendEndIndex - index + 1);
            }

            // �����һ�������� "?" ��ô���m_query
            else if (url[index - 1] == '?')
            {
                m_query = url.substr(index, extendEndIndex - index + 1);
            }

            // �����һ�������� "#" ��ô���m_fragment
            else if (url[index - 1] == '#')
            {
                m_fragment = url.substr(index, extendEndIndex - index + 1);
            }

            index = extendEndIndex + 2;
        }
    }

    /** url �Ƿ���Ч
    @return �Ƿ���Ч
    */
    bool IsValid()
    {
        return !m_scheme.empty() && m_port != 0 && !m_host.empty();
    }
};

#endif //__DOGURL_H_
