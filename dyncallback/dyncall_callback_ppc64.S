/*

 Package: dyncall
 Library: dyncallback
 File: dyncallback/dyncall_callback_ppc64.S
 Description: Callback Thunk - Implementation for PowerPC 64-bit
 License:

   Copyright (c) 2014-2015 Masanori Mitsugi <mitsugi@linux.vnet.ibm.com>

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

#include "../portasm/portasm-ppc.S"

/* Callback Thunk Entry code for PowerPC 64-bit. */

/* Stack Frame Layout: 

	296 DCValue ( 8 )
	112 DCArgs ( 64+104+8+4+4 = 184 )
	 48 Parameter area ( 8*8 = 64 )
	  0 Linkage area   ( 48 )


*/

/* Constants. */
INT_REGS    = 8
FLOAT_REGS  = 13
SIZEOF_GPR  = 8
SIZEOF_FPR  = 8

/* Linkage area. */
LINK_SP     = 0
LINK_CR     = 8
LINK_LR     = 16
LINK_OFFSET = 0
#if DC__ABI_PPC64_ELF_V == 2
LINK_TOC    = 24
LINK_SIZE   = 32
#else
LINK_TOC    = 40
LINK_SIZE   = 48
#endif
/* Parameter area. */
PAR_OFFSET = LINK_SIZE
#if DC__ABI_PPC64_ELF_V == 2
PAR_SIZE = 0
#else
PAR_SIZE = 64
#endif 
/* local struct DCArgs */
ARGS_OFFSET = (PAR_OFFSET+PAR_SIZE)
ARGS_SIZE   = (SIZEOF_GPR*INT_REGS)+(SIZEOF_FPR*FLOAT_REGS) + 8 + 4 * 4 
/* local struct DCValue */
RESULT_OFFSET = (ARGS_OFFSET+ARGS_SIZE)
RESULT_SIZE   = 8
/* additional locals (reg 30/31) */
LOCALS_OFFSET = (RESULT_OFFSET+RESULT_SIZE)
LOCALS_SIZE   = 2*SIZEOF_GPR
/* total */
FRAME_SIZE = ( (LOCALS_OFFSET+LOCALS_SIZE)+15 & (-16) )

/* struct DCCallback */
#if DC__ABI_PPC64_ELF_V == 2
DCB_THUNK      = 0
DCB_HANDLER    = 48
DCB_STACKCLEAN = 56
DCB_USERDATA   = 64
#else
DCB_THUNK      = 0
DCB_HANDLER    = 64
DCB_STACKCLEAN = 72
DCB_USERDATA   = 80
#endif

/* struct DCArgs */
DCA_IARRAY = 0
DCA_FARRAY = SIZEOF_GPR*INT_REGS
DCA_SP     = DCA_FARRAY + SIZEOF_FPR*FLOAT_REGS
DCA_ICOUNT = DCA_SP + 8
DCA_FCOUNT = DCA_ICOUNT + 4

/* struct DCValue */
DCV_INT   = 0
DCV_FLOAT = 0
DCV_SIZE  = 8

iregfile = ARGS_OFFSET+DCA_IARRAY
fregfile = ARGS_OFFSET+DCA_FARRAY
save_sp  = ARGS_OFFSET+DCA_SP
icount   = ARGS_OFFSET+DCA_ICOUNT
fcount   = ARGS_OFFSET+DCA_FCOUNT

/* 
  Thunk entry:
  R2 = DCCallback*
*/
.text
	.global dcCallbackThunkEntry
	.type dcCallbackThunkEntry, @function
#if DC__ABI_PPC64_ELF_V != 2
	.section .opd, "aw"
	.align 3
#endif

dcCallbackThunkEntry:
#if DC__ABI_PPC64_ELF_V != 2
	.quad .dcCallbackThunkEntry, .TOC.@tocbase, 0
	.previous
	.global .dcCallbackThunkEntry

