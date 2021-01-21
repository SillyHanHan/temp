// HP_Object.h : ∂‘œÛ
//
#ifndef _HP_OBJECT_H
#define _HP_OBJECT_H

typedef unsigned long           hp_style;

typedef hp_ptrval               hp_hint;

typedef struct _HP_Object
{
    hp_hint hint;
    hp_int x;
    hp_int y;
    hp_int w;
    hp_int h;
    hp_style style;
}hp_object;
typedef hp_long(*HP_ObjectProc)(hp_hint, hp_ulong);

#include "HP_Window.h"
#include "HP_Button.h"
#include "HP_EditBox.h"

#endif