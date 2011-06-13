/*
 Package: dyncall
 Library: dyncallback
 File: dyncallback/dyncall_callback_arch_x64.S
 Description: Callback Thunk entry for x64 (portasm version)
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

#include "../portasm/portasm-x64-att.S"

/* structure sizes */

SET(DCThunk_size,24)
SET(DCArgs_size,128)
SET(DCValue_size,8)

/* frame local variable offsets relative to %rbp*/

SET(FRAME_arg0,16)
SET(FRAME_return,8)
SET(FRAME_parent,0)
SET(FRAME_DCArgs,-128)
SET(FRAME_DCValue,-136)

/* struct DCCallback */

SET(CTX_thunk,0)
SET(CTX_handler,24)
SET(CTX_userdata,32)
SET(DCCallback_size,40)

/* character constants */

SET(ASCII_f,102)
SET(ASCII_d,100)

GLOBAL(dcCallbackThunkEntry)
BEGIN_PROC(dcCallbackThunkEntry)
	
	PUSHQ(RBP)
	MOVQ(RSP,RBP)

	/* initialize DCArgs */

	/* float parameters (8 registers spill to DCArgs) */

	SUBQ(LIT(8*8),RSP)	
	
	MOVQ(XMM7, QWORD(RSP,8*7))		/* struct offset 120: float parameter 7 */
	MOVQ(XMM6, QWORD(RSP,8*6))		/* struct offset 112: float parameter 6 */
	MOVQ(XMM5, QWORD(RSP,8*5))		/* struct offset 104: float parameter 5 */
	MOVQ(XMM4, QWORD(RSP,8*4))		/* struct offset  96: float parameter 4 */
	MOVQ(XMM3, QWORD(RSP,8*3))		/* struct offset  88: float parameter 3 */
	MOVQ(XMM2, QWORD(RSP,8*2))		/* struct offset  80: float parameter 2 */
	MOVQ(XMM1, QWORD(RSP,8*1))		/* struct offset  72: float parameter 1 */
	MOVQ(XMM0, QWORD(RSP,8*0))		/* struct offset  64: float parameter 0 */

	/* integer parameters (6 registers spill to DCArgs) */

	PUSHQ(R9)				/* struct offset 56: parameter 5 */
	PUSHQ(R8)				/* struct offset 48: parameter 4 */
	PUSHQ(RCX)				/* struct offset 40: parameter 3 */
	PUSHQ(RDX)				/* struct offset 32: parameter 2 */
	PUSHQ(RSI)				/* struct offset 24: parameter 1 */
	PUSHQ(RDI)				/* struct offset 16: parameter 0 */

	/* register counts for integer/pointer and float regs */

	PUSHQ(LIT(0))				/* struct offset 12: fcount */
						/* struct offset  8: icount */

	LEA(QWORD(RBP,FRAME_arg0),RDX)		/* struct offset  0: stack pointer */
	PUSHQ(RDX)

	MOVQ(RSP,RSI)				/* arg 1 RSI : DCArgs* */
	
	/* initialize DCValue */

	PUSHQ(LIT(0))				/* struct offset 0: return value (max long long) */

	/* call handler( *ctx, *args, *value, *userdata) */

	MOVQ(RAX,RDI)				/* arg 0 RDI : DCCallback* (RAX) */
	MOVQ(QWORD(RDI,CTX_userdata),RCX)	/* arg 3 RCX : userdata* */
	MOVQ(RSP,RDX)				/* arg 2 RDX : DCValue*  */
	PUSHQ(LIT(0))				/* align to 16 bytes */
	CALL_REG(QWORD(RAX,CTX_handler))

	/* pass return type via registers */
	/* distinguish two basic classes 'integer' and 'float' */
	
	MOVB(AL,DL)
	MOVQ(QWORD(RBP,FRAME_DCValue),RAX)

	CMPB(LIT(ASCII_f),DL)
	JE(.float)
	CMPB(LIT(ASCII_d),DL)
	JNE(.return)

.float:
	MOVD(RAX,XMM0)

.return:
	MOVQ(RBP,RSP)
	POPQ(RBP)
	RET()

