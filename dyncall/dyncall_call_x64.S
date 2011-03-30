/* 
This is a evaluation file for a version that works when --traditional-cpp is set on cc,
which was the case in NetBSD 5.1 

The problem in tradional-cpp mode is:

we define reg -> %reg ... which is recursive in traditional-cpp.

Currently this is fixed via overload the make rule '%.S -> %.o' 
which uses 'cc -c' without --traditional-cpp.

This file should be tested for gen_masm and eventually needs macros for masm to map capitalized regs to lower-cases.
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
#  if defined (__APPLE__)
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
#endif

BEGIN_ASM

// ---------------------------------------------------------------------------
// Call Kernel for x64 System V

GLOBAL(dcCall_x64_sysv)
BEGIN_PROC(dcCall_x64_sysv)

	/* RDI : size of arguments to be passed via stack */
	/* RSI : pointer to arguments to be passed via the stack */ 
	/* RDX : pointer to arguments of integrAL/pointer type to be passed via registers */
	/* RCX : pointer to arguments of floating point type to be passed via registers */
	/* R8  : target function pointer */

	push	RBP			/* Pseudo-prolog - preserve RBP. */
	push	RBX			/* Preserve RBX and store pointer to function in it. */

	mov	RBP, RSP		/* Store stack pointer in RBP.   */

	mov	RBX, R8

	movsd	XMM0, qword ptr[RCX   ]	/* Copy first 8 floats to XMM0-XMM7 (this makes RCX free to use). */
	movsd	XMM1, qword ptr[RCX+ 8]
	movsd	XMM2, qword ptr[RCX+16]
	movsd	XMM3, qword ptr[RCX+24]
	movsd	XMM4, qword ptr[RCX+32]
	movsd	XMM5, qword ptr[RCX+40]
	movsd	XMM6, qword ptr[RCX+48]
	movsd	XMM7, qword ptr[RCX+56]

	sub	RSP, RDI		/* Setup stack frame by subtracting the size of the arguments. */

	mov	RAX, RDI		/* Align stack. */
	add	RAX, 8
	and	RAX, 15
	sub	RSP, RAX

	mov	RCX, RDI		/* Store number of bytes to copy to stack in RCX (for rep movsb). */
	mov	RDI, RSP		/* Store pointer to beginning of stack arguments in RDI (for rep movsb). */

	rep movsb			/* @@@ should be optimized (e.g. movq) */

	mov	RDI, qword ptr[RDX   ]	/* Copy first six int/pointer arguments to RDI, RSI, RDX, RCX, R8, R9. */
	mov	RSI, qword ptr[RDX+ 8]
	mov	RCX, qword ptr[RDX+24]
	mov	R8,  qword ptr[RDX+32]
	mov	R9,  qword ptr[RDX+40]
	mov	RDX, qword ptr[RDX+16]	/* Set RDX last to not overwrite it to soon. */

	mov	AL, 8						/* Put upper bound of number of used xmm registers in AL. */
	call	RBX						/* Invoke function. */

	mov	RSP, RBP					/* Restore stack pointer (such that we can pop the preserved vALues). */

	pop	RBX						/* Restore RBX. */
	pop	RBP						/* Pseudo-epilog. */

	ret
END_PROC(dcCALl_x64_sysv)

// ---------------------------------------------------------------------------
// CALl Kernel for x64 Win64

GLOBAL(dcCall_x64_win64)
BEGIN_PROC(dcCall_x64_win64)

	/* RCX : size of arguments to be passed via stack */
	/* RDX : pointer to arguments to be passed via the stack */ 
	/* R8  : pointer to arguments of integrAL/pointer type to be passed via registers */
	/* R9  : target function pointer */

	push	RBP			/* Pseudo-prolog - preserve RBP. */
	push	RSI			/* Preserve RSI and RDI. */
	push	RDI
	
	// and  RSP, -16		// Align frame to 16 bytes.
	mov	RBP, RSP		/* Store stack pointer in RBP. */

	add	RCX, 15			// Align stack size to 16 bytes.
	and	RCX, -16
	sub	RSP, RCX		// Setup stack frame by subtracting the size of the arguments.

	mov	RSI, RDX		/* Let RSI point to the arguments. */
	mov	RDI, RSP		/* Store pointer to beginning of stack arguments in RDI (for rep movsb). */
	mov	RAX, R9			/* Put function address in RAX. */

	rep movsb			/* @@@ should be optimized (e.g. movq) */

	mov	RCX,  qword ptr[R8   ]	/* Copy first four arguments to RCX, RDX, R8, R9 and XMM0-XMM3. */
	mov	RDX,  qword ptr[R8+ 8]
	mov	R9,   qword ptr[R8+24]	/* Set R9 first to not overwrite R8 too soon. */
	mov	R8,   qword ptr[R8+16]
	movd	XMM0, RCX
	movd	XMM1, RDX
	movd	XMM2, R8
	movd	XMM3, R9

	push	R9			/* Push first four arguments onto the stack preserve area. */
	push	R8
	push	RDX
	push	RCX

	call	RAX			/* Invoke function. */

	mov	RSP, RBP		/* Restore stack pointer (such that we can pop the preserved vALues). */

	pop	RDI			/* Restore RSI and RDI. */
	pop	RSI
	pop	RBP			/* Pseudo-epilog. */

	ret

END_PROC(dcCall_x64_win64)

END_ASM

