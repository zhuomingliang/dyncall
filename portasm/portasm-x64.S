/*
 Package: portasm
 File: portasm-x64.S
 Description: Portable Assembler Macros for X64
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
.CODE
#  define BEGIN_ASM
#  define END_ASM END
#  define GLOBAL(X) X PROC
#  define BEGIN_PROC(X) 	OPTION PROLOGUE:NONE, EPILOGUE:NONE
#  define END_PROC(X)   X ENDP
#else
	.intel_syntax
	.text
#  define BEGIN_ASM
#  define END_ASM
#  include "autovar_OS.h"
#  if defined (OS_Darwin)
#    define CSYM(X) _##X
#  else
#    define CSYM(X) X
#  endif
#  define RAX %rax
#  define RBX %rbx
#  define RCX %rcx
#  define RDX %rdx
#  define RSI %rsi
#  define RDI %rdi
#  define RBP %rbp
#  define RSP %rsp
#  define R8   %r8
#  define R9   %r9
#  define R10  %r10
#  define R11  %r11
#  define R12  %r12
#  define R13  %r13
#  define R14  %r14
#  define R15  %r15
#  define XMM0 %xmm0
#  define XMM1 %xmm1
#  define XMM2 %xmm2
#  define XMM3 %xmm3
#  define XMM4 %xmm4
#  define XMM5 %xmm5
#  define XMM6 %xmm6
#  define XMM7 %xmm7
#  define AL   %al
#  define GLOBAL(X) .globl CSYM(X)
#  define BEGIN_PROC(X)  CSYM(X):
#  define END_PROC(X)
#  define qword
#  define ptr
#endif

