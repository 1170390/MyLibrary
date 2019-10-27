
#ifndef _LOGDOGCONFIG_H__
#define _LOGDOGCONFIG_H__

#include "LogDogDef.h"

/** ��־�������ļ�
*/
class LogDogConfig
{
public:
    /** ���캯��������ʼ��
    @param [in] path �����ļ�·��
    @param [in] name �������в��ҵ���־����
    */
    LogDogConfig(const DogString& path, const DogString& name);

public:
    /** ��ʼ��
    @param [in] path �����ļ�·��
    */
    void ReLoad(const DogString& path, const DogString& name);

    /* ���������ļ��Ƿ��д���
    @return ������ ����LDC_NO_ERROR��ʾ�ɹ�
    */
    LogDogConfigErrorCode GetErrorCode();

    /** �����־����
    @return ��־����
    */
    LogDogConfigEntry& GetLogDogConfigEntry();

private:
    /** ������
    */
    LogDogConfigErrorCode m_errorCode = LogDogConfigErrorCode::LDC_NO_ERROR;

    /** ��ǰ������Ŀ
    */
    LogDogConfigEntry m_configEntry;
};

#endif
