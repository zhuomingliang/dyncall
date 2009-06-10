#include "dyncall_macros.h"

#if defined(DC__OS_Darwin)
#if defined(DC__Arch_Intel_x86)
#include "dyncall_callback_x86_apple.s"
#elif defined(DC__Arch_AMD64)
#include "dyncall_callback_x64_apple.s"
#elif defined(DC__Arch_PowerPC)
#include "dyncall_callback_ppc32_apple.s"
#endif
#else
#if defined(DC__Arch_Intel_x86)
#include "dyncall_callback_x86_gas.s"
#elif defined(DC__Arch_AMD64)
#include "dyncall_callback_x64_gas.s"
#elif defined(DC__Arch_PowerPC)
#include "dyncall_callback_ppc32_gas.s"
#endif
#endif

