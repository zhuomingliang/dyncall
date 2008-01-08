/*//////////////////////////////////////////////////////////////////////

	dyncall_arm9e_arm.s
	Copyright 2007 Tassilo Philipp.

	ARM9E family of processors (ARM mode).
	2007-10-11

//////////////////////////////////////////////////////////////////////*/

.text

.globl dcCall_arm9e_arm

/* Main dyncall call. */
dcCall_arm9e_arm:

	/* Prolog. This function never needs to spill inside its prolog, so just store the permanent registers. */
	mov		%r12, %r13						/* Stack ptr (r13)       -> temporary (r12). */
	sub		%r13, %r13, #16					/* Jump over spill area. */
	stmdb	%r13!, {%r4-%r12, %r14}			/* Permanent registers and stack pointer (now in r12), etc...   -> save area on stack (except counter). */
	sub		%r11, %r12, #16					/* Compute frame ptr (r11 - set past 4 first args at beginning of register save area). */

	/* Call. */
	mov		%r4, %r0						/* Move 'fptr' to r4 (1st argument is passed in r0). */
	mov		%r5, %r1						/* Move 'args' to r5 (2nd argument is passed in r1). */
	mov		%r6, %r2						/* Move 'size' to r6 (3rd argument is passed in r2). */
	ldm		%r5, {%r0-%r3}					/* Load first 4 arguments for new call into r0-r3. */

	subs	%r6, %r6, #16					/* Size of remaining arguments. */
	ble		call							/* Jump to call if no more arguments. */

	add		%r5, %r5, #16					/* Points to beginning of remaining arguments. */
	sub		%r13, %r13, %r6					/* Set stack pointer to top of stack. */
	and		%r9, %r6, #7					/* Align stack on 8 byte boundaries. */
	sub		%r13, %r13, %r9

	mov		%r8, %r13						/* Temp. destination pointer. */
	mov		%r9, #0							/* Init byte counter. */

pushArgs:
	ldrb	%r7, [%r5, %r9]					/* Load a byte into r7. */
	strb	%r7, [%r8, %r9]					/* Push byte onto stack. */
	add		%r9, %r9, #1					/* Increment byte counter. */
	cmp		%r9, %r6
	bne		pushArgs

call:
	blx		%r4								/* Call. */

	/* Epilog. */
	ldmdb	%r11, {%r4-%r11, %r13, %r15}	/* Restore permanent registers (ignore temporary (r12), restore stack ptr and program counter).@@@db not needed since we rewrite r13? */

