#ifndef __LIMITSINGLEINSTANCE_H_
#define __LIMITSINGLEINSTANCE_H_

#include <windows.h>

/** ���ƽ���ʵ��Ψһ
*/
class LimitSingleInstance
{
public:
    /** ���캯��
    */
    LimitSingleInstance(LPCTSTR strInstanceUUID)
    {
        m_hMutex = ::CreateMutex(NULL, FALSE, strInstanceUUID);
        m_dwLastError = ::GetLastError();
    }

    /** ��������
    */
    ~LimitSingleInstance()
    {
        if (m_hMutex) 
        {
            ::CloseHandle(m_hMutex);
        }
    }

    /** �Ƿ��Ѿ���������
    @return �Ƿ�������
    */
    BOOL IsAnotherInstanceRunning()
    {
        return (ERROR_ALREADY_EXISTS == m_dwLastError);
    }

private:
    /** last_error
    */
    DWORD  m_dwLastError;

    /** ���
    */
    HANDLE m_hMutex;
};

#endif // LIMITSINGLEINSTANCE_H