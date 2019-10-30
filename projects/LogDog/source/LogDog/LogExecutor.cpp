
#include "dir_utils/dir_utils.h"
#include "LogExecutor.h"
#include "stream/FileStream.h"

#include <tchar.h>
#include <time.h>
#include <Windows.h >

//////////////////////////////////////////////////////////////////////////
///DumpToFileExecutor{
DumpToFileExecutor::DumpToFileExecutor()
{
}

bool DumpToFileExecutor::Executor(const DogString& logStr, const std::shared_ptr <LogDogConfig>& config)
{
    const LogDogConfigEntry& configEntry = config->GetLogDogConfigEntry();

    // ��Ҫд�ļ�
    if (!configEntry.m_isNeedDmpToFile)
    {
        return false;
    }

    DogString baseDirBath = configEntry.m_path;

    // ȥ���ļ���
    for (size_t i = baseDirBath.length() - 1; i >= 0; --i)
    {
        if (baseDirBath[i] == _DogT('\\') || baseDirBath[i] == _DogT('/'))
        {
            baseDirBath[i] = 0;

            // resize~
            baseDirBath = baseDirBath.c_str();
            break;
        }
    }

    baseDirBath += _DogT("\\log\\");
    baseDirBath += configEntry.m_name;
    baseDirBath += _DogT("\\");
    DogString path = GetAndCreateLogFile(logStr.length(), baseDirBath);
    FileStream fileStream(path.c_str());
    fileStream.WriteW((const u16*)logStr.c_str(), logStr.length());
    return true;
}

DogString DumpToFileExecutor::GetAndCreateLogFile(size_t logLen, const DogString& baseDirBath)
{
    if (baseDirBath.empty())
    {
        return _DogT("");
    }

    // ��ó���ģ������
    DogChar buff[_MAX_ENV] = {0};

    if (::GetModuleFileName(0, buff, _MAX_ENV) == 0)
    {
        return _DogT("");
    }

    int index = 0;
    DogChar tmp = buff[index];
    DogChar* fileName = NULL;

    while (tmp != 0)
    {
        if (tmp == _DogT('\\') || tmp == _DogT('/'))
        {
            fileName = buff + index + 1;
        }

        tmp = buff[++index];
    }

    DogString logPath = baseDirBath;
    logPath += fileName;
    logPath += _DogT('\\');

    // ��������
    __time64_t long_time;
    ::_time64(&long_time);
    struct tm nowtime;
    ::_localtime64_s(&nowtime, &long_time);
    DogChar data[12] = {0};
    ::_stprintf_s(data, _DogT("%04d-%02d-%02d\\"), nowtime.tm_year + 1900, nowtime.tm_mon + 1, nowtime.tm_mday);
    logPath += data;

    // ����Ŀ¼
    if (!dir_uitls::CreateDirEx(logPath))
    {
        return _DogT("");
    }

    // �����ļ����ƣ�Сʱ-0��
    DogChar hour[13] = {0};
    ::_stprintf_s(hour, _DogT("%02dh-%04d.log"), nowtime.tm_hour, 0);
    logPath += hour;

    // ��鲢�����ļ�
    if (!CheckFileSizeAndCreate(logLen, logPath))
    {
        return _DogT("");
    }

    return logPath;
}

bool DumpToFileExecutor::CheckFileSizeAndCreate(size_t logLen, DogString& filePath)
{
    DogChar* buff = (DogChar*)filePath.c_str();
    buff += filePath.length() - 8;

    while (true)
    {
        FileStream fileStream(filePath.c_str());

        if (fileStream.Size() + logLen < g_file_size)
        {
            break;
        }

        if (::_tcscmp(buff, _DogT("9999")) == 0 || !StrInc(buff, 4))
        {
            break;
        }
    }

    return true;
}

bool DumpToFileExecutor::StrInc(DogChar * buff, int len)
{
    // ��λ
    int inc = 0;
    for (int i = len - 1; i >= 0; --i)
    {
        if (buff[i] > _DogT('9') || buff[i] < _DogT('0'))
        {
            return false;
        }

        if (inc == 1)
        {
            if (buff[i] == _DogT('9'))
            {
                buff[i] = _DogT('0');
            }
            else
            {
                buff[i] += 1;
                inc = 0;
            }
        }
        else
        {
            if (buff[i] == _DogT('9'))
            {
                buff[i] = _DogT('0');
                inc = 1;
            }
            else
            {
                buff[i] += 1;
            }
        }

        if (inc == 0)
        {
            break;
        }
    }

    return true;
}
///DumpToFileExecutor}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///UpLoadExecutor{
bool UpLoadExecutor::Executor(const DogString & logStr, const std::shared_ptr <LogDogConfig>& config)
{
    const LogDogConfigEntry& configEntry = config->GetLogDogConfigEntry();

    // ��Ҫ�ϴ�
    if (configEntry.m_isNeedUpload)
    {
        UpLoadExecutor uploadExecutor;
    }

    return false;
}
///UpLoadExecutor}
//////////////////////////////////////////////////////////////////////////

