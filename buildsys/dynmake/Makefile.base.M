#include "../../dyncall/dyncall_macros.h"

#if defined(DC_WINDOWS)

/* Abstractions */
#define _(X)      $(X)         /* Standard variables */
#define _L(X)     X.lib
#define _O(X)     X.obj

#define TARGET   @
#define PREREQS  **

/* Makefile internal vars for platform abstraction */
MAKEFLAGS_USER = /NOLOGO
MAKEFLAG_FILE = /f
MAKE_DEFAULT_FILE = dynMakefile
SHELL_COMMAND_SEPARATOR = &&

AR = lib
ARFLAGS_USER = /NOLOGO
ARFLAGS = 
ARFLAG_OUT_PREFIX = /OUT:

CFLAGS_USER = /nologo
CFLAGS      = _(CFLAGS) _(CFLAGS_USER)

ASLAGS_USER = /NOLOGO
ASLAGS      = _(AFLAGS) _(ASLAGS_USER)
ALAGS      = _(ASFLAGS) /* Set AFLAGS (without 'S'), which is the standard nmake predefined macro for MASM */

.SUFFIXES : .S

.S.obj:
	cl /nologo /EP $< > $*.asm
	_(AS) _(ASFLAGS) _(ASFLAGS_USER) /nologo /c $*.asm
	del $*.asm


#else

/* Abstractions */
#define _(X)      ${X}         /* Standard variables */
#define _L(X)     lib##X.a
#define _O(X)     X.o

#define _TARGET   @
#define _PREREQS  <

/* Makefile internal vars for platform abstraction */
MAKEFLAGS_USER = 
MAKEFLAG_FILE = -f
MAKE_DEFAULT_FILE = dynMakefile
SHELL_COMMAND_SEPARATOR = ;

ARFLAG_OUT_PREFIX = /OUT:

CFLAGS_USER = 
CFLAGS      = _(CFLAGS) _(CFLAGS_USER)

ASLAGS_USER = 

#endif

