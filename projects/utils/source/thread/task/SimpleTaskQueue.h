
#ifndef __SIMPLE_TASK_QUEUE_H_
#define __SIMPLE_TASK_QUEUE_H_

#include "ISimpleTask.h"

#include "noncopyable/noncopyable.h"

#include <mutex>
#include <memory>
#include <queue>
#include <thread>

/** ǰ�����������¼���ֻSimpleTaskQueue��
*/
class SimpleEvent;

/** ���߳�����ģ��
@note �е���������������ģ�ͣ�ֻ��������ֻ��һ��
*/
class SimpleTaskQueue :
    public NonCopyable
{
public:
    /** ���캯��
    */
    SimpleTaskQueue();

    /** ��������
    */
    ~SimpleTaskQueue();

public:
    /** ��ʼѭ��
    @return �Ƿ�ɹ�
    */
    bool Start();

    /** ֹͣ��������
    */
    void StopAll();

    /** ֹͣ��ǰ������
    */
    void StopCurrent();

    /** ����������������ǰ�ģ�����ֹͣѭ��
    */
    void ClearAll();

    /** ����������񲻰�����ǰ�ģ�����ֹͣѭ��
    */
    void ClearQueue();

    /** ���һ������
    @param [in] task ����
    */
    void PushTask(const std::shared_ptr<ITask>& task);

    /** ���һ����������
    @param [in] task ����
    */
    void PushTask(const std::function<void()>& task);

public:
    /** �̻߳ص�
    */
    virtual void ThreadCallBack();

private:
    /** �߳�
    */
    std::thread* m_pThread;

    /** ������
    */
    std::recursive_mutex m_mutex;

    /** �߳��¼�
    */
    SimpleEvent m_event;

    /** �������
    */
    std::queue<std::shared_ptr<ITask> > m_taskQue;

    /** �Ƿ�ֹͣ��
    */
    bool m_stop;

    /** ��ǰ����ִ�е�
    */
    std::shared_ptr<ITask> m_currentTask;
};


#endif // __SIMPLE_TASK_QUEUE_H_


