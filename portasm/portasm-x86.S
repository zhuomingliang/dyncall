/*
 Package: portasm
 File: portasm-x86.S
 Description: Portable Assembler Macros for x86
 License:
 Copyright (c) 2011      Daniel Adler <dadler@uni-goettingen.de>

 Permission to use, copy, modify, and distribute this software for any
 purpose with or without fee is hereby granted, provided that the above
 copyright notice and this permission notice appear in all copies.

 THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
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
#  include "autovar_OS.h"
#  if defined(OS_Win32) || defined(OS_Cygwin) || defined(OS_MinGW) || defined(OS_Darwin) || defined(OS_Minix)
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

