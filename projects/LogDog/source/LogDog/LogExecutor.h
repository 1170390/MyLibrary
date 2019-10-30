
#ifndef __LOG_EXECUTOR_H_
#define __LOG_EXECUTOR_H_

#include "typedef/DogString.h"
#include "LogDogConfig.h"

/** ��־�ļ���������С 5M
*/
const int g_file_size = 5242880;

class ILogExecutor
{
public:
    virtual ~ILogExecutor()
    {
    }

    /** ��־��������
    @param [in] logStr ��־�ַ���
    @param [in] config ��־����
    @return �Ƿ�ɹ�
    */
    virtual bool Executor(const DogString& logStr, const std::shared_ptr <LogDogConfig>& config) = 0;
};

/** д���ļ�
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
    @param [in] config ��־����
    @return �Ƿ�ɹ�
    */
    virtual bool Executor(const DogString& logStr, const std::shared_ptr <LogDogConfig>& config);

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

/** ��������
*/
class UpLoadExecutor :
    public ILogExecutor
{
public:
    /** ��־��������
    @param [in] logStr ��־�ַ���
    @param [in] config ��־����
    @return �Ƿ�ɹ�
    */
    virtual bool Executor(const DogString& logStr, const std::shared_ptr <LogDogConfig>& config);
};
#endif //__LOG_EXECUTOR_H_
