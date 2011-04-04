#if defined(GEN_MASM)
.386
.MODEL FLAT
.CODE
#  define BEGIN_ASM
#  define END_ASM END
#  define GLOBAL(X) _##X PROC
#  define BEGIN_PROC(X) 	OPTION PROLOGUE:NONE, EPILOGUE:NONE
#  define END_PROC(X)   _##X ENDP
#  define HEX(X) X##h
#else
	.intel_syntax
	.text
#  define BEGIN_ASM
#  define END_ASM 
#  include "dyncall_macros.h"
#  if defined(DC__OS_Win32) || defined(DC__OS_Cygwin) || defined(DC__OS_MinGW) || defined(DC__OS_Darwin)
#    define CSYM(X) _##X
#  else
#    define CSYM(X) X
#  endif
/* Systems that work without '%' prefix: MinGW,Apple */
#  define EAX %eax
#  define EBX %ebx
#  define ECX %ecx
#  define EDX %edx
#  define ESI %esi
#  define EDI %edi
#  define EBP %ebp
#  define ESP %esp
#  define GLOBAL(X) .globl CSYM(X)
#  define BEGIN_PROC(X)  CSYM(X):
#  define END_PROC(X)
#  define HEX(X) 0x##X
#endif

