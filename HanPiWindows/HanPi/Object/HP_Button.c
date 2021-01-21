#include "../HanPi_PCH.h"

void HP_DrawShadow(COLORREF bgColor, HDC mdc, int disWidth, int disHeight) {
    int tmpx = 0, tmpy = 0, tmpw = disWidth, tmph = disHeight;
    for (int i = GetRValue(bgColor); i >= 240; i -= 1) {
        HP_DrawRoundRect(mdc, RGB(i, i, i), 30, tmpx, tmpy, tmpx + tmpw, tmpy + tmph);
        tmpx += 1;
        tmpy += 1;
        tmpw -= 2;
        tmph -= 2;
    }
    tmpx = 8;
    tmpy = 8;
    tmpw = disWidth - 16;
    tmph = disHeight - 6;
    for (int i = GetRValue(bgColor); i >= 207; i -= 3) {
        HP_DrawRoundRect(mdc, RGB(i, i, i), 20, tmpx, tmpy, tmpx + tmpw, tmpy + tmph);
        tmpx += 1;
        tmpy += 1;
        tmpw -= 2;
        tmph -= 2;
    }
}

void HP_DrawBtn(HWND hWnd, HDC* dc, UINT msg)
{
    RECT rect, textrect;
    HDC mdc;
    HBITMAP hOrgBitmap;
    HBITMAP hOldBitmap;
    int disHeight, disWidth;

    GetClientRect(hWnd, &rect);//获取客户区大小
    GetClientRect(hWnd, &textrect);//获取客户区大小

    textrect.left += 14;
    textrect.right -= 14;
    textrect.top += 14;
    textrect.bottom -= 14;

    disHeight = rect.bottom - rect.top;
    disWidth = rect.right - rect.left;

    mdc = CreateCompatibleDC(*dc);//创建当前上下文的兼容dc(内存DC)

    hOrgBitmap = CreateCompatibleBitmap(*dc, disWidth, disHeight);

    hOldBitmap = (HBITMAP)SelectObject(mdc, hOrgBitmap);//将位图加载到内存DC

    HBRUSH tmpBrush = (HBRUSH)GetWindowLongPtr(hWnd, HP_GAL_BGCOLOR);
    FillRect(mdc, &rect, tmpBrush);

    HRGN hrgn;

    LPCWSTR lpText = (LPCWSTR)GetWindowLongPtr(hWnd, HP_GBL_TXT);
    HFONT hFont = (HFONT)GetWindowLongPtr(hWnd, HP_GBL_FONT);
    COLORREF bgColor = RGB(255, 255, 255);//(COLORREF)GetWindowLongPtr(hWnd, HP_GAL_BGCOLOR);
    HBRUSH btnBrush = (HBRUSH)GetWindowLongPtr(hWnd, HP_GBL_BTNHBRUSH);
    HBRUSH hoverBrush = (HBRUSH)GetWindowLongPtr(hWnd, HP_GBL_HOVERHBRUSH);
    COLORREF txtColor = (COLORREF)GetWindowLongPtr(hWnd, HP_GBL_TXTCOLOR);

    switch (msg)
    {
    case HP_BTN_DRAWPAINT:
    {
        hrgn = CreateRoundRectRgn(8, 8, disWidth - 8, disHeight - 8, 3, 3);
        FillRgn(mdc, hrgn, btnBrush);
        //HP_DrawRoundRect(mdc, btnColor, 3, 8, 8, disWidth - 8, disHeight - 8);
        break;
    }
    case HP_BTN_DRAWHOVER:
    {
        HP_DrawShadow(bgColor, mdc, disWidth, disHeight);
        hrgn = CreateRoundRectRgn(8, 8, disWidth - 8, disHeight - 8, 3, 3);
        FillRgn(mdc, hrgn, hoverBrush);
        //HP_DrawRoundRect(mdc, hoverColor, 3, 8, 8, disWidth - 8, disHeight - 8);
        break;
    }
    case HP_BTN_DRAWDOWN:
    {
        HP_DrawShadow(bgColor, mdc, disWidth, disHeight);

        hrgn = CreateRoundRectRgn(8, 8, disWidth - 8, disHeight - 8, 3, 3);
        HBRUSH BlackBrush = CreateSolidBrush(RGB(0, 0, 0));
        FillRgn(mdc, hrgn, BlackBrush);
        DeleteBrush(BlackBrush);

        //HP_DrawRoundRect(mdc, RGB(0, 0, 0), 3, 8, 8, disWidth - 8, disHeight - 8);
        hrgn = CreateRoundRectRgn(10, 10, disWidth - 10, disHeight - 10, 3, 3);
        FillRgn(mdc, hrgn, hoverBrush);
        //HP_DrawRoundRect(mdc, hoverColor, 3, 10, 10, disWidth - 10, disHeight - 10);
        break;
    }
    case HP_BTN_DRAWNO:
    {
        HBRUSH NoBrush = CreateSolidBrush(RGB(204, 204, 204));
        hrgn = CreateRoundRectRgn(8, 8, disWidth - 8, disHeight - 8, 3, 3);
        FillRgn(mdc, hrgn, hoverBrush);
        DeleteBrush(NoBrush);
        //HP_DrawRoundRect(mdc, RGB(204, 204, 204), 3, 8, 8, disWidth - 8, disHeight - 8);
        break;
    }
    break;
    default:
        break;
    }

    HP_DrawText(mdc, txtColor, hFont, &textrect, DT_CENTER | DT_VCENTER | DT_SINGLELINE, lpText);
    //COLORREF crOld = SetTextColor(mdc, txtColor);
    //int nOldMode = SetBkMode(mdc, TRANSPARENT);
    //HFONT hOldFont = (HFONT)SelectObject(mdc, hFont);
    //DrawText(mdc, lpText, lstrlen(lpText), &textrect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    //SetBkMode(mdc, nOldMode);
    //SetTextColor(mdc, crOld);
    //SelectObject(mdc, hOldFont);

    //拷贝内存DC数据块到当前DC，自动拉伸
    StretchBlt(*dc, 0, 0, disWidth, disHeight, mdc, 0, 0, disWidth, disHeight, SRCCOPY);

    //恢复内存原始数据
    SelectObject(mdc, hOldBitmap);

    //删除资源，防止泄漏
    DeleteObject(hOrgBitmap);
    DeleteDC(mdc);
}

