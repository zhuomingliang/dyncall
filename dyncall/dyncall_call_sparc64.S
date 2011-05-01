/*
 Package: dyncall
 File: dyncall/dyncall_call_sparc_v9.S
 Description: Call kernel for sparc processor architecture Sparc 64-bit "Sparc V9" ABI.
 Status: passed all dyncall tests.
 License: 

 Copyright (c) 2011 Daniel Adler <dadler@uni-goettingen.de> 

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


/* --------------------------------------------------------------------------- 

call kernel for sparc v9
tested on sparc64/linux/debian [gcc54.fsffrance.org - thanx to the farm!] 

C Interface:
  void dcCall_sparc (DCpointer target, DCsize size, DCpointer data);
		     %i0             , %i1        , %i2
Input:
  i0   target
  i1   size
  i2   data

Changes from v8:
- fundamental data types
	- (un)signed int: 8,16,32,64
	- float: 32,64,128
- float: IEEE 754 compilant
	32 32-bit  float registers f0,f1,..,f31
	32 64-bit  float registers f0,f2,..,f62
	16 128-bit float registers f0,f4,..,f60
- 

Description:
We need to raise up a dynamic stack frame.
Therefore we need to compute the stack size. We do this first, 
in the context of the caller as a leaf function (using o3 as scratch for addition).
Then we raise the frame, ending up in o0-o3 is then i0-i3.

Stack Layout 32-Bit Model:
	XX: should be 8 byte aligned (min stack frame size is 96).
	            ...
	92: on stack argument 6
	88: input argument 5 spill
	            ...
	68: input argument 0 spill
	64: struct/union pointer return value
	 0: 16 registers save area

Stack Layout 64-Bit Model:
        XX: should be 16 byte aligned (min stack frame size is 172).
       168: on stack argument 6
       136: input argument 0 spill
       128: struct/union poiner return value
	 0: 16 registers save area



Register Usage:
%fp0..%fp31: floating-point arguments.
%sp or  %o6: stack pointer, always 8 (or 16?)-byte aligned.
%fp or  %i6: frame pointer.
%i0 and %o0: integer and pointer return values.
%i7 and %o7: return address. (caller puts return address to %o7, callee uses %i7)
%fp0 and %fp1: return value (float).
%i0..%i5:    input argument registers 
%o0..%o5:    output argument registers
%g0:         always zero, writes to it have no effect.

Register Mappings:
r0-7    -> globals
r8-15   -> outs
r16-r23 -> locals
r24-r31 -> ins

Integer Register Overview Table:
ID      Class   Name    Description
------------------------------------------------------------------------------
0	globals	g0	always zero, writes to it have no effect
1		g1
2		g2
3		g3
4		g4
5		g5
6		g6
7		g7
8	out	o0	[int/ptr] arg 0 and return
9		o1	          arg 1
10		o2	          arg 2
11		o3	          arg 3
12              o4                arg 4
13              o5                arg 5
14              o6	stack pointer
15		o7
16	local	l0	scratch
17		l1
18		l2
19		l3
20		l4
21		l5
22		l6
23		l7
24	in	i0	[int/pt] arg 0 and return
25		i1
26		i2
27		i3
28		i4
29		i5
30		i6	frame pointer
31		i7
*/

#if defined __arch64__
#define REGSIZE 8
#else
#define REGSIZE 4
#endif

#define ALIGN   16

.global dcCall_sparc64
dcCall_sparc64:

/* Basic Prolog: supports up to 6 arguments. */

	/*leaf functions: may use the first six output registers.*/
	/*o0-2:target,size,data*/
	/*o3-5:free to use */

	/* Compute a matiching stack size (approximate): o3 = align(92+o1,16) */

	add     %o1, (16+1+6)*REGSIZE+ALIGN-1, %o3
	and     %o3,   -ALIGN, %o3
	neg     %o3
	
	/* Prolog. */
	save	%sp, %o3, %sp	/* min stack size 64+4+6*4=92 plus 8 byte alignment => min frame size of 96 bytes. */
	
	/* Load output registers. */

	ld	[%i2           ],%o0
	ld	[%i2+REGSIZE*1 ],%o1
	ld	[%i2+REGSIZE*2 ],%o2
	ld	[%i2+REGSIZE*3 ],%o3
	ld	[%i2+REGSIZE*4 ],%o4
	ld	[%i2+REGSIZE*5 ],%o5

	/* Copy on stack? */
	sub	%i1,  REGSIZE*6, %i1   		/* i1 = decrement copy size by 6 regs (=6 regs x 4 bytes = 24 bytes total). */
	cmp     %i1, 0
        ble	.do_call
	 nop

	/* Copy loop: */
	add     %i2,  REGSIZE*6, %i2		/* i2 = address of 7th word of args buffer. */
	or	%g0, %g0, %l0			/* l0 = offset initialized to 0. */
	add     %sp,  REGSIZE*(16+1+6), %l2	/* l2 = argument area on stack space (7th word). (64+4+6*4 = byte offset 92). */
.next:
	ld      [%i2+%l0],%l1			/* Read from arg buffer(%i2) to %l1. */
	st      %l1, [%l2+%l0]			/* Write %l1 to stack space(%l2). */
	add     %l0, REGSIZE, %l0		/* Increment offset. */
	sub     %i1, REGSIZE, %i1		/* Decrement copy size. */
	cmp     %i1, 0
        bgt     .next
	 nop
.do_call:
	call	%i0				/* Call target. */
	 nop
        restore
	ret

