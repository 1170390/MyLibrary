
#ifndef __TEST_GRAPHICS_H_
#define __TEST_GRAPHICS_H_

#include <windows.h>


class MyConsoleWnd
{
public:
    /** ���캯��
    */
    MyConsoleWnd();

    /** ��������
    */
    ~MyConsoleWnd();


public:
    /** ��ʼ��
    @return �Ƿ�ɹ�
    */
    bool Loop();

public:
    /** ������Ϣ������
    */
    HRESULT OnEvent(HWND hWnd, UINT, WPARAM, LPARAM);

private:
    /** ����̨���
    */
    HWND m_hWnd;
};

#endif // __TEST_GRAPHICS_H_
