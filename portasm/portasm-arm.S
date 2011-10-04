#define BEGIN_ASM	.text
#include "../autovar/autovar_OS.h"
#if defined(OS_Darwin)
#define GLOBAL_C(X) .globl _##X
#define ENTRY_C(X) _##X:
#else
#define GLOBAL_C(X) .globl X
#define ENTRY_C(X) X:
#endif

