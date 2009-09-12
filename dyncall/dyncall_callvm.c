#include "dyncall_macros.h"
#if defined(DC__Arch_Intel_x86)
#  include "dyncall_callvm_x86.c"
#elif defined(DC__Arch_AMD64)
#  include "dyncall_callvm_x64.c"
#elif defined(DC__Arch_PowerPC)
#  include "dyncall_callvm_ppc32.c"
#elif defined(DC__Arch_PPC64)
#  include "dyncall_callvm_ppc64.c"
#elif defined(DC__Arch_MIPS)
#  include "dyncall_callvm_mips.c"
#elif defined(DC__Arch_ARM_ARM)
#  include "dyncall_callvm_arm9_arm.c"
#elif defined(DC__Arch_ARM_THUMB)
#  include "dyncall_callvm_arm9_thumb.c"
#else
#  error unsupported platform
#endif

