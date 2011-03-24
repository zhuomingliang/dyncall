// Package: dyncall
// File: dyncall/dyncall_call_x86_gas.S
// Description: All x86 abi call kernel implementations in GNU Assembler using C Preprocessor
// License:
//
// Copyright (c) 2007-2010 Daniel Adler <dadler@uni-goettingen.de>,
//                         Tassilo Philipp <tphilipp@potion-studios.com>
//
// Permission to use, copy, modify, and distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//

.file "dyncall_call_x86_gas_att.S"

#include "dyncall_macros.h"


// ============================================================================
// DynCall Call Kernels for X86 Architecture
// ----------------------------------------------------------------------------
// C Interface:
//    dcCall_x86_XXX(void* target, void* args, size_t size);
//
// Parameter Stack layout:
//    size    :=  ebp + 16
//    args    :=  ebp + 12
//    target  :=  ebp +  8
//
// NOTES:
//  - epilog restore esp serves callee cleanup 


// Macro to prefix C symbol names with '_' (underscore) on Windows and Darwin.

#if defined(DC__OS_Win32) || defined(DC__OS_Cygwin) || defined(DC__OS_MinGW) || defined(DC__OS_Darwin)
#define CSYM(X) _##X
#else
#define CSYM(X) X
#endif

// ============================================================================

	.text

// --- default / cdecl --------------------------------------------------------
//  - caller clean-up

.globl CSYM(dcCall_x86_cdecl)
CSYM(dcCall_x86_cdecl):
	push %ebp		// prolog
 	movl %esp, %ebp
	push %esi		// save preserved
	push %edi
	movl 12(%ebp), %esi	// esi = copy source args
	movl 16(%ebp), %ecx	// ecx = size
	subl %ecx, %esp         // alloc stack size
	movl %esp, %edi         // edi = copy target stack
	shrl $2, %ecx		// ecx = count DWORDs
	rep  movsd		// copy DWORDs
	call *8(%ebp)		// call target
	addl 16(%ebp), %esp     // cleanup stack
	pop  %edi               // restore preserved 
	pop  %esi
	movl %ebp, %esp       	// epilog
	pop  %ebp
	ret

// ---- C++ this calls (microsoft) ------------------------------------------ 
// Details:
//   - this pointer is in ECX

.globl CSYM(dcCall_x86_win32_msthis)
CSYM(dcCall_x86_win32_msthis):
	push %ebp               // prolog 
	movl %esp, %ebp
	push %esi               // save preserved
	push %edi
	movl 12(%ebp), %esi	// esi = pointer on args 
	movl 16(%ebp), %ecx	// ecx = size 
	movl   (%esi), %eax	// eax = this pointer 
	addl $4, %esi           // increment args pointer by thisptr 
	subl $4, %ecx           // decrement size by sizeof(thisptr) 
	subl %ecx, %esp         // allocate argument-block on stack 
	movl %esp, %edi         // edi = stack args
	rep movsb               // copy arguments
	movl %eax, %ecx         // ecx = this pointer
	call *8(%ebp)           // call function
	pop  %edi               // restore preserved
	pop  %esi
	movl %ebp, %esp         // epilog
	pop  %ebp
	ret

// ---- win32 stdcall ---------------------------------------------------------
// - callee cleans up stack

.globl CSYM(dcCall_x86_win32_std)
CSYM(dcCall_x86_win32_std):
	push %ebp               // prolog
	movl %esp, %ebp
	push %esi               // save esi, edi
	push %edi
	movl 12(%ebp), %esi	// esi = args
	movl 16(%ebp), %ecx	// ecx = size
	subl %ecx, %esp		// allocate size bytes on stack
	movl %esp, %edi		// edi = copy destination stack
	rep movsb		// copy BYTEs
	call *8(%ebp)		// call target
	pop  %edi		// restore edi, esi */
	pop  %esi
	mov  %ebp, %esp		// epilog
	pop  %ebp
	ret

// ---- win32 fastcall (GNU/Microsoft) ----------------------------------------
// - callee cleans up stack
// - first two integer (up to 32bits) are passed in ECX and EDX

.globl CSYM(dcCall_x86_win32_fast)
CSYM(dcCall_x86_win32_fast):
	push %ebp               // prolog
	movl %esp, %ebp
	push %esi               // save preserved
	push %edi
	movl 12(%ebp), %esi	// esi = copy source args
	movl 16(%ebp), %ecx	// ecx = size
	movl  0(%esi), %eax	// eax = first argument
	movl  4(%esi), %edx	// edx = second argument
	addl $8, %esi           // skip registers
	subl $8, %ecx           // 
	movl %ecx, 16(%ebp)	// save stack alloc size
	subl %ecx, %esp         // allocate stack 
	movl %esp, %edi         // edi = stack args 
	rep movsb               // copy BYTEs
	movl %eax, %ecx         // ecx = first argument 
	call *8(%ebp)           // call target
	pop  %edi               // restore preserved
	pop  %esi
	movl %ebp, %esp         // epilog 
	pop  %ebp
	ret

// --- syscall int80 linux ---------------------------------------------------
//  - all arguments are passed via registers

.globl CSYM(dcCall_x86_sys_int80h_linux)
CSYM(dcCall_x86_sys_int80h_linux):
	push %ebp        	// prolog
 	movl %esp, %ebp
	push %ebx		// save preserved
	push %esi               
	push %edi
	movl 12(%ebp), %eax	// eax = argument buffer 
	movl 0(%eax),  %ebx	// move first five arguments
	movl 4(%eax),  %ecx	
	movl 8(%eax),  %edx
	movl 12(%eax), %esi
	movl 16(%eax), %edi
	movl 8(%ebp),  %eax	// eax = syscall id
	int  $0x80
	pop  %edi               // restore preserved
	pop  %esi
	pop  %ebx
	movl %ebp, %esp        	// epilog
	pop  %ebp
	ret

// --- syscall int80 bsd -----------------------------------------------------
// - all arguments are passed via stack
	
.globl CSYM(dcCall_x86_sys_int80h_bsd)
CSYM(dcCall_x86_sys_int80h_bsd):
	push %ebp               // prolog
 	movl %esp, %ebp
	push %esi               // save preserved
	push %edi
	movl 12(%ebp), %esi    	// esi = pointer on args
	movl 16(%ebp), %ecx    	// ecx = size
	subl %ecx, %esp        	// allocate stack space
	movl %esp, %edi         // edi = stack args
	shrl $2, %ecx           // ecx = number of DWORDs
	rep movsd               // copy DWORDs
	movl  8(%ebp), %eax	// load system call id
	call _do_int
	pop  %edi               // restore preserved
	pop  %esi
	movl %ebp, %esp         // epilog
	pop  %ebp
	ret
_do_int:
	int $0x80
	ret


