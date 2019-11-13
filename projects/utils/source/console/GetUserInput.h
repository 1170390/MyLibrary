
#ifndef __GETUSERINPUT_H_
#define __GETUSERINPUT_H_

#include "color_print.h"
#include "typedef/DogString.h"

/** �û�����һ�У��س�����
@param [out] line �û������һ��
*/
inline void GetUserInputLineW(DogStringW& line)
{
    ColorPrintf(Gray, "input>>");
    line = L"";

    while (true)
    {
        DogCharW wc = ::getwchar();

        if (wc == L'\n')
        {
            break;
        }
        else
        {
            line.append(1, wc);
        }
    }
}

/** �û�����һ�У��س�����
@param [out] line �û������һ��
*/
inline void GetUserInputLineA(DogStringA& line)
{
    ColorPrintf(Gray, "input>>");
    line = "";

    while (true)
    {
        DogCharA c = ::getchar();

        if (c == '\n')
        {
            break;
        }
        else
        {
            line.append(1, c);
        }
    }
}

#ifdef _UNICODE
#define GetUserInputLine GetUserInputLineW
#else
#define GetUserInputLine GetUserInputLineA
#endif // 


#endif //__GETUSERINPUT_H_
