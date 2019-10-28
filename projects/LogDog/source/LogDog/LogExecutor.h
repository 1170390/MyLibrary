
#ifndef __LOG_EXECUTOR_H_
#define __LOG_EXECUTOR_H_

#include "typedef/DogString.h"

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

/** д���ļ�
*/
class DumpToFileExecutor :
    public ILogExecutor
{
public:
    DumpToFileExecutor(const DogString& path);

    /** ��־��������
    @param [in] logStr ��־�ַ���
    @return �Ƿ�ɹ�
    */
    virtual bool Executor(const DogString& logStr);

private:
    /** Ŀ���ļ���·��
    */
    DogString m_path;
};

/** ��������
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
