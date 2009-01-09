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

/*///////////////////////////////////////////////////////////////////////

      dyncall_ppc32.s
 
      powerpc 32 bit C call, AS source.
      November  28, 2007

//////////////////////////////////////////////////////////////////////*/


/* -------------------------------------------------------------------------
      PPC 32bit calling convention for Mac OS X / Darwin
   -------------------------------------------------------------------------
   
   - Stack frames are always aligned on 16 byte
  
   - The GPR3 .. GPR10 are loaded
   - The FPR1 .. FPR13 are loaded
   
   No support for Vector Parameters so far. 

   Parameter Area (min. 32 Bytes)
   Linkage Area (24 Bytes)
  
*/

/*
   dcCall_ppc32(DCpointer target, struct DCRegData* pRegData, DCsize stacksize, DCptr stackdata);
   struct DCRegData { int i[8]; double d[13]; };
 */

.globl _dcCall_ppc32
_dcCall_ppc32:

/*
	arguments 
     
	r3 = func ptr
	r4 = register data ptr (8xGPR 32 bytes, 13xFPR 104 bytes)
	r5 = stack data size 
	r6 = stack data ptr
 */

	mflr r0			/* r0 = return address */
	stw  r0,8(r1)		/* store return address in caller link-area */

	/* compute aligned stack-size */

	/* add link area and align to 16 byte border */

	addi r0,r5,24+15	/* r0 = stacksize + link area */
                                
	rlwinm r0,r0,0,0,27	/* r0 = r0 and -15 */
				/* r0 = r0 and -15 */
	neg r2,r0		/* r2 = -stacksize */

	stwux r1,r1,r2		/* r1 = r1 - stacksize */

	/* copy stack data */

	subi r6,r6,4		/* r6 = 4 bytes before source stack ptr */
	addi r7,r1,20		/* r7 = 4 bytes before target stack parameter-block */

	srwi r5,r5,2		/* r5 = size in words */

	cmpi cr0,r5,0		/* if stacksize != 0 .. */
	beq  cr0,.done

	mtctr r5		/* copy loop */

.next:	lwzu r0, 4(r6)		
	stwu r0, 4(r7)
	bdnz .next

.done:

	mtctr r3		/* setup target function */
	mr r2, r4		/* r2 = reg data */

        /* load 8 integer registers */

	lwz  r3 , 0(r2)
	lwz  r4 , 4(r2)
	lwz  r5 , 8(r2)
	lwz  r6 ,12(r2)
	lwz  r7 ,16(r2)
	lwz  r8 ,20(r2)
	lwz  r9 ,24(r2)
	lwz  r10,28(r2)

	/* load 13 float registers */

	lfd  f1 ,32(r2)
	lfd  f2 ,40(r2)
	lfd  f3 ,48(r2)
	lfd  f4 ,56(r2)
	lfd  f5 ,64(r2)
	lfd  f6 ,72(r2)
	lfd  f7 ,80(r2)
	lfd  f8 ,88(r2)
	lfd  f9 ,96(r2)
	lfd  f10,104(r2)
	lfd  f11,112(r2)
	lfd  f12,120(r2)
	lfd  f13,128(r2)

	/* branch */

	bctrl

	/* epilog */

	lwz  r1, 0(r1)		/* restore stack */
	lwz  r0, 8(r1)		/* r0 = return address */
	mtlr r0			/* setup link register */
	blr			/* store */

/* utility (test) function to compute aligned stack size */

.globl _dcComputeStackSize
_dcComputeStackSize:
	; r3 = stacksize
	addi r3, r3, 24+15	/* r0 = stacksize + link area */
	rlwinm r3,r3,0,0,27	/* r3 = r3 and 0xFFFFFFF0 (align to 16 byte border) */
	neg  r3,r3		/* r2 = -stacksize */
	blr

