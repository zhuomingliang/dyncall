;//////////////////////////////////////////////////////////////////////////////
;
; Copyright (c) 2007-2009 Daniel Adler <dadler@uni-goettingen.de>, 
;                         Tassilo Philipp <tphilipp@potion-studios.com>
;
; Permission to use, copy, modify, and distribute this software for any
; purpose with or without fee is hereby granted, provided that the above
; copyright notice and this permission notice appear in all copies.
;
; THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
; WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
; MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
; ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
; WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
; ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
; OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
;
;//////////////////////////////////////////////////////////////////////////////

;///////////////////////////////////////////////////////////////////////
;
; Package: dyncall
; Library: dyncallback
; File: dyncallback/dyncall_callback_x64_msvc.asm
; Description: Callback Thunk - MASM implementation for x64
;
;///////////////////////////////////////////////////////////////////////

.CODE

; sizes
DCThunk_size    =   24
DCArgs_size     =  128
DCValue_size    =    8

; frame local variable offsets relative to rbp
FRAME_arg0      =   16
FRAME_return    =    8
FRAME_parent    =    0
FRAME_DCArgs    = -128
FRAME_DCValue   = -136

; struct DCCallback
CTX_thunk       =    0
CTX_handler     =   24
CTX_userdata    =   32
DCCallback_size =   40


dcCallbackThunkEntry PROC EXPORT

  OPTION PROLOGUE:NONE, EPILOGUE:NONE

  push     rbp
  mov      rbp, rsp

  ; initialize DCArgs

  ; float parameters (8 registers spill to DCArgs)
  sub      rsp, 8*8
  movd     qword ptr[rsp+8*7], xmm7         ; struct offset 124: float parameter 7
  movd     qword ptr[rsp+8*6], xmm6         ; struct offset 116: float parameter 6
  movd     qword ptr[rsp+8*5], xmm5         ; struct offset 108: float parameter 5
  movd     qword ptr[rsp+8*4], xmm4         ; struct offset  96: float parameter 4
  movd     qword ptr[rsp+8*3], xmm3         ; struct offset  88: float parameter 3
  movd     qword ptr[rsp+8*2], xmm2         ; struct offset  80: float parameter 2
  movd     qword ptr[rsp+8*1], xmm1         ; struct offset  72: float parameter 1
  movd     qword ptr[rsp+8*0], xmm0         ; struct offset  64: float parameter 0

  ; integer parameters (6 registers spill to DCArgs)
  push     r9                      ; struct offset 56: parameter 5
  push     r8                      ; struct offset 48: parameter 4
  push     rcx                     ; struct offset 40: parameter 3
  push     rdx                     ; struct offset 32: parameter 2
  push     rsi                     ; struct offset 24: parameter 1
  push     rdi                     ; struct offset 16: parameter 0

  ; register counts for integer/pointer and float regs
                                   ; struct offset 12: fcount
  push     0                       ; struct offset  8: icount

  lea      rdx, [rbp+FRAME_arg0]   ; struct offset  0: stack pointer
  push     rdx

  mov      rsi, rsp                ; parameter 1 (RSI) = DCArgs*

  ; initialize DCValue

  push     0                       ; structo offset 0: return value (max long long)

  ; call handler( *ctx, *args, *value, *userdata)
  mov      rdi, rax                ; parameter 0 (RDI) = DCCallback* (RAX)
  mov      rcx, [rdi+CTX_userdata] ; arg3 = userdata*
  mov      rdx, rsp                ; arg2 (RDX) = DCValue*

  push     0                       ; align to 16 bytes

  call     qword ptr[rax+CTX_handler]

  ; return values
  mov      rdx, [rbp+FRAME_DCValue]
  movd     xmm0, rdx

  mov      rsp, rbp
  pop      rbp

  ret

dcCallbackThunkEntry ENDP

END
