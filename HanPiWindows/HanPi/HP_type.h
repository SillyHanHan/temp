// HP_type.h : 没毛用的定义
// 看上去很nb
#ifndef _HP_TYPE_H
#define _HP_TYPE_H

#define     HP_TYPE(type,dest)  (*((type*)(void*)(&dest)))

typedef     void                hp_void;

typedef     signed char         hp_bool;

typedef     unsigned short      hp_word;
typedef     unsigned int        hp_dword;
typedef     unsigned long long  hp_qword;

typedef     signed char         hp_char;

typedef     unsigned short      hp_wchar;
typedef     unsigned char       hp_uchar, hp_byte;

typedef     signed short        hp_short, hp_int16;
typedef     unsigned short      hp_ushort;

typedef     signed int          hp_int32, hp_int;
typedef     unsigned int        hp_uint32, hp_uint;

typedef     signed long         hp_long;
typedef     unsigned long       hp_ulong;

typedef     signed long long    hp_int64;
typedef     unsigned long long  hp_uint64;

typedef     float			    hp_float, hp_float32;
typedef     double			    hp_double, hp_double64;

typedef     void*               hp_ptr;

#if HP_x64
typedef hp_int64                hp_ptrval;
typedef hp_uint64               hp_size;
#elif HP_x86
typedef hp_int32                hp_ptrval;
typedef hp_uint32               hp_size;
#endif // HP_x64

typedef struct _hp_string
{
    hp_char* buffer;
    hp_size bufferlen;
    hp_size maxlen;
}hp_string;

#endif