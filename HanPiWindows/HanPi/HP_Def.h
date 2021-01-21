// HP_def.h : 预定义
//
#ifndef _HP_DEF_H
#define _HP_DEF_H

#ifdef _WIN32
#   ifdef _WIN64
#       define HP_x64   1
#   else
#       define HP_x86   1
#   endif
#else
#   ifdef __x86_64__
#       define HP_x64   1
#   elif __i386__
#       define HP_x86   1
#   else
#       error(Unknown_System_Info)
#   endif
#endif

#if _UNICODE
#define HP_SIZE_CHAR        sizeof(hp_wchar)
#else
#define HP_SIZE_CHAR        sizeof(hp_char)
#endif

#define HP_EXTRA_SIZE_DEF   16  // 对象预留空间(基础)

#define HP_GAL_ENABEL       0   // 是否启用
#define HP_GAL_VISIBLE      2   // 是否显示
#define HP_GAL_STYLE        4   // 风格
#define HP_GAL_PROC         8   // 过程函数指针

#define HP_GAL_BGCOLOR      12  // 背景

#define HP_GBL_BTNHBRUSH    16  // 按钮背景画刷
#define HP_GBL_HOVERHBRUSH  20  // 悬停(按下)时的画刷
#define HP_GBL_TXTCOLOR     24  // 文字颜色
#define HP_GBL_TXT          28  // 文字
#define HP_GBL_FONT         32  // 字体

#endif