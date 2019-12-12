#include "TestLogDog.h"
#include "LogDog/LogDogDef.h"

#include <windows.h>

#include "AutoLib.h"
#pragma comment(lib, LIBDIR "LogDog.lib")

void LogDog()
{
    LOG_INIT(_DogT("./test.ini"), _DogT("����"));

    /** ������Ϣ
    */
    LOG_DEBUG(_DogT("test1"));
    LOG_DEBUG(_DogT("test2"));
    LOG_WARNING(_DogT("����"));
    LOG_ASSERT(_DogT("����"));
    LOG_SERIOUS_ERROR(_DogT("���ش���"));
    LOG_VERY_SERIOUS_ERROR(_DogT("�ǳ����ش���"));
    LOG_CRASH(_DogT("����"));

    while (1)
    {
        ::Sleep(10);
    }

    LOG_UNINIT();
}
