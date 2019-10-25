
#ifndef _LOGCONFIG_H_
#define _LOGCONFIG_H_

#include "Export/LogDogDef.h"
#include "noncopyable.h"

/** ��־�������ļ�
*/
class LogDogConfig :
    public NonCopyable
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

public:
    /** ��ʼ��
    @param [in] path �����ļ�·��
    */
    void ReLoad(const std::wstring& path, const std::wstring& name);

    /* ���������ļ��Ƿ��д���
    @return ������ ����LDC_NO_ERROR��ʾ�ɹ�
    */
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


