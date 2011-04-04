/*
 Package: dyncall
 File: dyncall/dyncall_call_x86.S
 Description: All - expect Plan9 - x86 abi call kernel implementation
 License:

 Copyright (c) 2007-2011 Daniel Adler <dadler@uni-goettingen.de>,
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

#include "../portasm/portasm-x86.S"

/* ============================================================================
   DynCall Call Kernels for X86 Architecture
   ----------------------------------------------------------------------------
   C Interface:
      dcCall_x86_XXX(void* target, void* args, size_t size);
 
   Where XXX is one of calling-conventions,
	cdecl, win32_msthis, win32_std, win32_fastcall.

   The system call kernels:
      ddCall_x86_sys_XXX(int_ptr target, void* args, size_t size);

   Parameter Stack layout:
      size    :=  EBP + 16
      args    :=  EBP + 12
      target  :=  EBP +  8
  
   NOTES:
    - epilog restore ESP serves callee cleanup 
    - 16 byte alignment (to be compatible with darwin).
*/


/*--- default / cdecl --------------------------------------------------------

  Details:
  - caller clean-up

*/

BEGIN_ASM
GLOBAL(dcCall_x86_cdecl)
BEGIN_PROC(dcCall_x86_cdecl)
	push EBP			/* prolog. */
 	mov  EBP, ESP
	push ESI			/* save preserved. */
	push EDI
	mov  ESI, dword ptr[EBP+12] 	/* ESI = copy source args. */
	mov  ECX, dword ptr[EBP+16] 	/* ECX = size. */
	
	add  ECX, 15			/* align size to 16 byte. */
	and  ECX, -16
	mov  dword ptr [EBP+16], ECX
	
	sub  ESP, ECX         	    	/* alloc stack size. */
	mov  EDI, ESP		    	/* EDI = copy target stack. */
	shr  ECX, 2			/* ECX = count DWORDs. */
	rep  movsd			/* copy DWORDs. */
	call dword ptr[EBP+8] 		/* call target. */
	add  ESP, dword ptr[EBP+16] 	/* cleanup stack. */
	pop  EDI               	    	/* restore preserved. */ 
	pop  ESI
	mov  ESP, EBP			/* epilog. */
	pop  EBP
	ret
END_PROC(dcCall_x86_cdecl)


/* ---- C++ this calls (microsoft) ------------------------------------------ 

  Details:
  - this pointer is in ECX

*/

GLOBAL(dcCall_x86_win32_msthis)
BEGIN_PROC(dcCall_x86_win32_msthis)
	push EBP               		/* prolog. */
	mov  EBP, ESP
	push ESI               		/* save preserved. */
	push EDI
	mov  ESI, dword ptr [EBP+12]	/* ESI = pointer on args. */
	mov  ECX, dword ptr [EBP+16]	/* ECX = size. */
	mov  EAX, dword ptr [ESI+0]	/* EAX = this pointer. */ 
	add  ESI, 4           		/* increment args pointer by thisptr. */
	sub  ECX, 4         		/* decrement size by sizeof(thisptr). */
	sub  ESP, ECX         		/* allocate argument-block on stack. */
	mov  EDI, ESP       		/* EDI = stack args. */
	rep  movsb              	/* copy arguments. */
	mov  ECX, EAX       		/* ECX = this pointer. */
	call dword ptr[EBP+8]		/* call function. */
	pop  EDI			/* restore preserved. */
	pop  ESI
	mov  ESP, EBP        		/* epilog. */
	pop  EBP
	ret
END_PROC(dcCall_x86_win32_msthis)

/*---- win32 stdcall ---------------------------------------------------------
  
  Details:
  - callee cleans up stack

*/

GLOBAL(dcCall_x86_win32_std)
BEGIN_PROC(dcCall_x86_win32_std)
	push EBP			/* prolog. */
	mov  EBP, ESP
	push ESI			/* save ESI, EDI. */
	push EDI
	mov  ESI, dword ptr[EBP+12]	/* ESI = args. */
	mov  ECX, dword ptr[EBP+16]	/* ECX = size. */
	sub  ESP, ECX			/* allocate size bytes on stack. */
	mov  EDI, ESP			/* EDI = copy destination stack. */
	rep  movsb			/* copy BYTEs. */
	call dword ptr[EBP+8]		/* call target. */
	pop  EDI			/* restore EDI, ESI. */
	pop  ESI
	mov  ESP, EBP			/* epilog. */
	pop  EBP
	ret
