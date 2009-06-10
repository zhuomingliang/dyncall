#include "dyncall_macros.h"

#ifdef DC_WINDOWS
#include "dyncall_alloc_wx_win32.c"
#else
#include "dyncall_alloc_wx_mmap.c"
#endif

