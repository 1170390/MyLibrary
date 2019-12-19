
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

        if (!m_hasSignal)
        {
            // �������������ǣ�
            // 1��m_mutex.unlock();
            // 2��wait()
            // 3��m_mutex.lock();
            // wait(lck) �൱�ڽ�1��2�����ŵ�һ��cpu������
            m_con.wait(lck);
        }

        m_hasSignal = false;
    }

    /** ����һ���ź�
    */
    void SetEvent()
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_hasSignal = true;
        m_con.notify_all();
    }

private:
    /** ������
    */
    std::mutex m_mutex;

    /** condition_variable
    */
    std::condition_variable m_con;

    /** �Ƿ����ź�
    @note ��Ҫ��Ϊ���ȵ���SetEvent()��Ȼ�����wait�������������Wait()ǰ����::Sleep(1000);
    */
    bool m_hasSignal = false;
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

    // ��������
    SimpleTaskQueue(const SimpleTaskQueue&) = delete;
    SimpleTaskQueue(SimpleTaskQueue&&) = delete;
    SimpleTaskQueue& operator=(const SimpleTaskQueue&) = delete;

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


