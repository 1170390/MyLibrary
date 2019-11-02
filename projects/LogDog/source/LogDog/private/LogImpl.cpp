
#include "../ILog.h"
#include "../LogDog.h"
#include "../LogDogDef.h"

#include <tchar.h>
#include <time.h>

ILog::ILog()
{
}

ILog::~ILog()
{

}

void ILog::DoTask()
{
    Log();
}

ISimpleLog::ISimpleLog(LogDogConfigLevel level, const DogString& logStr) :
    m_level(level),
    m_logStr(logStr)
{
}

ISimpleLog::~ISimpleLog()
{
}

void ISimpleLog::Log()
{
    std::shared_ptr<LogDogConfig> spConfig = Singleton<LogDog>::GetInstance().GetConfig();

    // ÿ�ζ�Ҫ�������¼���
    spConfig->TryReload();

    // ��������ļ�����ʧ�ܵĻ�
    if (spConfig->GetErrorCode() != LogDogConfigErrorCode::LDC_NO_ERROR)
    {
        return;
    }

    if (spConfig->GetInt32(_DogT("level")) < (int)m_level)
    {
        return;
    }

    DogString logFormated;

    if (!MakeLogStr(logFormated) || logFormated.empty())
    {
        return;
    }

    for (auto it : m_executors)
    {
        assert(it != NULL);
        it->Executor(logFormated);
    }
}

void ISimpleLog::PushExecutor(const std::shared_ptr<ILogExecutor>& executor)
{
    m_executors.push_back(executor);
}

SimpleLog::SimpleLog(LogDogConfigLevel level, const DogString& logStr) :
    ISimpleLog(level, logStr)
{

}

SimpleLog::~SimpleLog()
{
}

bool SimpleLog::MakeLogStr(DogString & outLogStr)
{
    // ��������
    __time64_t long_time;
    ::_time64(&long_time);
    struct tm nowtime;
    ::_localtime64_s(&nowtime, &long_time);
    DogChar date[24] = { 0 };
    ::_stprintf_s(date, _DogT("[%04d-%02d-%02d %02d:%02d:%02d "),
                  nowtime.tm_year + 1900,
                  nowtime.tm_mon + 1,
                  nowtime.tm_mday,
                  nowtime.tm_hour,
                  nowtime.tm_min,
                  nowtime.tm_sec);

    outLogStr = date;

    // ���ϵȼ�����
    switch (m_level)
    {
    case LogDogConfigLevel::LDC_LEVEL_0:
        outLogStr += _DogT("CRASH");
        break;
    case LogDogConfigLevel::LDC_LEVEL_1:
        outLogStr += _DogT("VERY_SERIOUS_ERROR");
        break;
    case LogDogConfigLevel::LDC_LEVEL_2:
        outLogStr += _DogT("SERIOUS_ERROR");
        break;
    case LogDogConfigLevel::LDC_LEVEL_3:
        outLogStr += _DogT("ASSERT");
        break;
    case LogDogConfigLevel::LDC_LEVEL_4:
        outLogStr += _DogT("WARNING");
        break;
    case LogDogConfigLevel::LDC_LEVEL_5:
        outLogStr += _DogT("INFO");
        break;
    case LogDogConfigLevel::LDC_LEVEL_6:
        outLogStr += _DogT("DEBUG");
        break;
    default:
        break;
    }
    outLogStr += _DogT("] ");

    // ������־,�����־β���ǻ��з��ţ�ȥ��
    if (m_logStr.length() > 0)
    {
        if (m_logStr[m_logStr.length() - 1] == _DogT('\n'))
        {
            m_logStr[m_logStr.length() - 1] = 0;
        }
    }

    if (m_logStr.length() > 1)
    {
        if (m_logStr[m_logStr.length() - 2] == _DogT('\r'))
        {
            m_logStr[m_logStr.length() - 2] = 0;
        }
    }

    m_logStr = m_logStr.c_str();
    outLogStr += m_logStr;
    outLogStr += _DogT(" \r\n");
    return true;
}
