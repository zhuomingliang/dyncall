/*/////////////////////////////////////////////////////////////////////////////

 Copyright (c) 2007-2009 Daniel Adler <dadler@uni-goettingen.de>, 
                         Tassilo Philipp <tphilipp@potion-studios.com>

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

/////////////////////////////////////////////////////////////////////////////*/

/*///////////////////////////////////////////////////////////////////////

	dyncall__call_x64_gas.s

	SystemV x64 calls for GAS
	November 28, 2007

/*///////////////////////////////////////////////////////////////////////

.text

#include "dyncall_macros.h"
#if defined(DC__OS_Win32) || defined(DC__OS_Cygwin) || defined(DC__OS_MinGW) || defined(DC__OS_Darwin)
#define CSYM(X) _##X
#else
#define CSYM(X) X
#endif

.globl CSYM(dcCall_x64_sysv)
	// .type dcCall_x64_sysv, @function

CSYM(dcCall_x64_sysv):

	/* arguments: */
	/* rdi : size of arguments to be passed via stack */
	/* rsi : pointer to arguments to be passed via the stack */
	/* rdx : pointer to arguments of integral/pointer type to be passed via registers */
	/* rcx : pointer to arguments of floating point type to be passed via registers */
	/* r8  : target function pointer */

	push		%rbp						/* Pseudo-prolog - preserve rbp. */
	push		%rbx						/* Preserve rbx and store pointer to function in it. */

	movq			%rsp, %rbp				/* Store stack pointer in rbp. */

	movq			%r8, %rbx

	movsd		  (%rcx), %xmm0	/* Copy first 8 floats to xmm0-xmm7 (this makes rcx free to use). */
	movsd		 8(%rcx), %xmm1
	movsd		16(%rcx), %xmm2
	movsd		24(%rcx), %xmm3
	movsd		32(%rcx), %xmm4
	movsd		40(%rcx), %xmm5
	movsd		48(%rcx), %xmm6
	movsd		56(%rcx), %xmm7

	subq			%rdi,%rsp					/* Setup stack frame by subtracting the size of the arguments. */

	mov			%rdi, %rax				/* Align stack. */
	add			$8,   %rax
	and			$15,  %rax
	sub			%rax, %rsp

	mov			%rdi, %rcx			/* Store number of bytes to copy to stack in rcx (for rep movsb). */
	mov			%rsp, %rdi					/* Store pointer to beginning of stack arguments in rdi (for rep movsb). */

	rep movsb	/* @@@ should be optimized (e.g. movq) */

	mov			(%rdx), %rdi	/* Copy first six int/pointer arguments to rdi, rsi, rdx, rcx, r8, r9. */
	mov			8(%rdx), %rsi
	mov			24(%rdx), %rcx
	mov			32(%rdx), %r8
	mov			40(%rdx), %r9
	mov			16(%rdx), %rdx		/* Set rdx last to not overwrite it to soon. */

	mov			$8, %al						/* Put upper bound of number of used xmm registers in al. */
	call			*%rbx						/* Invoke function. */

	mov			%rbp, %rsp					/* Restore stack pointer (such that we can pop the preserved values). */

	pop			%rbx						/* Restore rbx. */
	pop			%rbp						/* Pseudo-epilog. */

	ret

/* Stack markings for ELF/GNU to specify no executable stack */

.globl dcCall_x64_win64
	// .type dcCall_x64_win64, @function


dcCall_x64_win64:
	ret

#if defined (__linux__) && defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif

