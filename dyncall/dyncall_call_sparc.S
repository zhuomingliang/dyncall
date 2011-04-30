/* 
void dcCall_sparc (DCpointer target, DCsize size, DCpointer data);
                   %i0             , %i1           , %i2

%sp or %o6: stack pointer, always 16-byte aligned.
%fp or %i6: frame pointer.
%i0 and %o0: integer and pointer return values.
%i7 and %o7: return address. (caller puts return address to %o7, callee uses %i7)
%f0 and %f1: return value (float).
%i0..%i5: 
%o0..%o5:

*/
.global dcCall_sparc
dcCall_sparc:
/* decrement stack using size */
/* sp+92 seventh argument */
/* sp+68 argument 0 */
/* copy data to sp+68 , 
/*
*/
	save	%sp, -160, %sp
	st	%i0, [%sp+68]
	st	%i1, [%sp+72]
	st	%i2, [%sp+76]
	ld	[%i2   ],%o0
	ld	[%i2+4 ],%o1
	ld	[%i2+8 ],%o2
	ld	[%i2+12],%o3
	ld	[%i2+16],%o4
	ld	[%i2+20],%o5
	add     %i2,  24, %i2
	or	%g0, %g0, %l0
	add     %sp,  92, %l2
.next:
	ld      [%i2+%l0],%l1
	st      %l1, [%l2+%l0]
	add     %l0, 4, %l0
	subcc   %i1, 4, %i1
	bgt     .next
	nop

	call	%i0
	nop
	ret
	restore
/*
	nop
	mov	[%sp+A   ],%o0
	mov	[%sp+A+4 ],%o1
	mov	[%sp+A+8 ],%o2
	mov	[%sp+A+12],%o3
	mov	[%sp+A+16],%o4
	mov	[%sp+A+20],%o5
	ld      [%sp+F],%f9
	ld      [%sp+F],%f10
	ld      [%sp+F],%f11
	ld      [%sp+F],%f12
	ld      [%sp+F],%f13
	ld      [%sp+F],%f14
	call	%i0, 0
	nop
	restore
	ret
*/
