#include "dyncall_macros.h"
#if defined(DC_WINDOWS)
#include "dynload_win32.c"
#elif defined(DC_UNIX)
#include "dynload_unix.c"
#endif

