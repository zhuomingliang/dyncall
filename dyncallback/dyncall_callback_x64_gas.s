.intel_syntax
.text
.globl dcCallbackThunkEntry

/* sizes */

.eqv DCThunk_size	,  24
.eqv DCArgs_size	, 128
.eqv DCValue_size	,   8

/* frame local variable offsets relative to %rbp*/

.eqv FRAME_arg0		,  16
.eqv FRAME_return	,   8
.eqv FRAME_parent	,   0
.eqv FRAME_DCArgs	,-128
.eqv FRAME_DCValue	,-136

/* struct DCCallback */

.eqv CTX_thunk		,   0
.eqv CTX_handler	,  24
.eqv CTX_userdata	,  32
.eqv DCCallback_size	,  40

dcCallbackThunkEntry:

	pushq %rbp
	movq  %rbp, %rsp
	
	// initialize DCArgs

	// float parameters (8 registers spill to DCArgs)
	sub %rsp, 8*8
	movq [%rsp+8*7], %xmm7  # struct offset 124: float parameter 7
	movq [%rsp+8*6], %xmm6  # struct offset 116: float parameter 6
	movq [%rsp+8*5], %xmm5  # struct offset 108: float parameter 5
	movq [%rsp+8*4], %xmm4  # struct offset  96: float parameter 4
	movq [%rsp+8*3], %xmm3  # struct offset  88: float parameter 3
	movq [%rsp+8*2], %xmm2  # struct offset  80: float parameter 2
	movq [%rsp+8*1], %xmm1  # struct offset  72: float parameter 1
	movq [%rsp+8*0], %xmm0	# struct offset  64: float parameter 0

	// integer parameters (6 registers spill to DCArgs)
	pushq %r9	# struct offset 56: parameter 5
	pushq %r8	# struct offset 48: parameter 4
	pushq %rcx	# struct offset 40: parameter 3
	pushq %rdx	# struct offset 32: parameter 2
	pushq %rsi	# struct offset 24: parameter 1
	pushq %rdi	# struct offset 16: parameter 0

	// register counts for integer/pointer and float regs
			# struct offset 12: fcount
	pushq 0		# struct offset 8:  icount	

	lea  %rdx, [%rbp+FRAME_arg0]	# struct offset 0: stack pointer
	pushq %rdx

	mov  %rsi, %rsp			# parameter 1 (RSI) = DCArgs*

	// initialize DCValue

	pushq 0				# structo offset 0: return value (max long long)

	// call handler( *ctx, *args, *value, *userdata)

	mov  %rdi, %rax			# parameter 0 (RDI) = DCCallback* (RAX)
	mov  %rcx, [%rdi+CTX_userdata]	# arg3 = userdata*
	mov  %rdx, %rsp 		# arg2 (RDX) = DCValue* 

	pushq 0				# align to 16 bytes

	call [%rax+CTX_handler]

	// return values

	movq  %rdx, [%rbp+FRAME_DCValue]
	movq  %xmm0, %rdx

	mov  %rsp, %rbp
	pop  %rbp

	ret

