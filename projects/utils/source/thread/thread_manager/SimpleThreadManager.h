
#ifndef __SIMPLE_THREAD_MANAGER_H_
#define __SIMPLE_THREAD_MANAGER_H_ 1

#include "thread/task/SimpleTaskThread.h"
#include "thread/task/HeartBeatTaskThread.h"

/** ���̹߳�����
@note !!!!!!!!!!! ��������/uninit �в�Ӧ���ж������߳���ִ��
*/
class SimpleThreadManager
{
public:
    /** ���캯��
    */
    SimpleThreadManager();

    /** ��������
    */
    virtual ~SimpleThreadManager();

public:
    /** ��������߳������������Ҫ�����������̳и��ಢ���ظú���
    @return �������������������
    */
    virtual uint32_t GetBlockTaskThreadCount();

    /** ֹͣ���У��������ظú���ʱ��Ӧ����ʾ�ٴε��øú���
    */
    virtual void StopAll();

public:
    /** ���һ����������
    @param [in] task ����
    */
    void PushFastTask(const std::shared_ptr<ITask>& task);

    /** ���һ�����ٺ�������
    @param [in] task ����
    */
    void PushFastTask(const std::function<bool()>& task);

    /** ��ÿ��ٶ��У������û��ʼ���Ļ����ú������Զ���ʼ��
    @return ���ٶ���
    */
    std::weak_ptr <SimpleTaskThread> GetFastThreadTaskQueue();

    /** ���һ����������
    @param [in] task ����
    */
    void PushBlockTask(const std::shared_ptr<ITask>& task);

    /** ���һ��������������
    @param [in] task ����
    */
    void PushBlockTask(const std::function<bool()>& task);

    /** ���һ��������
    @param [in] task ����
    */
    void PushHeartBeatTask(const SPHeartBeatTask& task);

    /** ���һ��������������
    @param [in] task ����
    @param [in] timeOut ʱ����
    @param [in] times ִ�д�����Ϊ-1����ִ�������Σ�Ĭ��Ϊ-1
    */
    void PushHeartBeatTask(const std::function<bool()>& task, uint32_t timeOut, int32_t times = -1);

protected:
    /** ���������߳�һ��
    */
    std::shared_ptr<SimpleTaskThread> m_spFastThreadTaskQueue;

    /** ���������߳�����
    @note TODO: ��ʱ������洢���������У��Ժ���Կ��ǽ��ڲ���que��װ���̰߳�ȫ�ģ�Ȼ�����֧�ֶ���̵߳Ķ���
    */
    std::vector<std::shared_ptr<SimpleTaskThread>> m_spBlockThreadTaskQueues;

    /** ��������һ��
    */
    std::shared_ptr<HeartBeatTaskThread> m_spHeartBeatThreadTaskQueue;

    /** ������
    */
    std::recursive_mutex m_mutex;
};

#endif // __SIMPLE_THREAD_MANAGER_H_
