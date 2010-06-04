#if defined(__GNUC__)

#if defined(_ABIO32)
#include "dyncall_callvm_mips_o32.c
#elif defined(_ABI64)
#include "dyncall_callvm_mips_n64.c
#else
#include "dyncall_callvm_mips_eabi.c
#endif

#endif

