#ifndef __MEMORYSHARE_H_
#define __MEMORYSHARE_H_

#include <string>
#include <Windows.h>

#define  BUF_SIZE 100
#define  FLAG 1

/** �̼߳�ͨ��ʹ��---------------------TODO �Ժ��п�����д
*/
class MemoryShare
{
public:
    /** ���캯��
    @param [in] sShareName �����ڴ�����
    */
    MemoryShare(const std::string & sShareName);

    /** ��������
    */
    ~MemoryShare();

public:
    /** д�ڴ�
    @param [in] pBuf Ҫд�����飬�ⲿ�����ͷ�
    @param [in] nSize buff ��С
    @return �Ƿ�ɹ�
    */
    bool Write(const void * pBuf, int nSize);

    /** ���ڴ�
    @param [out] pBuf ��СΪBUF_SIZE���ڴ���Ҫ�Լ����
    @return �Ƿ�ɹ�
    */
    bool Read(void * pBuf);

    /** ���
    @return �Ƿ�ɹ�
    */
    bool Clear();

    /** ����д����
    @return �Ƿ����д��
    */
    bool IsReadToWrite();

    /** ���Զ�����
    @return �Ƿ���Զ���
    */
    bool IsReadToRead();

    /** �ж��
    @return ��С
    */
    int GetBuffSize();

private:
    /** ӳ��
    */
    HANDLE  m_hMapFile;

    /** m_lpBase
    */
    LPVOID    m_lpBase;
};

#endif
