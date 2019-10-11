
#ifndef __SIMPLE_TASK_QUEUE_H_
#define __SIMPLE_TASK_QUEUE_H_

#include "ISimpleTask.h"

#include <mutex>
#include <memory>
#include <queue>
#include <thread>

class SimpleEvent
{
public:
    /** �ȴ�һ���ź�
    */
    void Wait()
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_con.wait(lck);
    }

    /** ����һ���ź�
    */
    void SetEvent()
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_con.notify_all();
    }

private:
    /** ������
    */
    std::mutex m_mutex;

    /** condition_variable
    */
    std::condition_variable m_con;
};

/** ���߳�����ģ��
*/
class SimpleTaskQueue
{
public:
    /** ���캯��
    */
    SimpleTaskQueue();

    /** ��������
    */
    ~SimpleTaskQueue();

    // ����������
    SimpleTaskQueue(const SimpleTaskQueue&) = delete;
    SimpleTaskQueue(SimpleTaskQueue&&) = delete;
    SimpleTaskQueue& operator=(const SimpleTaskQueue&) = delete;

public:
    /** ��ʼѭ��
    */
    void Start();

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

    /** ����һ������
    @param [in] task ����
    */
    void PushTask(const std::shared_ptr<ITask>& task);

    /** ����һ����������
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

