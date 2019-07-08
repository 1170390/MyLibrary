#ifndef __STRING_UTILS_S_H_
#define __STRING_UTILS_S_H_

#include <string>
#include <vector>
#include <tchar.h>

// ��string ���� wstring
#define MULTI_CHAR

#ifdef MULTI_CHAR
#define TString std::string
#define TChar char
#define T(x)      x
#else
#define TString std::wstring
#define TChar wchar_t
#define T(x)      L ## x
#endif // MULTI_CHAR

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
    bool StrSplit(const TString& raw, TChar& spliter, std::vector<TString>& out);
}

#endif // __STRING_UTILS_S_H_
