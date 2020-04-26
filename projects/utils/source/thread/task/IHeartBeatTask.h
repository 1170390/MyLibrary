
#ifndef __IHEARTBEATTASK_h_
#define __IHEARTBEATTASK_h_ 1

#include "ITask.h"

#include <functional>
#include <memory>

/** ��������Ϊ�����������׼��
*/
class IHeartBeatTask :
    public ITask
{
public:
    /** ���캯��
    */
    IHeartBeatTask()
    {
    }

    /** ��������
    */
    virtual ~IHeartBeatTask()
    {
    }

    /** ����ִ����ɺ��Ƿ��Ƴ�������
    @return Ϊtrueʱ��ִ��������񽫴�����������Ƴ�
    */
    virtual bool RemoveAfterExcute()
    {
        return false;
    };

    /** ��������������λms
    @return �������
    */
    virtual uint32_t GetTimeOut() = 0;
};

/** ��������ָ��
*/
using SPHeartBeatTask = std::shared_ptr<IHeartBeatTask>;

/** �ص������ر�Ϊlambda׼�������Ǹ�Ϊģ��
*/
class HeartBeatFunTask :
    public IHeartBeatTask
{
public:
    /** ���캯��
    @param [callback] ��ִ�лص�
    @param [in] timeOut ʱ����
    @param [in] times ִ�д�����Ϊ-1����ִ�������Σ�Ĭ��Ϊ-1
    */
    HeartBeatFunTask(const std::function<bool()>& callback, uint32_t timeOut, int32_t times = -1) :
        m_callback(callback),
        m_timeOut(timeOut),
        m_times(times),
        m_curTimes(0)
    {
    }

    /** ��������
    */
    virtual ~HeartBeatFunTask()
    {
    }

    /** ִ������
    @return �Ƿ�ɹ�
    */
    virtual void DoTask()
    {
        if (m_callback != nullptr)
        {
            if (m_times != -1)
            {
                ++m_curTimes;
            }

            m_callback();
        }
    }

    /** ֹͣ����
    */
    virtual void Stop()
    {
        //
    }

    /** ����ִ����ɺ��Ƿ��Ƴ�������
    @return Ϊtrueʱ��ִ��������񽫴�����������Ƴ�
    */
    virtual bool RemoveAfterExcute()
    {
        if (m_callback == nullptr)
        {
            return true;
        }

        if (m_times == -1 || m_curTimes != m_times)
        {
            return false;
        }

        return true;
    };

    /** ��������������λms
    @return �������
    */
    virtual uint32_t GetTimeOut()
    {
        return m_timeOut;
    }

private:
    /** �ص�
    */
    std::function<bool()> m_callback;

    /** ִ�м��
    */
    uint32_t m_timeOut;

    /** ִ�д���
    */
    int32_t m_times;

    /** ��ǰִ�д���
    */
    int32_t m_curTimes;
};

#endif // __IHEARTBEATTASK_h_
