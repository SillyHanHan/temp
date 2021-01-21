#include <stdio.h>
#include <time.h>
#include "HanPi/HanPi_PCH.h"

#pragma comment (lib, "winmm.lib")

HFONT hfont;

DWORD WINAPI HP_MusicThread(LPVOID lpParam)
{
    WCHAR s[200];
    hp_hint h = (hp_hint)lpParam;
    mciSendString(TEXT("open music.mp3 alias sounder"), s, 200, NULL);
    //Debug("%ws", s);

    mciSendString(TEXT("play sounder wait repeat"), s, 200, NULL);
    //Debug("%ws", s);

    //SetWindowWord((HWND)h, HP_GAL_ENABEL, 1);
    //RECT rc;
    //GetClientRect((HWND)h, &rc);
    //InvalidateRect((HWND)h, &rc, 1);
    //UpdateWindow((HWND)h);
    return 0;
}

int i,lastr=1 ,  r, vis[50];
DWORD WINAPI HP_RandThread(LPVOID lpParam)
{

    HWND ph = GetParent((HWND)lpParam);
    HDC hdc = GetDC(ph);
    RECT textrect = (RECT){ 340,100,440,200 };
    //GetClientRect(hWnd, &textrect);
    WCHAR s[200];

    if (i >= 46)
    {
        HP_DrawRect(hdc, RGB(255, 255, 255), 340, 100, 440, 200);
        HP_DrawText(hdc, RGB(200, 0, 0), hfont, &textrect, DT_CENTER | DT_VCENTER | DT_SINGLELINE, L"已抽完!");
        Debug("Rand OK! 46/46");
        puts("ohhhhhhhh!\n\
            渺小的德军 在融化尘埃\n\
            这期盼光明 为宣召的国\n\
            把心胸描染 这鲜红的夜\n\
            在必胜光芒 向敌人阵地鞭挞！\n\
            仓皇的德军 全部化尘埃\n\
            这期盼光明 为宣召的国\n\
            把心胸描染 这鲜红的夜\n\
            在必胜光芒 向敌人阵地鞭挞！\n\
\n\
            激昂的老兵 像雄鹰的头\n\
            守护着人类 把躯体奉献\n\
            爬上了光明 你期盼的国！\n\
            把苍海道路 宣泄成平野\n\
            血战的老兵 抬胸仰着头\n\
            守护着人类 把躯体奉献\n\
            爬上了光明 你期盼的国！\n\
            把苍海道路 宣泄成平野\n\
            乌拉！乌拉！\n\
\n\
            渺小的德军 在融化尘埃\n\
            这期盼光明 为宣召的国\n\
            把心胸描染 这鲜红的\n\
            在必胜光芒 向敌人阵地鞭挞！\n\
            仓皇的德军 全部化尘埃\n\
            这必胜光明 为宣召的国\n\
            把心胸描染 这鲜红的夜\n\
            在必胜光芒 向敌人阵地鞭挞！\n\
            乌拉！乌拉！");
        return 0;
    }

    do
    {
        r = rand() % 46 + 1;
        Debug("Rand : %d", r);
        wsprintf(s, L"%d 号", r);
        HP_DrawRect(hdc, RGB(255, 255, 255), 340, 100, 440, 200);
        HP_DrawText(hdc, RGB(0, 0, 0), hfont, &textrect, DT_CENTER | DT_VCENTER | DT_SINGLELINE, s);
        Sleep(10);
    } while (vis[r]);
    vis[r] = 1;
    i++;
    Debug("%d Choose %d (%d/46)", lastr,r, i);
    lastr = r;
    SetWindowWord((HWND)lpParam, HP_GAL_ENABEL, 1);
    RECT rc;
    GetClientRect((HWND)lpParam, &rc);
    InvalidateRect((HWND)lpParam, &rc, 1);
    UpdateWindow((HWND)lpParam);
    ReleaseDC(ph, hdc);
    return 0;
}

hp_long proc(hp_hint h, hp_uint m)
{

    HWND ph = (HWND)GetParent((HWND)h);
    HDC hdc = GetDC(ph);
    RECT textrect = (RECT){ 100,100,300,200 };
    //GetClientRect(hWnd, &textrect);
    HP_DrawRect(hdc, RGB(255, 255, 255), 100, 100, 300, 200);
    HP_DrawText(hdc, RGB(0, 0, 0), hfont, &textrect, DT_CENTER | DT_VCENTER | DT_SINGLELINE, TEXT("本次抽到的是: "));

    ReleaseDC(ph, hdc);

    DWORD id;
    HANDLE hThread;
    hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HP_RandThread, (LONG)h, 0, &id);
    if (!hThread)
    {
        Debug("Can't create rand thread");
        return 0;
    }

    //GetWindowText((HWND)h, s, 7);
    //MessageBox((HWND)h, s, TEXT(""), 0);
    
    SetWindowWord((HWND)h, HP_GAL_ENABEL, 0);
    RECT rc;
    GetClientRect((HWND)h, &rc);
    InvalidateRect((HWND)h, &rc, 1);
    UpdateWindow((HWND)h);
    return 0;
}

hp_long procBtn(hp_hint h, hp_uint m)
{
    MessageBox((HWND)h, L"btnpush", L"", 0);
    return 0;
}

int main()
{
    srand(time(NULL));
    DWORD id;
    HANDLE hThread;
    //hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HP_MusicThread, 0, 0, &id);
    /*if (!hThread)
    {
        Debug("Can't create music thread");
        return 0;
    }*/
    hp_hint w=HP_CreateWindow( TEXT("HanPiWindow"), 0, 0, 600, 400, 0, 0);

    hfont = CreateFont(
        -20,
        0,
        0,
        0,
        FW_BOLD,
        0,
        0,
        0,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH,
        L"Microsoft YaHei UI"//Segoe UI//
    );
    
    hp_hint ah = HP_CreateButton(w, (hp_hint)hfont, 0, L"乌拉!", 220, 250, 150, 46);
    hp_hint eh = HP_CreateEditBox(TEXT("123"), 100, 100, 200, 40, w, 0);
    //SetWindowText((HWND)ah, TEXT("GiuGiu"));
    SetWindowLongPtr((HWND)ah, HP_GAL_PROC, (LONG)procBtn);
    //system("pause");
    MSG msg;
    // 主消息循环:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        //printf("%x\n", msg.message);
        //printf("%1u\n", msg.message);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
    //return 0;
}