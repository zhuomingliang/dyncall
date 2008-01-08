/*///////////////////////////////////////////////////////////////////////

	dyncall_x64_system_v.s
	Copyright 2007 Tassilo Philipp.

	SystemV x64 calls for GAS
	November 28, 2007

/*///////////////////////////////////////////////////////////////////////

.intel_syntax
.text

.globl dcCall_x64
	.type dcCall_x64, @function

/* Main dyncall call. */
dcCall_x64:

	/* arguments: */
	/* rdi : size of arguments to be passed via stack */
	/* rsi : pointer to arguments to be passed via the stack */
	/* rdx : pointer to arguments of integral/pointer type to be passed via registers */
	/* rcx : pointer to arguments of floating point type to be passed via registers */
	/* r8  : target function pointer */

	push		%rbp						/* Pseudo-prolog - preserve rbp. */
	push		%rbx						/* Preserve rbx and store pointer to function in it. */

	mov			%rbp, %rsp					/* Store stack pointer in rbp. */

	mov			%rbx, %r8

	movd		%xmm0, qword ptr[%rcx   ]	/* Copy first 8 floats to xmm0-xmm7 (this makes rcx free to use). */
	movd		%xmm1, qword ptr[%rcx+ 8]
	movd		%xmm2, qword ptr[%rcx+16]
	movd		%xmm3, qword ptr[%rcx+24]
	movd		%xmm4, qword ptr[%rcx+32]
	movd		%xmm5, qword ptr[%rcx+40]
	movd		%xmm6, qword ptr[%rcx+48]
	movd		%xmm7, qword ptr[%rcx+56]

	sub			%rsp, %rdi					/* Setup stack frame by subtracting the size of the arguments. */

	mov			%rax, %rdi					/* Align stack. */
	add			%rax, 8
	and			%rax, 15
	sub			%rsp, %rax

	mov			%rcx, %rdi					/* Store number of bytes to copy to stack in rcx (for rep movsb). */
	mov			%rdi, %rsp					/* Store pointer to beginning of stack arguments in rdi (for rep movsb). */

	rep movsb	/* @@@ should be optimized (e.g. movq) */

	mov			%rdi, qword ptr[%rdx   ]	/* Copy first six int/pointer arguments to rdi, rsi, rdx, rcx, r8, r9. */
	mov			%rsi, qword ptr[%rdx+ 8]
	mov			%rcx, qword ptr[%rdx+24]
	mov			%r8,  qword ptr[%rdx+32]
	mov			%r9,  qword ptr[%rdx+40]
	mov			%rdx, qword ptr[%rdx+16]	/* Set rdx last to not overwrite it to soon. */

	mov			%al, 8						/* Put upper bound of number of used xmm registers in al. */
	call		%rbx						/* Invoke function. */

	mov			%rsp, %rbp					/* Restore stack pointer (such that we can pop the preserved values). */

	pop			%rbx						/* Restore rbx. */
	pop			%rbp						/* Pseudo-epilog. */

	ret

