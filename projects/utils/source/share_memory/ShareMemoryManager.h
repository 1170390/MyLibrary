
#ifndef __MEMORYSHARE_MANAGER_H_
#define __MEMORYSHARE_MANAGER_H_

#include "singleton/singleton.h"

#include <string>
#include <map>
#include <Windows.h>

/** ����ǵ���
*/
class ShareMemoryManager
{
protected:
    ShareMemoryManager();
    ~ShareMemoryManager();

    // ��������
    ShareMemoryManager(const ShareMemoryManager&) = delete;
    ShareMemoryManager(ShareMemoryManager&&) = delete;
    ShareMemoryManager& operator=(const ShareMemoryManager&) = delete;

public:
    /** ���������ڴ棬����Ѿ��������
    @param [in] name �����ڴ����ƣ�Ϊ��ʱʧ��
    @param [in] size ��С
    @return ӳ������ʧ�ܷ���NULL
    */
    HANDLE Create(const std::wstring name, size_t size);

    /** �򿪹����ڴ棬������������ʧ��
    @param [in] name �����ڴ����ƣ�Ϊ��ʱʧ��
    @return ӳ������ʧ�ܷ���NULL
    */
    HANDLE Open(const std::wstring name);

private:
    /** ����map�Ƿ��Ѿ�������
    @param [in] name �����ڴ����ƣ�Ϊ��ʱʧ��
    @return ӳ�����������ڷ���NULL
    */
    HANDLE Find(const std::wstring name);

private:
    /** �ڴ�ӳ�������������Ƶ�map
    */
    std::map<std::wstring, HANDLE> m_handleMap;
};

// ��������
#define SHAREMEMORYMANAGER() (Singleton<ShareMemoryManager>::GetInstance())
#endif // __MEMORYSHARE_MANAGER_H_
