#include "../../dyncall/dyncall_macros.h"

#ifdef DC__OS_PSP

#include <pspdebug.h>
#define printf pspDebugScreenPrintf

#else

#include <stdio.h>

#endif

