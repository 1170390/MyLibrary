#pragma once

#include "string_utils_c.h"

namespace utilstest
{
    using namespace stringutils_c;

    static void Test_stringutils0()
    {
        strwildcard("cabcd", "*a", true);
    }

    static void Test_stringutils1()
    {
        bool b = strwildcard("΢��", "*ע", true);
        b = 0 != strstr("΢��", "΢��", true);
    }
}