.dcCallbackThunkEntry:
#endif
	mflr    r0
	std     r0,  16(r1)           /* store return address */
	std     r31, -8(r1)           /* store preserved registers (r31) */
	addi    r12, r1, PAR_OFFSET   /* temporary r12 = parameter area on callers stack frame */
	stdu    r1, -FRAME_SIZE(r1)   /* save callers stack pointer and make new stack frame. */

	std     r3, iregfile+0*8(r1)  /* spill 8 integer parameter registers */
	std     r4, iregfile+1*8(r1)
	std     r5, iregfile+2*8(r1)
	std     r6, iregfile+3*8(r1)
	std     r7, iregfile+4*8(r1)
	std     r8, iregfile+5*8(r1)
	std     r9, iregfile+6*8(r1)
	std     r10,iregfile+7*8(r1)
	stfd    f1, fregfile+ 0*8(r1) /* spill 13 float parameter registers */
	stfd    f2, fregfile+ 1*8(r1)
	stfd    f3, fregfile+ 2*8(r1)
	stfd    f4, fregfile+ 3*8(r1)
	stfd    f5, fregfile+ 4*8(r1)
	stfd    f6, fregfile+ 5*8(r1)
	stfd    f7, fregfile+ 6*8(r1)
	stfd    f8, fregfile+ 7*8(r1)
	stfd    f9, fregfile+ 8*8(r1)
	stfd    f10,fregfile+ 9*8(r1)
	stfd    f11,fregfile+10*8(r1)
	stfd    f12,fregfile+11*8(r1)
	stfd    f13,fregfile+12*8(r1)
	                        /* initialize struct DCCallback */
	std     r12,save_sp(r1) /* init stack pointer */
	xor     r0, r0, r0      /* init register counters */
	std     r0, icount(r1)
	std     r0, fcount(r1)
	std     r0, RESULT_OFFSET(r1)
	                               /* invoke callback handler */
	mr      r3, r11                /* arg 1: DCCallback* pcb  */
	addi    r4, r1, ARGS_OFFSET    /* arg 2: DCArgs* args     */
	addi    r5, r1, RESULT_OFFSET  /* arg 3: DCValue* result  */
	ld      r6, DCB_USERDATA(r11)  /* arg 4: void* userdata   */

	/* branch-and-link to DCCallback.handler */
	ld      r12,  DCB_HANDLER(r11)
	std     r2, LINK_TOC(r1)
#if DC__ABI_PPC64_ELF_V != 2
	ld      r2, 8(r12)
	ld      r0, 0(r12)
	mtctr   r0
#else
	mtctr   r12
#endif
	bctrl

	addi    r0, r1, RESULT_OFFSET /* r0 = DCValue* */
	                              /* switch on base result type */
	cmpi    cr0, r3, 'B
	beq     .i64
	cmpi    cr0, r3, 'i
	beq     .i64
	cmpi    cr0, r3, 'c
	beq     .i64
	cmpi    cr0, r3, 's
	beq     .i64
	cmpi    cr0, r3, 'l
	beq     .i64
	cmpi    cr0, r3, 'f
	beq     .f32
	cmpi    cr0, r3, 'd
	beq     .f64
	cmpi    cr0, r3, 'p
	beq     .i64
.void: /* ignore result (void call) */
	b       .end
.i64:  /* result is 64-bit long long result */
	ld       r3, RESULT_OFFSET + DCV_INT(r1)
	b       .end
.f32:  /* result is C float result */
	lfs       f1, RESULT_OFFSET + DCV_FLOAT(r1)
	b       .end
.f64:  /* result is C double result */
	lfd       f1, RESULT_OFFSET + DCV_FLOAT(r1)
	b       .end
.end:

	ld     r2,  LINK_TOC(r1)
	ld     r1,  0(r1)  /* restore stack pointer */
	ld     r31, -8(r1) /* restore preserved registers */
	ld     r0,  16(r1) /* load link register with return address */
	mtlr   r0
	blr                /* branch back to link register */
 
