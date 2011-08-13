#if defined(__GNUC__)

#if defined(DC__ABI_MIPS_O32)
#include "dyncall_callvm_mips_o32.c"
#elif defined(DC__ABI_MIPS_N64)
#include "dyncall_callvm_mips_n64.c"
#elif defined(DC__ABI_MIPS_N32)
#include "dyncall_callvm_mips_n32.c"
#else
#include "dyncall_callvm_mips_eabi.c"
#endif

#endif

