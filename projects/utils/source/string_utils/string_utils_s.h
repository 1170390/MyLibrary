#ifndef __STRING_UTILS_S_H_
#define __STRING_UTILS_S_H_

#include "typedef/DogString.h"
#include <vector>

/** std::string �ַ�������
*/
namespace stringutils_s
{
    /** �ָ��ַ���
    @param [in] raw Դ
    @param [in] spliter �ָ�����
    @param [out] out ���
    @return �Ƿ�ɹ�
    */
    template <class tc>
    bool StrSplit(const DongStringT<tc>& raw, tc spliter, std::vector<DongStringT<tc> >& out)
    {
        tc c = 0;
        DongStringT<tc> line;

        for (size_t i = 0; i < raw.length(); ++i)
        {
            c = raw[i];

            if (c == spliter)
            {
                out.push_back(line);
                line.clear();
            }
            else
            {
                line.append(1, c);
            }
        }

        out.push_back(line);
        return true;
    }

    /** �ַ����������
    */
    template<class tc>
    struct ParseResult
    {
    public:
        /** �ôε������
        */
        DongStringT<tc> value;

        /** �´ο�ʼλ��
        */
        const tc* ch;
    };

    template<class tc, class F>
    static inline ParseResult<tc> ParseUntil(const tc* str, F func)
    {
        ParseResult<tc> result{};
        tc const* ch = str;
        for (; *ch && !func(*ch); ++ch);
        result.value = DongStringT<tc>(str, ch - str);
        result.ch = ch;
        return result;
    }

    template<class tc, class F>
    static inline ParseResult<tc> ParseWhile(const tc* str, F func)
    {
        ParseResult<tc> result{};
        tc const* ch = str;
        for (; *ch && func(*ch); ++ch);
        result.value = DongStringT<tc>(str, ch - str);
        result.ch = ch;
        return result;
    }
}

#endif // __STRING_UTILS_S_H_
