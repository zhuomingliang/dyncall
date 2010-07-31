/*
 Package: dyncall
 File: dyncall/dyncall_call_x86_8a.s
 Description: All x86 abi call kernel implementations in Plan9's assembler
 License:

 Copyright (c) 2007-2010 Daniel Adler <dadler@uni-goettingen.de>,
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

TEXT dcCall_x86_cdecl(SB), 8

	PUSHL EBP           /* PROLOG */
 	MOVL  ESP, EBP

	/* ARGUMENTS:
	   FUNPTR   8(EBP)
	   ARGS    12(EBP)
	   SIZE    16(EBP)
	   RESULT  20(EBP)
	 */

	MOVL  12(EBP), ESI  /* ESI = POINTER ON ARGS */
	MOVL  16(EBP), ECX  /* ECX = SIZE */

	SUBL  ECX, ESP      /* CDECL CALL: ALLOCATE 'SIZE' BYTES ON STACK */
	MOVL  ESP, EDI      /* EDI = STACK ARGS */

	SHRL  $2, ECX       /* ECX = NUMBER OF DWORDs to copy */
	REP; MOVL SI, DI    /* COPY DWORDs */

	CALL  8(EBP)        /* CALL FUNCTION */

	ADDL  16(EBP), ESP  /* CDECL CALL: CLEANUP STACK */

	MOVL  EBP, ESP      /* EPILOG */
	POPL  EBP

	RET

