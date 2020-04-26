
#ifndef __ISIMPLEFUNCTIONTASK_H_
#define __ISIMPLEFUNCTIONTASK_H_

#include "ITask.h"
#include <functional>

class SimpleFunctionTask :
    public ITask
{
public:
    SimpleFunctionTask(const std::function<void()>& callback) :
        m_callback(callback)
    {

    }

    virtual ~SimpleFunctionTask()
    {

    }

    /** ִ������
    */
    virtual void DoTask()
    {
        if (m_callback != nullptr)
        {
            m_callback();
        }
    }

    /** ֹͣ����
    */
    virtual void Stop() {}

private:
    /** �ص�
    */
    std::function<void()> m_callback;
};

#endif // __ISIMPLEFUNCTIONTASK_H_

