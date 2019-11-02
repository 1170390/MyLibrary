
#include "../LogDogConfig.h"
#include "../LogDogDef.h"

#include "init_file/init_file.h"

#include <tchar.h>

// �ļ�������״̬��ÿ10s�᳢�Լ���
#define FAILURE_TIME_PASS 10000

// �ļ�����״̬ÿ3min�᳢�Լ���
#define CUCCESS_TIME_PASS 160000

LogDogConfig::LogDogConfig(const DogString& path, const DogString& name) :
    m_path(path),
    m_name(name)
{
    ReLoad();
}

void LogDogConfig::TryReload(bool atonce/* = false*/)
{
    bool needReload = false;

    if (!atonce)
    {
        if (m_errorCode == LogDogConfigErrorCode::LDC_NO_CONFIG_FILE)
        {
            // �ļ�������״̬��ÿ10s�᳢�Լ���
            if (m_timer.GetTimePass() > FAILURE_TIME_PASS)
            {
                needReload = true;
            }
        }
        else
        {
            // �ļ�����״̬ÿ3min�᳢�Լ���
            if (m_timer.GetTimePass() > CUCCESS_TIME_PASS)
            {
                needReload = true;
            }
        }
    }
    else
    {
        needReload = true;
    }

    if (needReload)
    {
        ReLoad();
    }
}

bool LogDogConfig::GetStrVal(const DogString & key, DogString& val)
{
    auto it = m_keyValue.find(key);

    if (it == m_keyValue.end())
    {
        return false;
    }

    val = it->second;
    return true;
}

bool LogDogConfig::GetBool(const DogString & key)
{
    DogString val;

    // ��������Ϊ�Ǽ�
    if (!GetStrVal(key, val))
    {
        return false;
    }

    // '0' ��Ϊ�Ǽ�
    if (val.length() == 1 && val[0] == _DogT('0'))
    {
        return false;
    }

    // "FALSE" ��Ϊ�Ǽ�
    if (val.length() == 4 &&
        ::toupper(0) == _DogT('F') &&
        ::toupper(0) == _DogT('A') &&
        ::toupper(0) == _DogT('L') &&
        ::toupper(0) == _DogT('E'))
    {
        return false;
    }

    // ������Ϊ��true
    return true;
}

int LogDogConfig::GetInt32(const DogString & key)
{
    DogString val;

    // ��������Ϊ�Ǽ�
    if (!GetStrVal(key, val))
    {
        return 0;
    }

    return ::_tstoi(val.c_str());
}

void LogDogConfig::ReLoad()
{
    m_keyValue.clear();
    m_timer.ReSet();
    m_errorCode = LogDogConfigErrorCode::LDC_NO_ERROR;
    std::shared_ptr<IniFile> spIniFile(IniFile::CreateObj(m_path));

    if (spIniFile == NULL)
    {
        m_errorCode = LogDogConfigErrorCode::LDC_NO_CONFIG_FILE;
        return;
    }

    std::vector<DogString> names = spIniFile->Get(NULL, NULL);
    bool hasName = false;

    for (size_t i = 0; i < names.size(); ++i)
    {
        if (names[i] == m_name)
        {
            hasName = true;
            break;
        }
    }

    if (!hasName)
    {
        m_errorCode = LogDogConfigErrorCode::LDC_NO_MATCH_NAME;
        return;
    }

    std::vector<DogString> keys = spIniFile->Get(m_name.c_str(), NULL);

    for (auto it : keys)
    {
        std::vector<DogString> vals = spIniFile->Get(m_name.c_str(), it.c_str());

        if (vals.size() == 1)
        {
            m_keyValue[it] = vals[0];
        }
    }
}

/* ���������ļ��Ƿ��д���
@return ������ ����LDC_NO_ERROR��ʾ�ɹ�
*/
LogDogConfigErrorCode LogDogConfig::GetErrorCode()
{
    return m_errorCode;
}

DogString & LogDogConfig::GetConfigPath()
{
    return m_path;
}

DogString & LogDogConfig::GetConfigName()
{
    return m_name;
}

