#include "producer_consumer.h"

#include "cpu/cpu_thread_count.h"
#include "singleton/singleton.h"
#include <functional>
#include <assert.h>

/** ��Ʒ�������
*/
const long MAX_SEMAPHORE_COUNT = 0x7FFFFFFF;

/** ��BEFORE_TIME_PASS����֮��ʼƽ���߳�����
*/
const long BEFORE_TIME_PASS = 3000;

PAndCModel::PAndCModel(IProducer* pProducer, IConsumer* pConsumer) :
    m_pProducer(pProducer),
    m_pConsumer(pConsumer),
    m_pMutex(NULL),
    m_hSemaphore(NULL),
    m_isProductEnd(false),
    m_maxThreadCount(0),
    m_pTimerRecoder(NULL),
    m_notUsedThreadCount(0),
    m_sleepThreadCount(0),
    m_maxProducerCount(AUTO_THREAD_COUNT)
{
    m_maxThreadCount = 
        Singleton<CpuCoreThreadCount>::GetInstance().GetCount();

    // �����ȡʧ���˻���֧�ֵ��߳�ֻ��1������ô����̱߳��������������������߸�һ����
    if (m_maxThreadCount < 2)
    {
        m_maxThreadCount = 2;
    }
}

PAndCModel::~PAndCModel()
{
    if (m_goodsVec.size() > 0)
    {
        for (auto it : m_goodsVec)
        {
            delete it;
        }

        m_goodsVec.clear();
    }
}

void PAndCModel::Start()
{
    if (m_pProducer == NULL ||
        m_pConsumer == NULL)
    {
        return;
    }

    m_pMutex = new (std::nothrow) std::mutex();

    if (m_pMutex == NULL)
    {
        return;
    }

    m_hSemaphore = ::CreateSemaphore(NULL, 0, MAX_SEMAPHORE_COUNT, NULL);

    if (m_hSemaphore == NULL)
    {
        return;
    }

    m_pTimerRecoder = new (std::nothrow) TimerRecorder();

    if (m_pTimerRecoder == NULL)
    {
        return;
    }

    StartProduct();
    StartConsume();

    // �ȴ������߶�����
    for (auto it : m_producerThreadVec)
    {
        it->join();
    }

    m_isProductEnd = true;

    // �ȴ������߶�����
    for (unsigned int i = 0; i < m_consumerThreadVec.size(); ++i)
    {
        ::ReleaseSemaphore(m_hSemaphore, 1, NULL);
    }

    for (auto it : m_consumerThreadVec)
    {
        it->join();
    }

    // ��Դ����
    for (auto it : m_producerThreadVec)
    {
        delete it;
    }

    m_producerThreadVec.clear();

    for (auto it : m_consumerThreadVec)
    {
        delete it;
    }

    m_consumerThreadVec.clear();
    ::CloseHandle(m_hSemaphore);
    delete m_pMutex;
    m_pMutex = NULL;
}

void PAndCModel::ProductCallBack(IGoods* pGoods)
{
    if (pGoods == NULL)
    {
        return;
    }

    m_pMutex->lock();
    int tmp = (int)m_maxProducerCount;

    if (tmp == AUTO_THREAD_COUNT)
    {
        tmp = (int)m_producerThreadVec.size();
    }

    tmp = (int)m_maxThreadCount - tmp - (int)m_notUsedThreadCount;

    // ���ж���δʹ���߳�&&(��Ʒ��ʣ||�������߳�������û�дﵽ���)����������������
    if ((int)m_consumerThreadVec.size() < tmp &&
        (m_goodsVec.size() > m_consumerThreadVec.size() || m_producerThreadVec.size() < m_maxProducerCount))
    {
        if (!m_isProductEnd && m_pTimerRecoder->GetTimePass() > BEFORE_TIME_PASS)
        {
            AddConsumeThread();
        }
    }

    m_goodsVec.push_back(pGoods);

    // �����߹���,��������ģʽ������
    assert(m_goodsVec.size() < MAX_SEMAPHORE_COUNT);

    if (m_sleepThreadCount > 0)
    {
        ::ReleaseSemaphore(m_hSemaphore, 1, NULL);
    }

    m_pMutex->unlock();
}

void PAndCModel::ConsumeCallBack()
{
    while (true)
    {
        m_pMutex->lock();

        // ����̫����
        if (m_goodsVec.size() == 0)
        {
            m_pMutex->unlock();

            if (m_isProductEnd)
            {
                break;
            }
 
            m_pMutex->lock();
 
            // ��������������
            int tmp = (int)m_maxProducerCount;
 
            if (tmp == AUTO_THREAD_COUNT)
            {
                tmp = (int)m_maxThreadCount - (int)m_consumerThreadVec.size() - (int)m_notUsedThreadCount;
            }
 
            if ((int)m_producerThreadVec.size() < tmp && !m_isProductEnd)
            {
                if (m_pTimerRecoder->GetTimePass() > BEFORE_TIME_PASS)
                {
                    AddProductThread();
                }
            }
 
            ++m_sleepThreadCount;
            m_pMutex->unlock();
 
            ::WaitForSingleObject(m_hSemaphore, INFINITE);
            m_pMutex->lock();
            --m_sleepThreadCount;
 
            // ���Ǳ������ˣ������Ļ�ֱ�ӷ���
            if (m_goodsVec.size() == 0)
            {
                m_pMutex->unlock();
                continue;
            }
        }

        IGoods* pGoods = m_goodsVec.back();
        m_goodsVec.pop_back();
        m_pMutex->unlock();
        m_pConsumer->Consumer(pGoods);

        // ��Ҫ��������
        delete pGoods;
    }
}

bool PAndCModel::AddProductThread()
{
    // �ȿ���һ���߳�
    std::thread* pThread = new (std::nothrow) std::thread([this]()
    {
        m_pProducer->Product([this](IGoods* pGoods)
        {
            ProductCallBack(pGoods);
        });
    });

    if (pThread == NULL)
    {
        return false;
    }

    m_producerThreadVec.push_back(pThread);
    return true;
}

bool PAndCModel::AddConsumeThread()
{
    // �ȿ���һ���߳�
    std::thread* pThread = new (std::nothrow) std::thread([&]()
    {
        ConsumeCallBack();
    });

    if (pThread == NULL)
    {
        return false;
    }

    m_consumerThreadVec.push_back(pThread);
    return true;
}

bool PAndCModel::StartProduct()
{
    // һ��������
    if (m_maxProducerCount == 0)
    {
        m_pProducer->Product([&](IGoods* pGoods)
        {
            if (pGoods == NULL)
            {
                return;
            }

            m_goodsVec.push_back(pGoods);
        });

        return true;
    }

    return AddProductThread();
}

bool PAndCModel::StartConsume()
{
    // m_maxProducerCountҲ����ΪMAX_THREAD_COUNT
    // ΪMAX_THREAD_COUNTʱ����߳�������Ȼ�������߳�һ��������
    if (m_maxProducerCount == MAX_THREAD_COUNT)
    {
        for (auto it : m_goodsVec)
        {
            m_pConsumer->Consumer(it);
        }

        return true;
    }
    
    return AddConsumeThread();
}
