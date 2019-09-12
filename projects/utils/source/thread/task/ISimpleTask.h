
#ifndef __ISIMPLETASK_H_
#define __ISIMPLETASK_H_

#include "ITask.h"
#include <functional>

class ISimpleTask :
    public ITask
{
public:
    ISimpleTask(const std::function<void(int)>& callback) :
        m_callback(callback)
    {

    }

    virtual ~ISimpleTask()
    {

    }

    /** ִ������
    */
    virtual void DoTask() = 0;

    /** ֹͣ����
    */
    virtual void Stop() = 0;

    void CallBack(int val)
    {
        if (m_callback != NULL)
        {
            m_callback(val);
        }
    }

protected:
    /** �ص�
    */
    std::function<void(int)> m_callback;
};

class SimpleFunTask :
    public ITask
{
public:
    SimpleFunTask(const std::function<void()>& callback) :
        m_callback(callback)
    {

    }

    virtual ~SimpleFunTask()
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

#endif // __ITASK_H_

