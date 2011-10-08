#include "../../dyncall/dyncall_macros.h"

#if defined(DC_WINDOWS)

/* Abstractions */
#define _(X)      $(X)         /* Standard variables */
#define _L(X)     X.lib
#define _O(X)     X.obj

#define TARGET   @
#define PREREQS  **

/* Makefile internal vars for platform abstraction */
MAKE_FLAG  = /f
MAKE_DEFAULT_FILE = dynMakefile
SHELL_COMMAND_SEPARATOR = &&

AR = lib
ARFLAGS = /NOLOGO
ARFLAG_OUT_PREFIX = /OUT:

.SUFFIXES : .S

.S.obj:
	cl /EP $< > $*.asm
	$(AS) $(AFLAGS) /c $*.asm
	del $*.asm


#else

/* Abstractions */
#define _(X)      ${X}         /* Standard variables */
#define _L(X)     lib##X.a
#define _O(X)     X.o

#define _TARGET   @
#define _PREREQS  <

/* Makefile internal vars for platform abstraction */
MAKE_FLAG  = -f
MAKE_DEFAULT_FILE = dynMakefile
SHELL_COMMAND_SEPARATOR = ;

ARFLAG_OUT_PREFIX = /OUT:

#endif


