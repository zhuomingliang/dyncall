#ifndef AUTOVAR_ABI_H
#define AUTOVAR_ABI_H

#include "autovar_OS.h"

#if defined(OS_Win32) || defined(OS_Win64) || defined(OS_Cygwin) || defined(OS_MinGW)
#define ABI_PE
#elif defined(OS_Darwin)
#define ABI_Mach
#else
#define ABI_ELF
# if defined(__LP64__) || defined(_LP64)
#   define ABI_ELF64
# else
#   define ABI_ELF32
# endif
#endif

#endif /* AUTOVAR_ABI_H */

