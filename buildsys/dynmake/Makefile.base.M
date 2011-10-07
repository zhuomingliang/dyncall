#include "../../dyncall/dyncall_macros.h"

#if defined(DC_WINDOWS)

/* Abstractions */
#define _(X)      $(X)         /* Standard variables */
#define _L(X)     X##.lib
#define _O(X)     X##.obj

/* Makefile internal vars for platform abstraction */
MAKE_FLAG  = /f
MAKE_DEFAULT_FILE = dynMakefile
SHELL_COMMAND_SEPARATOR = &&


.SUFFIXES : .S

.S.obj:
	cl /EP $< > $*.asm
	$(AS) $(AFLAGS) /c $*.asm
	del $*.asm


#else

/* Abstractions */
#define _(X)      ${X}         /* Standard variables */
#define _L(X)     lib##X##.a
#define _O(X)     X##.o

/* Makefile internal vars for platform abstraction */
MAKE_FLAG  = -f
MAKE_DEFAULT_FILE = dynMakefile
SHELL_COMMAND_SEPARATOR = ;

#endif


