
#ifndef __ILOG_H_
#define __ILOG_H_

#include "task/ISimpleTask.h"
#include "noncopyable.h"

/** ��־ʵ��
*/
class ILog :
    public ITask,
    public NonCopyable
{
public:
    ILog()
    {
    }

    /** ִ������
    */
    virtual void DoTask()
    {
        Log();
    }

    /** ��־����
    */
    virtual void Log() = 0;

    /** ֹͣ����
    */
    virtual void Stop()
    {
        // ɾ��
    };
};


#endif //__ILOG_H_
