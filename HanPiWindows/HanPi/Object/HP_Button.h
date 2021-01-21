// HP_Button.h : ��ť
//
#ifndef _HP_BUTTON_H
#define _HP_BUTTON_H

#define HP_BTN_DEFPUSH          0x00000001  
#define HP_BTN_DEFAULT          0x00000002  

#define HP_BTN_DRAWPAINT        0   // ����Ĭ��״̬
#define HP_BTN_DRAWHOVER        1   // ������ͣ״̬
#define HP_BTN_DRAWDOWN         2   // ���ư���״̬
#define HP_BTN_DRAWNO           3   // ���ƽ���״̬

#define HP_BTN_DRAWDOWN_CLOSE   4
#define HP_BTN_DRAWHOVER_CLOSE  5
#define HP_BTN_DRAWPAINT_CLOSE  6

hp_hint HP_CreateButtonW(
    hp_hint hParent,
    hp_hint hFont,
    hp_style style,
    LPCWSTR lpText,
    hp_int x,
    hp_int y,
    hp_int w,
    hp_int h
);
hp_hint HP_CreateButtonA(
    hp_hint hParent,
    hp_hint hFont,
    hp_style style,
    LPCSTR lpText,
    hp_int x,
    hp_int y,
    hp_int w,
    hp_int h
);
#if _UNICODE
#   define HP_CreateButton HP_CreateButtonW
#else
#   define HP_CreateButton HP_CreateButtonA
#endif

#endif