// HP_Window.c : หตร๗
//
#include "../HanPi_PCH.h"

LRESULT CALLBACK HP_WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    RECT rect;
    HBRUSH bgHbr = NULL;
    switch (uMsg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            GetClientRect(hWnd, &rect);
            bgHbr = (HBRUSH)GetWindowLongPtr(hWnd, HP_GAL_BGCOLOR);
            FillRect(hdc, &rect, bgHbr);
            DeleteObject((HGDIOBJ)bgHbr);
            EndPaint(hWnd, &ps);
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

ATOM HP_RegWindowClass()
{
    static hp_bool isRegClass = 0;
    if (!isRegClass) {

        WNDCLASSEX wcex = { 0 };

        wcex.cbSize = sizeof(WNDCLASSEX);

        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = HP_WindowProc;
        wcex.cbWndExtra = HP_EXTRA_SIZE_DEF;
        wcex.hInstance = GetModuleHandle(0);
        wcex.hIcon = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));
        wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
        //wcex.hbrBackground = NULL;//(HBRUSH)(CreateSolidBrush(RGB(255, 255, 255)));
        //wcex.lpszMenuName = MAKEINTRESOURCEW(NULL);
        wcex.lpszClassName = TEXT("HanPi.Window");
        wcex.hIconSm = /*NULL;*/LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

        isRegClass = 1;

        return RegisterClassEx(&wcex);
    }
    else return 0;
}

hp_hint HP_CreateWindowW(LPCWSTR title, hp_int x, hp_int y, hp_int w, hp_int h, hp_hint windowParent, hp_style style)
{
    HP_RegWindowClass();
    hp_hint window = (hp_hint)CreateWindowW(
        TEXT("HanPi.Window"),
        title,
        WS_SYSMENU | WS_SIZEBOX,
        x, y, w, h,
        (HWND)windowParent,
        NULL,
        GetModuleHandle(0),
        NULL
    );
    if (!window)return 0;
    SetWindowLongPtr((HWND)window, HP_GAL_BGCOLOR, (LONG)CreateSolidBrush(RGB(255, 255, 255)));
    ShowWindow((HWND)window, SW_SHOW);
    UpdateWindow((HWND)window);
    return window;
}

hp_hint HP_CreateWindowA(LPCSTR title, hp_int x, hp_int y, hp_int w, hp_int h, hp_hint windowParent, hp_style style)
{
    HP_RegWindowClass();
    hp_hint window = (hp_hint)CreateWindowA(
        "HanPi.Window",
        title,
        WS_SYSMENU | WS_SIZEBOX,
        x, y, w, h,
        (HWND)windowParent,
        NULL,
        GetModuleHandle(0),
        NULL
    );
    if (!window)return 0;

    ShowWindow((HWND)window, SW_SHOW);
    UpdateWindow((HWND)window);
    return window;
}