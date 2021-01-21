// HP_EditBox.h : нд╠╬©Р
//
#ifndef _HP_EDITBOX_H
#define _HP_EDITBOX_H

hp_hint HP_CreateEditBoxW(
    LPCWSTR defText,
    hp_int x,
    hp_int y,
    hp_int w,
    hp_int h,
    hp_hint windowParent,
    hp_style style
);

#if _UNICODE
#   define HP_CreateEditBox HP_CreateEditBoxW
#else
//#   define HP_HP_CreateEditBox HP_CreateEditBoxA
#endif

#endif