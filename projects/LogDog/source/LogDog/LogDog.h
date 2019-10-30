
/****************************************************************************/
/* �ṩһ��ʹ�õķ������û����Ը����������¸�д���ļ�                               */
/****************************************************************************/

#ifndef _LOGDOG_H__
#define _LOGDOG_H__

#include "ILog.h"
#include "LogDogConfig.h"

#include "singleton.h"
#include "task/SimpleTaskQueue.h"

#include <functional>
#include <unordered_map>
#include <thread>

/** ��־����
*/
class LogDog :
    public NonCopyable
{
protected:
    LogDog()
    {
    }

public:
    /** ��ʼ��
    @param [in] path �����ļ�·��
    @param [in] name �����ļ��ж�Ӧ��secsion
    @return ��־�߳��Ƿ񴴽��ɹ�
    */
    bool Init(const DogString& path, const DogString& name);

    /** ѹ��һ����־
    */
    void Push(const std::shared_ptr<ILog>& log);

    /** �ͷ���Դ����ʵ������������Ǻ���Ҫ����Ϊ�����ڳ����˳���ʱ����Լ��ͷŵģ�
    ֻ��Ϊ�˺�init���Ӧ
    */
    void UnInit();

    /** �������
    @param [in] key �ؼ���
    @param [out] val ���
    @return �Ƿ�ɹ�
    */
    bool GetConfig(const DogString& key, DogString& val);

private:
    /** �����ļ�
    */
    std::shared_ptr <LogDogConfig> m_spConfig;

    /** ��־�������
    */
    std::shared_ptr<SimpleTaskQueue> m_spLogQue;
};

#endif

