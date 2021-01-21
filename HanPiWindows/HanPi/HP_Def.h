// HP_def.h : Ԥ����
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

#define HP_EXTRA_SIZE_DEF   16  // ����Ԥ���ռ�(����)

#define HP_GAL_ENABEL       0   // �Ƿ�����
#define HP_GAL_VISIBLE      2   // �Ƿ���ʾ
#define HP_GAL_STYLE        4   // ���
#define HP_GAL_PROC         8   // ���̺���ָ��

#define HP_GAL_BGCOLOR      12  // ����

#define HP_GBL_BTNHBRUSH    16  // ��ť������ˢ
#define HP_GBL_HOVERHBRUSH  20  // ��ͣ(����)ʱ�Ļ�ˢ
#define HP_GBL_TXTCOLOR     24  // ������ɫ
#define HP_GBL_TXT          28  // ����
#define HP_GBL_FONT         32  // ����

#endif