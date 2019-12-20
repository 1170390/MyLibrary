
#include "GolMacro.h"

//#define TEST_GRAPHICS
#ifdef TEST_GRAPHICS
#include "TestGraphics.h"

MyConsoleWnd::MyConsoleWnd() :
    m_hWnd(NULL)
{
}

MyConsoleWnd::~MyConsoleWnd()
{
}

LRESULT MyWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // ���ʵ�ж��󣬴������¼�
    MyConsoleWnd* pThis = (MyConsoleWnd*)::GetWindowLongPtr(hWnd, GWLP_USERDATA);

    if (pThis != NULL)
    {
        if (S_OK == pThis->OnEvent(hWnd, msg, wParam, lParam))
        {
            return S_OK;
        }
    }

    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

bool MyConsoleWnd::Loop()
{
    HWND m_hWnd = ::GetConsoleWindow();

    if (m_hWnd == NULL)
    {
        return false;
    }

    long res = ::SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);
    res = ::SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LONG_PTR)MyWndProc);

    ::SendMessage(m_hWnd, WM_INITDIALOG, 0, 0);
    ::ShowWindow(m_hWnd, SW_NORMAL);

    // ��Ϣѭ����ʵ���Ͽ��Խ����������װ��һ����MsgLoop
    MSG msg = {0};
    while (1)
    {
        // �ŵ�ǰ�棬���������Ӧһ����Щ��Ϣ
        if (msg.message == WM_DESTROY ||
            msg.message == WM_CLOSE ||
            msg.message == WM_QUIT)
        {
            break;
        }

        if (::GetMessage(&msg, m_hWnd, 0, 0))
        {
            if (::PeekMessage(&msg, m_hWnd, 0, 0, PM_REMOVE))
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
            else
            {
                break;
            }
        }
    }

    return true;
}

HRESULT MyConsoleWnd::OnEvent(HWND hWnd, UINT, WPARAM, LPARAM)
{
    return E_NOTIMPL;
}

#endif // TEST_GRAPHICS