END_PROC(dcCall_x86_win32_std)

/*---- win32 fastcall (GNU/Microsoft) ----------------------------------------

  Details:
  - callee cleans up stack
  - first two integer (up to 32bits) are passed in ECX and EDX

*/

GLOBAL(dcCall_x86_win32_fast)
BEGIN_PROC(dcCall_x86_win32_fast)
	push EBP			/* prolog. */
	mov  EBP, ESP
	push ESI			/* save preserved. */
	push EDI
	mov  ESI, dword ptr[EBP+12]	/* ESI = copy source args. */
	mov  ECX, dword ptr[EBP+16]	/* ECX = size. */
	mov  EAX, dword ptr[ESI+0]	/* EAX = first argument. */
	mov  EDX, dword ptr[ESI+4]	/* EDX = second argument. */
	add  ESI, 8			/* skip registers. */
	sub  ECX, 8
	mov  dword ptr [EBP+16], ECX	/* save stack alloc size. */
	sub  ESP, ECX			/* allocate stack. */
	mov  EDI, ESP			/* EDI = stack args. */ 
	rep  movsb			/* copy BYTEs. */
	mov  ECX, EAX			/* ECX = first argument. */ 
	call dword ptr[EBP+8]		/* call target. */
	pop  EDI			/* restore preserved. */
	pop  ESI
	mov  ESP, EBP			/* epilog. */
	pop  EBP
	ret
END_PROC(dcCall_x86_win32_fast)

/*--- syscall int80 linux ---------------------------------------------------
  
  Details:
  - all arguments are passed via registers

*/

GLOBAL(dcCall_x86_sys_int80h_linux)
BEGIN_PROC(dcCall_x86_sys_int80h_linux)
	push EBP        		/* prolog. */
 	mov  EBP, ESP
	push EBX			/* save preserved. */
	push ESI               
	push EDI
	mov  EAX, dword ptr[EBP+12]	/* EAX = argument buffer. */
	mov  EBX, dword ptr[EAX+0]	/* move first five arguments. */
	mov  ECX, dword ptr[EAX+4] 	
	mov  EDX, dword ptr[EAX+8] 
	mov  ESI, dword ptr[EAX+12]
	mov  EDI, dword ptr[EAX+16]
	mov  EAX, dword ptr[EBP+8] 	/* EAX = syscall id. */
	int  HEX(80)
	pop  EDI			/* restore preserved. */
	pop  ESI
	pop  EBX
	mov  ESP, EBP			/* epilog. */
	pop  EBP
	ret
END_PROC(dcCall_x86_sys_int80h_linux)

/*--- syscall int80 bsd -----------------------------------------------------

  Details:
  - all arguments are passed via stack

*/
	
GLOBAL(dcCall_x86_sys_int80h_bsd)
BEGIN_PROC(dcCall_x86_sys_int80h_bsd)
	push EBP			/* prolog. */
 	mov  EBP, ESP
	push ESI			/* save preserved. */
	push EDI
	mov  ESI, dword ptr[EBP+12]    	/* ESI = pointer on args. */
	mov  ECX, dword ptr[EBP+16]    	/* ECX = size. */
	sub  ESP, ECX       		/* allocate stack space. */
	mov  EDI, ESP           	/* EDI = stack args. */
	shr  ECX, 2             	/* ECX = number of DWORDs. */
	rep  movsd               	/* copy DWORDs. */
	mov  EAX, dword ptr[EBP+8]	/* load system call id. */
	call _do_int
	pop  EDI               		/* restore preserved. */
	pop  ESI
	mov  ESP, EBP          		/* epilog. */
	pop  EBP
	ret
_do_int:
	int  HEX(80)
	ret
END_PROC(dcCall_x86_sys_int80h_bsd)
END_ASM

