
#ifndef __LOGDOG_H_
#define __LOGDOG_H_

#include "LogDogConfig.h"

#include "task/SimpleTaskQueue.h"
#include "typedef/DogString.h"

#include <memory>

class LogDog :
    public NonCopyable
{
public:
    /** ���캯��
    */
    LogDog();

    /** ��������
    */
    ~LogDog();

    /** ��ʼ��
    @param [in] path �����ļ�·��
    @param [in] name ����־������
    */
    bool Init(const DogString& path, const DogString& name);

private:
    /** �����ļ�
    */
    LogDogConfig m_config;

    /** �������
    */
    std::shared_ptr<SimpleTaskQueue> m_taskque;
};


#endif //__NAME_H_
