
#ifndef __MEMORYSHARE_MANAGER_H_
#define __MEMORYSHARE_MANAGER_H_

#include "singleton/singleton.h"

#include <string>
#include <map>
#include <Windows.h>

/** ����ǵ���
*/
class ShareMemortManager
{
protected:
    ShareMemortManager();
    ~ShareMemortManager();

    // ��������
    ShareMemortManager(const ShareMemortManager&) = delete;
    ShareMemortManager(ShareMemortManager&&) = delete;
    ShareMemortManager& operator=(const ShareMemortManager&) = delete;

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
#define SHAREMEMORYMANAGER() (Singleton<ShareMemortManager>::GetInstance())
#endif // __MEMORYSHARE_MANAGER_H_
