// HanPi_PCH.h : 
//

#ifndef _HANPI_PCH_H
#define _HANPI_PCH_H

#include <Windows.h>
#include <WindowsX.h>

#include "../resource.h"

#if _DEBUG
#include <stdio.h>
#define Debug(_str,...) printf("DEBUG > "_str"\n",__VA_ARGS__)
#else
//#include <stdio.h>
#define Debug(_str,...) ((void)0)//printf("DEBUG > "_str"\n",__VA_ARGS__)
#endif

#include "HP_Def.h"
#include "HP_type.h"

#include "HP_Font.h"

#include "HP_Draw.h"

#include "Object/HP_Object.h"

#endif