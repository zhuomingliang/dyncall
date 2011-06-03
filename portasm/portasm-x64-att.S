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
/* Common macros. */
#define XCONCAT(A,B) A##B
#if defined(GEN_MASM)
/* MASM syntax. */
.CODE
#  define BEGIN_ASM
#  define END_ASM END
#  define GLOBAL(X) X PROC
#  define BEGIN_PROC(X) 	OPTION PROLOGUE:NONE, EPILOGUE:NONE
#  define END_PROC(X)   X ENDP
#  define PUSHQ(R) push R
#  define POPQ(R) pop R
#  define MOVL(S,D) mov D,S
#  define ADDL(S,D) add D,S
#  define ANDL(S,D) and D,S
#  define SUBL(S,D) sub D,S
#  define SHRL(S,D) shr D,S
#  define RET() ret
#  define CALL_DWORD(R,OFF) call DWORD(R,OFF)
#  define REP(X) rep X
#  define MOVSB movsb
#  define MOVSW movsw
#  define MOVSD movsd
#  define DWORD(R,OFF) dword ptr [R+OFF]
#  define QWORD(R,OFF) qword ptr [R+OFF]
#  define LIT(X) X
#  define INT(X) int X
#  define HEX(X) XCONCAT(X,h)
#  define CALL(X) call X
#else
/* GNU/SunPor Assembler AT&T Syntax */
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
#  define PUSHQ(R) pushq R
#  define POPQ(R) popq R
#  define MOVB(S,D) movb S,D
#  define MOVL(S,D) movl S,D
#  define ADDL(S,D) addl S,D
#  define ANDL(S,D) andl S,D
#  define SUBL(S,D) subl S,D
#  define SHRL(S,D) shrl S,D
#  define MOVQ(S,D) movq S,D
#  define ADDQ(S,D) addq S,D
#  define ANDQ(S,D) andq S,D
#  define SUBQ(S,D) subq S,D
#  define SHRQ(S,D) shrq S,D
#  define MOVD(S,D) movd S,D
#  define RET() ret
#  define CALL_DWORD(R,OFF) call *DWORD(R,OFF)
#  define REP(X) rep X
#  define MOVSB movsb
#  define MOVSW movsw
#  define MOVSD(S,D) movsd S,D
#  define DWORD(R,OFF) OFF(R)
#  define QWORD(R,OFF) OFF(R)
#  define LIT(X) $X
#  define INT(X) int X
#  define HEX(X) XCONCAT(0x,X)
#  define CALL(X) call X
#  define LEA(A,B) lea A,B
#  define CMP(A,B) cmp A,B
#  define JE(X)    je X
#  define FLDS(X)  flds X
#  define FLDL(X)  fldl X
#  define ADD(A,B) add A,B
#endif

