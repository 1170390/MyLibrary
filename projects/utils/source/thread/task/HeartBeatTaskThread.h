
#ifndef __HEARTBEAD_TASK_THREAD_
#define __HEARTBEAD_TASK_THREAD_ 1

#include "IHeartBeatTask.h"

#include "noncopyable/noncopyable.h"

#include <list>
#include <thread>
#include <mutex>

struct HeartBeatTaskWraper;
using SPHeartBeatTaskWraper = std::shared_ptr<HeartBeatTaskWraper>;

/** �����߳�����ģ��
*/
class HeartBeatTaskThread :
    public NonCopyable
{
public:
    /** ���캯��
    */
    HeartBeatTaskThread();

    /** ��������
    */
    ~HeartBeatTaskThread();

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
    void PushTask(const SPHeartBeatTask& task);

    /** ���һ����������
    @param [in] task ����
    @param [in] timeOut ʱ����
    @param [in] times ִ�д�����Ϊ-1����ִ�������Σ�Ĭ��Ϊ-1
    */
    void PushTask(const std::function<bool()>& task, uint32_t timeOut, int32_t times = -1);

    /** ��õ�ǰ�����е�������������ǰ����ִ�е�
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

    /** �������
    */
    std::list<SPHeartBeatTaskWraper > m_taskList;

    /** �Ƿ�ֹͣ��
    */
    bool m_stop;

    /** ��ǰ����ִ�е�
    */
    SPHeartBeatTaskWraper m_currentTask;
};

#endif // __HEARTBEAD_TASK_THREAD_
