
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

/** ��ʼ��
@param [in] path �����ļ�·��
@param [in] name �����ļ��ж�Ӧ��secsion
*/
void LOG_INIT(const DogString& path, const DogString& name);

/** ����ʼ��
*/
void LOG_UNINIT();

/** ����־
@param [in] level ��־�ȼ�
@param [in] logStr ��־��������
*/
void SIMPLE_LOG(LogDogConfigLevel level, const DogString& logStr);

/** ������Ϣ
*/
#define LOG_DEBUG(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_6, logStr)

/** ��ͨ��Ϣ
*/
#define LOG_INFO(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_5, logStr)

/** ����
*/
#define LOG_WARNING(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_4, logStr)

/** assert �����п�/��ĸΪ0
*/
#define LOG_ASSERT(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_3, logStr)

/** ���صĴ��󣬱�����Դ�����˵�
*/
#define LOG_SERIOUS_ERROR(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_2, logStr)

/** �������صĴ����Ҳ�֪���ͱ�����ɶ����o_0
*/
#define LOG_VERY_SERIOUS_ERROR(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_1, logStr)

/** ����������󣬱�����Ϊʲô�ܹ�����־����ʵ��Ҳ��֪��
@note try catch�еı����ϱ�
*/
#define LOG_CRASH(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_0, logStr)


#endif //__LOGDOGDEF_H_
