
#ifndef __ITASK_H_
#define __ITASK_H_

class ITask
{
public:
    virtual ~ITask()
    {

    }

    /** ִ������
    */
    virtual void DoTask() = 0;

    /** ֹͣ����
    */
    virtual void Stop() = 0;
};

#endif // __ITASK_H_

