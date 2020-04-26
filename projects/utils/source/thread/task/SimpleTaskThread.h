
#ifndef __SIMPLE_TASK_THREAD_H_
#define __SIMPLE_TASK_THREAD_H_

#include "ITask.h"

#include "noncopyable/noncopyable.h"

#include <mutex>
#include <memory>
#include <queue>
#include <thread>

/** ǰ�����������¼���ֻSimpleTaskThread��
*/
class SimpleEvent;

/** ���߳�����ģ��
@note �е���������������ģ�ͣ�ֻ��������ֻ��һ��
*/
class SimpleTaskThread :
    public NonCopyable
{
public:
    /** ���캯��
    */
    SimpleTaskThread();

    /** ��������
    */
    ~SimpleTaskThread();

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

    /** ��õ�ǰ�����е�������������ǰ����ִ�еģ�����0˵�����п���
    @return ��ǰ�����е�����
    */
    size_t GetTaskCount();
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
    std::shared_ptr<SimpleEvent> m_spEvent;

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

#endif // __SIMPLE_TASK_THREAD_H_

