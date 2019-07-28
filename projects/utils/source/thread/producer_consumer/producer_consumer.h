
#ifndef __PRODUCER_CONSUMER_H_
#define __PRODUCER_CONSUMER_H_

/************************************************************************************************
*������-������ģ�ͣ���ҪΪ���ö��̼߳��������ʹ��cpu��Դ��                                              *
*�������һ�����ļ��Ĵ�������ָ��һ���߳�ר�Ŷ��ļ���һ���̻߳����ϾͿ��Խ�ioռ���ˣ�,�����̴߳���ÿ�ζ��Ľ��  *
************************************************************************************************/

#include "IProducer.h"
#include "IConsume.h"
#include <vector>
#include <thread>
#include <mutex>
#include <windows.h>
#include "timer_recorder/timer_recorder.h"

using GOODS_VEC = std::vector<IGoods*>;
using THREAD_VEC = std::vector<std::thread*>;

/** �߳������������һ�����ʹ�ã�������ֵ��û��ʵ������
*/
#define MAX_THREAD_COUNT 10000

/** �߳�δָ�������������һ�����ʹ��
*/
#define AUTO_THREAD_COUNT 100000

/** Producer_Consumer_Model ������������ģ����
*/
class PAndCModel
{
public:
    PAndCModel(IProducer* pProducer, IConsumer* pConsumer);
    ~PAndCModel();

public:

    void Start();

    /** �е�ʱ��ϣ������cpu�����ʱ�����ָ��ʣ�༸��cpu�̡߳�
    ���m_maxThreadCountΪ2����ô�˲�����Ч
    @param [in] count ����
    */
    inline void SetNotUseThreadCount(unsigned int count)
    {
        if (m_maxThreadCount <= 2)
        {
            m_notUsedThreadCount = 0;
        }
        else
        {
            m_notUsedThreadCount = count;
        }
    }

    /** �е�ʱ����Ϊĳ��ԭ����Ҫָ��������/�������������
    @param [in] count ����������������Ϊ0��Ϊ0��ʱ�����߳�һ��������������Ʒ��Ȼ���ٶ��߳����ѣ�
                Ҳ����ΪMAX_THREAD_COUNT��ΪMAX_THREAD_COUNTʱ����߳�������Ȼ�������߳�һ��������
                Ҳ����ΪAUTO_THREAD_COUNT��ΪAUTO_THREAD_COUNTʱ���Զ������߳�����
    */
    inline void SetMaxProducerCount(unsigned int count)
    {
        m_maxProducerCount = count;
    }

private:
    /** �������̻߳ص�
    */
    void ProductCallBack(IGoods* pGoods);

    /** ���������̻߳ص�
    */
    void ConsumeCallBack();

    /** ���һ���������߳�
    */
    bool AddProductThread();

    /** ���һ���������߳�
    */
    bool AddConsumeThread();

private:
    /** ��ʼ����
    @return �Ƿ�ɹ�
    */
    bool StartProduct();

    /** ��ʼ����
    @return �Ƿ�ɹ�
    */
    bool StartConsume();

private:
    /** ������
    */
    IProducer* m_pProducer;

    /** ������
    */
    IConsumer* m_pConsumer;

    /** �������̳߳�
    */
    THREAD_VEC m_producerThreadVec;

    /** �������̳߳�
    */
    THREAD_VEC m_consumerThreadVec;

    /** ��Ʒ����
    */
    GOODS_VEC m_goodsVec;

    /** �Ƿ���������
    */
    bool m_isProductEnd;

    /** ������
    */
    std::mutex* m_pMutex;

    /** ������������ͬ����
    */
    HANDLE m_hSemaphore;

    /** ����߳�����
    */
    unsigned int m_maxThreadCount;

    /** ��ʹ�õ��߳�����
    */
    unsigned int m_notUsedThreadCount;

    /** �������������
    */
    unsigned int m_maxProducerCount;

    /** ��ʱ��
    */
    TimerRecorder* m_pTimerRecoder;

    /** �ȴ��е��߳�����
    */
    int m_sleepThreadCount;
};



#endif


