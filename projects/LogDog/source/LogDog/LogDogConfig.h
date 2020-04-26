
#ifndef _LOGDOGCONFIG_H__
#define _LOGDOGCONFIG_H__

#include "timer_recorder/timer_recorder.h"

#include "typedef/DogString.h"

#include <unordered_map>

/** ���������ļ��Ĵ�����
*/
enum class LogDogConfigErrorCode
{
    /** û�д���
    */
    LDC_NO_ERROR = 0,

    /** �����ļ�������
    */
    LDC_NO_CONFIG_FILE,

    /** �����ļ���û���ҵ���Ӧ������
    */
    LDC_NO_MATCH_NAME
};

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
    /** �������¼���
    @param [in] atonce false ʱ�����ʱ���������Ƶ���ļ��ػᱻ�ܾ���true���̼���
    */
    void TryReload(bool atonce = false);

    /* ���������ļ��Ƿ��д���
    @return ������ ����LDC_NO_ERROR��ʾ�ɹ�
    */
    LogDogConfigErrorCode GetErrorCode();

    /** ��������ļ�·��
    @return �����ļ�·��
    */
    DogString& GetConfigPath();

    /** ��������ļ�����
    @return �����ļ�����
    */
    DogString& GetConfigName();

    /** ��������ļ��е��ַ���ֵ
    @param [in] key key
    @param [out] ���ڵķ���ֵ
    @reutrn �Ƿ�ɹ�
    */
    bool GetStrVal(const DogString& key, DogString& val);

    /** ���boolֵ
    @note : ���Դ�Сд�� "false" ����0��Ϊ��false����������Ϊ��true
    @param [in] key key
    @reutrn ������key��Ӧ��ֵ�������ڷ���false
    */
    bool GetBool(const DogString& key);

    /** �����������������ڻ��߲���ת��Ϊ��������0
    @param [in] key key
    @param [out] ���ڵķ���ֵ
    @reutrn �Ƿ�ɹ�
    */
    int GetInt32(const DogString& key);

private:
    /** ��ʼ��
    */
    void ReLoad();

private:
    /** �����ļ�·��
    */
    DogString m_path;

    /** ��־���ƣ������Ҫд�ļ��Ļ��������ļ�����һ��Ŀ¼����
    */
    DogString m_name;

    /** ������
    */
    LogDogConfigErrorCode m_errorCode = LogDogConfigErrorCode::LDC_NO_ERROR;

    /** ��־�е�����
    */
    std::unordered_map<DogString, DogString> m_keyValue;

    /** ��ʱ��
    */
    TimerRecorder m_timer;
};

#endif
