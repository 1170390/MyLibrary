
#ifndef __ILOGDOG_H_
#define __ILOGDOG_H_

#include "LogDogDef.h"

#include "task/ISimpleTask.h"

class ILog : public ITask
{
public:
    ILog() :
        m_configEntry(NULL)
    {
    }

    /** ִ������
    */
    virtual void DoTask() = 0;

    /** ֹͣ����
    */
    virtual void Stop()
    {
        // ɾ��
    };

private:
    /** ��־�е�������Ϣ
    */
    LogDogConfigEntry* m_configEntry;
};


#endif //__ILOGDOG_H_
