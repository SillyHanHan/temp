// HP_Window.h : หตร๗
//
#ifndef _HP_WINDOW_H
#define _HP_WINDOW_H

hp_hint HP_CreateWindowW(
    LPCWSTR title,
    hp_int x,
    hp_int y,
    hp_int w,
    hp_int h,
    hp_hint windowParent,
    hp_style style
);

hp_hint HP_CreateWindowA(
    LPCSTR title,
    hp_int x,
    hp_int y,
    hp_int w,
    hp_int h,
    hp_hint windowParent,
    hp_style style
);
#if _UNICODE
#   define HP_CreateWindow HP_CreateWindowW
#else
#   define HP_CreateWindow HP_CreateWindowA
#endif

#endif