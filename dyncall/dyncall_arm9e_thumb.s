/*/////////////////////////////////////////////////////////////////////////////

 Copyright (c) 2007,2008 Daniel Adler <dadler@uni-goettingen.de>, 
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

/*//////////////////////////////////////////////////////////////////////

	dyncall_arm9e_thumb.s

	ARM9E family of processors (THUMB mode).
	2008-08-12

//////////////////////////////////////////////////////////////////////*/

.text
.code 16	/* THUMB mode */

.globl dcCall_arm9e_thumb
.thumb_func

/* Main dyncall call. */
dcCall_arm9e_thumb:

	/* Prolog. This function never needs to spill inside its prolog, so just store the permanent registers. */
	push	{%r4-%r7, %r14}					/* Frame ptr, permanent registers, link register -> save area on stack. */
	mov		%r7, %r13						/* Set frame ptr. */

	/* Call. */
	mov		%r4, %r0						/* Move 'fptr' to r4 (1st argument is passed in r0). */
	mov		%r0, #1							/* Set LSB to 1 (THUMB call). */
	orr		%r4, %r0
	mov		%r5, %r1						/* Move 'args' to r5 (2nd argument is passed in r1). */
	mov		%r6, %r2						/* Move 'size' to r6 (3rd argument is passed in r2). */
	ldmia	%r5!, {%r0-%r3}					/* Load first 4 arguments for new call into r0-r3. */

	sub		%r6, %r6, #16					/* Size of remaining arguments. */
	cmp		%r6, #0
	ble		call							/* Jump to call if no more arguments. */

/*@@@	sub		%r13, %r13, %r6*/					/* Set stack pointer to top of stack. */
/*@@@	and		%r9, %r6, #7*/					/* Align stack on 8 byte boundaries. */
/*@@@	sub		%r13, %r13, %r9*/

	mov		%r9, %r13						/* Temp. destination pointer. */
/*@@@	mov		%r10, #0*/						/* Init byte counter. */

pushArgs:
/*@@@	ldrb	%r8, [%r5, %r10]*/				/* Load a byte into r8. */
/*@@@	strb	%r8, [%r9, %r10]*/				/* Push byte onto stack. */
/*@@@	add		%r10, %r10, #1*/					/* Increment byte counter. */
	cmp		%r10, %r6
	bne		pushArgs

call:
	blx		%r4								/* Call. */

	/* Epilog. */
	mov		%r13, %r7						/* Reset stack ptr. */
	pop		{%r4-%r7, %r15}					/* Restore permanent registers and program counter. */



/* Internally used to avoid compiler overwriting r0 and r1 in call stub */
.globl dcCall_arm9e_thumb_word
.thumb_func

dcCall_arm9e_thumb_word:
	b	dcCall_arm9e_thumb


.globl dcCall_arm9e_thumb_dword
.thumb_func

dcCall_arm9e_thumb_dword:
	b	dcCall_arm9e_thumb

