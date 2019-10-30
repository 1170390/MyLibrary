
#ifndef __LOGDOGDEF_H_
#define __LOGDOGDEF_H_

#include "typedef/DogString.h"

/** ��־�ȼ�
*/
enum class LogDogConfigLevel
{
    /** 0 crash
    */
    LDC_LEVEL_0 = 0,

    /** 1 �������ص�
    */
    LDC_LEVEL_1,

    /** 2 ���ص�
    */
    LDC_LEVEL_2,

    /** 3 assert
    */
    LDC_LEVEL_3,

    /** 4 ����
    */
    LDC_LEVEL_4,

    /** 5 ��ͨ��־
    */
    LDC_LEVEL_5,

    /** 6 ������Ϣ
    */
    LDC_LEVEL_6,

    /** ��Ч
    */
    LDC_LEVEL_END,
};

struct LogDogConfigEntry
{
    /** �����ļ�·��
    */
    DogString m_path;

    /** ��־���ƣ������Ҫд�ļ��Ļ��������ļ�����һ��Ŀ¼����
    */
    DogString m_name;

    /** ��־�ȼ�
    */
    LogDogConfigLevel m_level = LogDogConfigLevel::LDC_LEVEL_4;

    /** �Ƿ���Ҫд���ļ�
    */
    bool m_isNeedDmpToFile = false;

    /** �Ƿ���Ҫ�ϴ�
    */
    bool m_isNeedUpload = false;
};

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

#endif //__LOGDOGDEF_H_