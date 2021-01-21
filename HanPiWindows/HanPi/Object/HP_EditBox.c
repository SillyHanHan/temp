// HP_EditBox.c : 文本框的实现
//
#include "../HanPi_PCH.h"

LRESULT CALLBACK HP_TextBoxProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    RECT rc;
    GetClientRect(hWnd, &rc);
    int x, y, w, h;
    x = rc.left;
    y = rc.top;
    w = rc.right - rc.left;
    h = rc.bottom - rc.top;

    switch (uMsg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            HP_DrawBorder(hdc, RGB(0, 0, 0), 2, 0, 0, rc.right, rc.bottom);
            EndPaint(hWnd, &ps);
            break;
        }
        case WM_MOUSEMOVE:
        {
            SetCursor(LoadCursor(NULL, IDC_IBEAM));
            break;
        }
        case WM_LBUTTONUP:
        {
            HDC hdc = GetDC(hWnd);
            
            ReleaseDC(hWnd, hdc);
        }
        break;
        case WM_CLOSE:
        {
            SendMessage(hWnd, WM_DESTROY, 0, 0);
            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
            break;
        }
    return 0;
}

ATOM HP_RegTextBoxClass()
{
    static hp_bool isRegClass = 0;
    if (!isRegClass) {

        WNDCLASSEX wcex = { 0 };

        wcex.cbSize = sizeof(WNDCLASSEX);

        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = HP_TextBoxProc;
        wcex.cbWndExtra = HP_EXTRA_SIZE_DEF;
        wcex.hInstance = GetModuleHandle(0);
        //wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
        wcex.lpszClassName = TEXT("HanPi.Control.TextBox");

        isRegClass = 1;

        return RegisterClassEx(&wcex);
    }
    else return 0;
}

hp_hint HP_CreateEditBoxW(LPCWSTR defText, hp_int x, hp_int y, hp_int w, hp_int h, hp_hint windowParent, hp_style style)
{
    HP_RegTextBoxClass();
    hp_hint window = (hp_hint)CreateWindowW(
        TEXT("HanPi.Control.TextBox"),
        NULL,
        WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
        x, y, w, h,
        (HWND)windowParent,
        NULL,
        GetModuleHandle(0),
        NULL
    );
    if (!window)return 0;
    //SetWindowLongPtr((HWND)window, HP_GAL_BGCOLOR, );
    ShowWindow((HWND)window, SW_SHOW);
    UpdateWindow((HWND)window);
    return window;
}
