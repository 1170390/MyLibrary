
#include "LogImpl.h"
#include "LogExecutor.h"

#include <windows.h>

//////////////////////////////////////////////////////////////////////////
///DecreasePriority{
void DecreasePriority::Log()
{
    ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_BELOW_NORMAL);
}
///DecreasePriority}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///SimpleLog{

void ISimpleLog::Log()
{
    if (m_spConfig == NULL)
    {
        return;
    }

    // ÿ�ζ�Ҫ�������¼���
    m_spConfig->TryReload();

    // ��������ļ�����ʧ�ܵĻ�
    if (m_spConfig->GetErrorCode() != LogDogConfigErrorCode::LDC_NO_ERROR)
    {
        return;
    }

    LogDogConfigEntry& configEntry = m_spConfig->GetLogDogConfigEntry();

    if (configEntry.m_level < m_level)
    {
        return;
    }

    DogString logFormated;

    if (!MakeLogStr(logFormated) || logFormated.empty())
    {
        return;
    }

    // ��Ҫд�ļ�
    if (configEntry.m_isNeedDmpToFile)
    {
        DogString path = configEntry.m_path;
        path += _DogT("\\");
        path += configEntry.m_name;
        DumpToFileExecutor fileExecutor(path);
        fileExecutor.Executor(logFormated);
    }

    // ��Ҫ�ϴ�
    if (configEntry.m_isNeedUpload)
    {
        UpLoadExecutor uploadExecutor;
        uploadExecutor.Executor(logFormated);
    }
}
///SimpleLog}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///SimpleLog{

SimpleLog::SimpleLog(const DogString& logStr) :
    m_logStr(logStr)
{

}

SimpleLog::~SimpleLog()
{

}

bool SimpleLog::MakeLogStr(DogString& outLogStr)
{
    // ��Ҫ��m_spConfig�пգ���ΪԼ�����пղ����ڵ���ǰ
    LogDogConfigEntry& configEntry = m_spConfig->GetLogDogConfigEntry();
    
    switch (configEntry.m_level)
    {
    case LogDogConfigLevel::LDC_LEVEL_0:
        break;
    case LogDogConfigLevel::LDC_LEVEL_1:
        break;
    case LogDogConfigLevel::LDC_LEVEL_2:
        break;
    case LogDogConfigLevel::LDC_LEVEL_3:
        break;
    case LogDogConfigLevel::LDC_LEVEL_4:
        break;
    case LogDogConfigLevel::LDC_LEVEL_5:
        break;
    case LogDogConfigLevel::LDC_LEVEL_6:
        break;
    default:
        break;
    }

    return true;
}
///SimpleLog}
//////////////////////////////////////////////////////////////////////////

