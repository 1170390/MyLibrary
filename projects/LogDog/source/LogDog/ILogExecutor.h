
#ifndef __LOG_EXECUTOR_H_
#define __LOG_EXECUTOR_H_

#include "typedef/DogString.h"
#include "LogDogConfig.h"

class ILogExecutor
{
public:
    virtual ~ILogExecutor()
    {
    }

    /** ��־��������
    @param [in] logStr ��־�ַ���
    @return �Ƿ�ɹ�
    */
    virtual bool Executor(const DogString& logStr) = 0;
};

/** �ṩһ��д���ļ��Ĵ�����
*/
class DumpToFileExecutor :
    public ILogExecutor
{
public:
    /** ���캯��
    */
    DumpToFileExecutor();

    /** ��־��������
    @param [in] logStr ��־�ַ���
    @return �Ƿ�ɹ�
    */
    virtual bool Executor(const DogString& logStr);

private:
    /** ��ȡ��־�ļ�·��������������򴴽�
    @param [in, out] logLen ��־����
    @param [in] baseDirBath Ŀ¼·��
    @return ��־�ļ�·��
    */
    DogString GetAndCreateLogFile(size_t logLen, const DogString& baseDirBath);

    /** ����ļ���С�Ƿ����Ԥ�ڣ�������������´����ļ�
    @param [in, out] logLen ��־����
    @param [in, out] filePath ��ǰ�ļ�·��
    @return �Ƿ�ɹ�
    */
    bool CheckFileSizeAndCreate(size_t logLen, DogString& filePath);

    /** ���� "910",ִ�к��� "911"
    @param [in, out] ����
    @param [in] len ����
    @return �Ƿ�ɹ������buff�������ַ���false,����ﵽ���ֵ��ѭ����0
    */
    bool StrInc(DogChar* buff, int len);
};

/** �ṩһ����������Ĵ�����
*/
class UpLoadExecutor :
    public ILogExecutor
{
public:
    /** ��־��������
    @param [in] logStr ��־�ַ���
    @return �Ƿ�ɹ�
    */
    virtual bool Executor(const DogString& logStr);
};

#endif //__LOG_EXECUTOR_H_
