/*
 Package: dyncall
 Library: dyncallback
 File: dyncallback/dyncall_callback_ppc32_apple.s
 Description: Callback Thunk - Implementation for PowerPC 32-bit on Darwin/Apple's as
 License:

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

*/
	.machine ppc
	.text
	.align 2

/* Darwin. */

INT_REGS	= 8
FLOAT_REGS	= 13

/* Stack Frame Layout: 
	
       206 DCValue ( )
	56 DCArgs (32+104+4+8 = 150)
	24 Parameter area ( 4*8 = 32 )
	0  Linkage area   ( 24 )


*/
	
LINK_SP 	= 0
LINK_CR    	= 4
LINK_LR    	= 8

/* Linkage area */

LINK_OFFSET	= 0
LINK_SIZE	= 24

PAR_OFFSET	= LINK_SIZE
PAR_SIZE	= 32

/* local: DCArgs */

ARGS_OFFSET	= (PAR_OFFSET+PAR_SIZE)

SIZEOF_INT      = 4
SIZEOF_DOUBLE	= 8

ARGS_SIZE 	= (SIZEOF_INT*INT_REGS)+(SIZEOF_DOUBLE*FLOAT_REGS)

	/* 136 */

RESULT_OFFSET	= (ARGS_OFFSET+ARGS_SIZE)
RESULT_SIZE	= 16

LOCALS_OFFSET   = (RESULT_OFFSET+RESULT_SIZE)
LOCALS_SIZE     = 2*4

FRAME_SIZE	= ( (LOCALS_OFFSET+LOCALS_SIZE)+15 & (-16) )

/* DCCallback Structure */

DCB_THUNK 	= 0
DCB_HANDLER	= 40
DCB_STACKCLEAN	= 44
DCB_USERDATA	= 48

/* DCArgs */

DCA_IARRAY 	= 0
DCA_FARRAY	= SIZEOF_INT*INT_REGS
DCA_SP          = DCA_FARRAY + SIZEOF_DOUBLE*FLOAT_REGS
DCA_ICOUNT	= DCA_SP + 4
DCA_FCOUNT	= DCA_ICOUNT + 4

/* DCValue */

DCV_INT		= 0
DCV_FLOAT	= 0 
DCV_DOUBLE	= 0
DCV_LONG_HI32	= 0
DCV_LONG_LO32	= 4
DCV_SIZE	= 8


	.globl _dcCallbackThunkEntry

	/* 
	  Thunk entry:
	  Register R2 points to DCCallback structure
	*/
_dcCallbackThunkEntry:
	
	/* store link-register to link-area on stack. */
	mflr  r0
	stw   r0,   8(r1)
	
	/* store preserved registers (for 2 local 32-bit integer variables). */

	stmw  r30, -8(r1)

	/* let r30 point to parameters on stack */

	addi  r30, r1, PAR_OFFSET

	/* store DCCallback* to r30 */

	/* mr    r30,    r2 */

	/* store stack pointer and make new stack frame. */

	stwu  r1, -FRAME_SIZE(r1)

	/* spill 8 integer parameter passing registers. */

	stw  r3 , ARGS_OFFSET+DCA_IARRAY+0*4(r1)
	stw  r4 , ARGS_OFFSET+DCA_IARRAY+1*4(r1)
	stw  r5 , ARGS_OFFSET+DCA_IARRAY+2*4(r1)
	stw  r6 , ARGS_OFFSET+DCA_IARRAY+3*4(r1)
	stw  r7 , ARGS_OFFSET+DCA_IARRAY+4*4(r1)
	stw  r8 , ARGS_OFFSET+DCA_IARRAY+5*4(r1)
	stw  r9 , ARGS_OFFSET+DCA_IARRAY+6*4(r1)
	stw  r10, ARGS_OFFSET+DCA_IARRAY+7*4(r1)

	/* spill 13 floating pointer parameter passing registers. */

	stfd f1 , ARGS_OFFSET+DCA_FARRAY+ 0*8(r1)
	stfd f2 , ARGS_OFFSET+DCA_FARRAY+ 1*8(r1)
	stfd f3 , ARGS_OFFSET+DCA_FARRAY+ 2*8(r1)
	stfd f4 , ARGS_OFFSET+DCA_FARRAY+ 3*8(r1)
	stfd f5 , ARGS_OFFSET+DCA_FARRAY+ 4*8(r1)
	stfd f6 , ARGS_OFFSET+DCA_FARRAY+ 5*8(r1)
	stfd f7 , ARGS_OFFSET+DCA_FARRAY+ 6*8(r1)
	stfd f8 , ARGS_OFFSET+DCA_FARRAY+ 7*8(r1)
	stfd f9 , ARGS_OFFSET+DCA_FARRAY+ 8*8(r1)
	stfd f10, ARGS_OFFSET+DCA_FARRAY+ 9*8(r1)
	stfd f11, ARGS_OFFSET+DCA_FARRAY+10*8(r1)
	stfd f12, ARGS_OFFSET+DCA_FARRAY+11*8(r1)
	stfd f13, ARGS_OFFSET+DCA_FARRAY+12*8(r1)

	/* initialize DCCallback */

	/* set stack pointer on previous frame's parameter area to DCArgs's stack pointer field */

	stw  r30 , ARGS_OFFSET+DCA_SP(r1)

	/* init counters with 0 */

	xor  r0 , r0, r0
	stw  r0 , ARGS_OFFSET+DCA_ICOUNT(r1)
	stw  r0 , ARGS_OFFSET+DCA_FCOUNT(r1)

	/* 
	   invoke callback handler, C signature:

           char handler(DCCallback* pcb, DCArgs* args, DCValue* result, void* userdata);

	 */
	
	mr   r3, r2			/* arg 1: DCCallback* pcb 	*/
	addi r4, r1, ARGS_OFFSET	/* arg 2: DCArgs* args 		*/
	addi r5, r1, RESULT_OFFSET	/* arg 3: DCValue* result	*/
	lwz  r6, DCB_USERDATA(r2)       /* arg 4: void* userdata 	*/

	/* branch to DCCallback.handler */

	lwz   r12, DCB_HANDLER(r2)
	mtctr r12
	bctrl
	
	addi r0, r1, RESULT_OFFSET	/* r0 = DCValue* */

	/* switch on base result type */	

	cmpi  cr0, r3, 'i
	beq  .i32 
	cmpi  cr0, r3, 'f
	beq  .f32
	cmpi  cr0, r3, 'l
	beq  .i64

	/* ignore result (void call) */
.void:
	b .end

	/* result is integer <= 32-bit result */
.i32:
	lwz r3, RESULT_OFFSET + DCV_INT(r1)	
	b .end

	/* result is C float result */
.f32:
	lfd f1, RESULT_OFFSET + DCV_FLOAT(r1)
	b .end

	/* result is C double result */
.i64:
	lwz r3, RESULT_OFFSET + DCV_LONG_HI32(r1)
	lwz r4, RESULT_OFFSET + DCV_LONG_LO32(r1)
	b .end

.end:

	/* restore stack pointer */
	lwz r1, 0(r1)
	/* restore preserved registers */
	lmw r30, -8(r1)
	/* load link register with return-address */
	lwz r0, 8(r1)
	mtlr r0
	/* branch to link register */
	blr

