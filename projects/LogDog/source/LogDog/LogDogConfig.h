
#ifndef _LOGCONFIG_H_
#define _LOGCONFIG_H_

#include "LogDogDef.h"

/** ��־�������ļ�
*/
class LogDogConfig
{
public:
    /** ���캯��
    */
    LogDogConfig();

    /** ���캯��������ʼ��
    @param [in] path �����ļ�·��
    @param [in] name �������в��ҵ���־����
    */
    LogDogConfig(const std::wstring& path, const std::wstring& name);

    LogDogConfig(const LogDogConfig&) = delete;
    LogDogConfig& operator=(const LogDogConfig&) = delete;

public:
    /** ��ʼ��
    @param [in] path �����ļ�·��
    */
    void ReLoad(const std::wstring& path, const std::wstring& name);

    inline LogDogConfigErrorCode GetErrorCode()
    {
        return m_errorCode;
    }

private:
    /** ������
    */
    LogDogConfigErrorCode m_errorCode = LogDogConfigErrorCode::LDC_NO_ERROR;

    /** ��ǰ������Ŀ
    */
    LogDogConfigEntry m_configEntry;
};

#endif // !_LOGCONFIG_H_