LRESULT CALLBACK HP_BtnProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static hp_bool isButtonDown = 0;
    static hp_bool isMouseIn = 0;

    RECT rc;
    int x, y, w, h;
    hp_bool enabel = (hp_bool)GetWindowWord(hWnd, HP_GAL_ENABEL);
    DWORD dwStyle = GetWindowLongPtr(hWnd, HP_GAL_STYLE);
    LPCWSTR lpText = (LPCWSTR)GetWindowLongPtr(hWnd, HP_GBL_TXT);
    HP_ObjectProc Btnproc = (HP_ObjectProc)GetWindowLongPtr(hWnd, HP_GAL_PROC);

    GetClientRect(hWnd, &rc);
    x = rc.left + 8;
    y = rc.top + 8;
    w = rc.right - rc.left - 16;
    h = rc.bottom - rc.top - 16;

    switch (message)
    {
    case WM_SETTEXT:
    {
        SetWindowLongPtr(hWnd, HP_GBL_TXT, (LONG)lParam);
        InvalidateRect(hWnd, &rc, 1);
        UpdateWindow(hWnd);
    }
    break;
    case WM_GETTEXT:
    {
        memcpy((void*)lParam, (void*)GetWindowLongPtr(hWnd, HP_GBL_TXT), HP_SIZE_CHAR * wParam);
        //Debug("wParam: %d", wParam);
        //StringCchCopy((LPWSTR)lParam, wParam, (LPWSTR)GetWindowLongPtr(hWnd, HP_GBL_TXT));
        return wParam;
    }
    break;
    case WM_MOUSEMOVE:
    {
        int xPos = GET_X_LPARAM(lParam);
        int yPos = GET_Y_LPARAM(lParam);
        //if (xPos > x && xPos<x + w && yPos>y && yPos < y + h) {
            if (enabel) {
                SetCursor(LoadCursor(NULL, IDC_HAND));
                if (!isMouseIn) {
                    isMouseIn = 1;
                    TRACKMOUSEEVENT tme;
                    tme.cbSize = sizeof(TRACKMOUSEEVENT);
                    tme.dwFlags = TME_HOVER | TME_LEAVE;
                    tme.dwHoverTime = 10;
                    tme.hwndTrack = hWnd;
                    TrackMouseEvent(&tme);
                }
            }
            else {
                SetCursor(LoadCursor(NULL, IDC_NO));
            }
        /*}
        else {
            SendMessage(hWnd, WM_MOUSELEAVE, 0, 0);
            SetCursor(LoadCursor(NULL, IDC_ARROW));
        }*/
    }
    break;
    case WM_MOUSEHOVER:
    {
        HDC hdc = GetDC(hWnd);
        if(enabel)HP_DrawBtn(hWnd, &hdc, HP_BTN_DRAWHOVER);
        ReleaseDC(hWnd, hdc);
    }
    break;
    case WM_MOUSELEAVE:
    {
        isMouseIn = 0;
        isButtonDown = 0;
        HDC hdc = GetDC(hWnd);

        if (enabel) {
            HP_DrawBtn(hWnd, &hdc, HP_BTN_DRAWPAINT);
        }
        ReleaseDC(hWnd, hdc);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        if (enabel) {
            int xPos = GET_X_LPARAM(lParam);
            int yPos = GET_Y_LPARAM(lParam);
            if (xPos > x && xPos<x + w && yPos>y && yPos < y + h) {
                isButtonDown = 1;
                HDC hdc = GetDC(hWnd);
                if (enabel) {
                    HP_DrawBtn(hWnd, &hdc, HP_BTN_DRAWDOWN);
                }
                ReleaseDC(hWnd, hdc);
            }
        }
    }
    break;
    case WM_LBUTTONUP:
    {
        HDC hdc = GetDC(hWnd);
        if (enabel) {
            if (isMouseIn)HP_DrawBtn(hWnd, &hdc, HP_BTN_DRAWHOVER);
            if (isButtonDown) {
                if(Btnproc)Btnproc((hp_hint)hWnd, WM_LBUTTONUP);
            }
            isButtonDown = 0;
        }
        ReleaseDC(hWnd, hdc);
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        if (enabel) {
            HP_DrawBtn(hWnd, &hdc, HP_BTN_DRAWPAINT);
        }
        else {
            HP_DrawBtn(hWnd, &hdc, HP_BTN_DRAWNO);
        }
        EndPaint(hWnd, &ps);
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

ATOM HP_RegBtnClass()
{
    static int isRegClass = 0;
    if (!isRegClass) {

        WNDCLASSEX wcex = { 0 };

        wcex.cbSize = sizeof(WNDCLASSEX);

        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = HP_BtnProc;
        wcex.cbWndExtra = HP_EXTRA_SIZE_DEF + 20;
        wcex.hInstance = GetModuleHandle(0);
        wcex.hCursor = LoadCursor(NULL, IDC_HAND);
        wcex.lpszClassName = L"HanPi.Control.Button";

        isRegClass = 1;

        return RegisterClassEx(&wcex);
    }
    else return 0;
}

hp_hint HP_CreateButtonW(hp_hint hParent, hp_hint hFont, hp_style style, LPCWSTR lpText, hp_int x, hp_int y, hp_int w, hp_int h)
{
    HP_RegBtnClass();
    HWND hWnd = CreateWindowW(
        L"HanPi.Control.Button",
        NULL,
        WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
        x - 8,
        y - 8,
        w + 16,
        h + 16,
        (HWND)hParent,
        NULL,
        GetModuleHandle(0),
        NULL
    );

    if (hWnd) {
        SetWindowWord(hWnd, HP_GAL_ENABEL, 1);
        SetWindowWord(hWnd, HP_GAL_VISIBLE, 1);
        SetWindowLongPtr(hWnd, HP_GAL_STYLE, style);

        HBRUSH bgHbr;
        if (hParent)
        {
            bgHbr = (HBRUSH)GetWindowLongPtr((HWND)hParent, HP_GAL_BGCOLOR);
        }
        else
        {
            bgHbr = CreateSolidBrush(RGB(255, 255, 255));
        }

        HBRUSH btnHbr = CreateSolidBrush(RGB(0, 103, 184)), hoverHbr = CreateSolidBrush(RGB(0, 93, 166));
        if (style & HP_BTN_DEFPUSH)
        {

        }
        else if (style & HP_BTN_DEFAULT) {
            //btnColor = RGB(180, 180, 180);
            //hoverColor = RGB(160, 160, 160);
        }
        
        SetWindowLongPtr(hWnd, HP_GAL_BGCOLOR, (LONG)bgHbr);
        SetWindowLongPtr(hWnd, HP_GBL_BTNHBRUSH, (LONG)btnHbr);
        SetWindowLongPtr(hWnd, HP_GBL_HOVERHBRUSH, (LONG)hoverHbr);
        SetWindowLongPtr(hWnd, HP_GBL_TXTCOLOR, RGB(255, 255, 255));
        SetWindowLongPtr(hWnd, HP_GBL_TXT, (LONG)lpText);
        SetWindowLongPtr(hWnd, HP_GBL_FONT, (LONG)hFont);
    }
    return (hp_hint)hWnd;
}

hp_hint HP_CreateButtonA(hp_hint hParent, hp_hint hFont, hp_style style, LPCSTR lpText, hp_int x, hp_int y, hp_int w, hp_int h)
{
    HP_RegBtnClass();
    HWND hWnd = CreateWindowW(
        L"HanPi.Control.Button",
        NULL,
        WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
        x - 8,
        y - 8,
        w + 16,
        h + 16,
        (HWND)hParent,
        NULL,
        GetModuleHandle(0),
        NULL
    );

    if (hWnd) {
        SetWindowWord(hWnd, HP_GAL_ENABEL, 1);
        SetWindowWord(hWnd, HP_GAL_VISIBLE, 1);
        SetWindowLongPtr(hWnd, HP_GAL_STYLE, style);
        HBRUSH bgHbr = CreateSolidBrush(RGB(255, 255, 255));
        HBRUSH btnHbr = CreateSolidBrush(RGB(0, 103, 184)), hoverHbr = CreateSolidBrush(RGB(0, 93, 166));
        if (style & HP_BTN_DEFPUSH)
        {

        }
        else if (style & HP_BTN_DEFAULT) {
            //btnColor = RGB(180, 180, 180);
            //hoverColor = RGB(160, 160, 160);
        }

        SetWindowLongPtr(hWnd, HP_GAL_BGCOLOR, (LONG)bgHbr);
        SetWindowLongPtr(hWnd, HP_GBL_BTNHBRUSH, (LONG)btnHbr);
        SetWindowLongPtr(hWnd, HP_GBL_HOVERHBRUSH, (LONG)hoverHbr);
        SetWindowLongPtr(hWnd, HP_GBL_TXTCOLOR, RGB(255, 255, 255));
        SetWindowLongPtr(hWnd, HP_GBL_TXT, (LONG)lpText);
        SetWindowLongPtr(hWnd, HP_GBL_FONT, (LONG)hFont);
    }
    return (hp_hint)hWnd;
}