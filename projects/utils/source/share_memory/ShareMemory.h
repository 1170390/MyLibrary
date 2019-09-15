#ifndef __MEMORYSHARE_H_
#define __MEMORYSHARE_H_

#include <string>
#include <Windows.h>

/** �����ڴ�
*/
class ShareMemory
{
public:
    ShareMemory();
    ~ShareMemory();

    // ��������
    ShareMemory(const ShareMemory&) = delete;
    ShareMemory(ShareMemory&&) = delete;
    ShareMemory& operator=(const ShareMemory&) = delete;

public:
    /** ���������ڴ棬����Ѿ��������
    @param [in] name �����ڴ����ƣ�Ϊ��ʱʧ��
    @param [in] size ��С
    @return �Ƿ�ɹ�
    */
    bool Create(const std::wstring name, size_t size);

    /** �򿪹����ڴ棬������������ʧ��
    @param [in] name �����ڴ����ƣ�Ϊ��ʱʧ��
    @return �Ƿ�ɹ�
    */
    bool Open(const std::wstring name);

    /** ����ڴ��ַ��ʧ�ܷ���NULL
    @param [in] offset ����ڿ�ʼ��λ��
    @return ����ӳ��ĵ�ַ��ʧ�ܷ���NULL
    */
    void* GetBuff(size_t offset = 0);

private:
    /** ��һ�ε�ӳ��
    */
    void* m_pMapViewOfFile;

    /** m_pMapViewOfFileӳ���λ�ã�һ���0��ʼ
    */
    size_t m_offset;

    /** �ڴ�ӳ���������಻��ȥclose�����������ǽ����������������
    */
    HANDLE m_hMap;
};

#endif
