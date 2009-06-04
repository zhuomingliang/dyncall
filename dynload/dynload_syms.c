#include "dyncall_macros.h"
#if defined(DC_WINDOWS)
# include "dynload_syms_pe32.c"
#elif defined(DC__OS_Linux)
# include "dynload_syms_elf.c"
#else
void dummy() { }
#endif

 
