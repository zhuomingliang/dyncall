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


TEXT dcCall_x86_cdecl(SB), $0

    /* Since all registers except SP are scratch, and we have a variable
       argument size depending on the function to call, we have to find
       a way to store and restore SP.
       The idea is to replace the return address with a custom one on the
       stack, and to put some logic there, jumping back to the real
       return address. This allows us, to put the SP somewhere next to
       the fake return address on the stack, so that we can get it back
       with a fixed offset. */

    /* On the stack at this point:
       RETADDR  0(SP)
       FUNPTR   4(SP)
       ARGS     8(SP)
       SIZE    12(SP)
    */

    MOVL  SP, BP
    PUSHL SP          /* save stack pointer */

    MOVL   0(BP), AX  /* Copy real return address to AX */
    MOVL   8(BP), SI  /* SI = pointer on args */
    MOVL  12(BP), CX  /* CX = size of args */

	SUBL  $16, SP     /* Make some room for our SP-refetch logic */
	MOVL   SP, BX     /* Copy address to executable stack space to BX */

    /* This part fills our executable stack space with instructions. We
       need to get the program counter, first, with a little hack. */
    MOVL  $0x000003e8, 0(SP) /* Copy 'call (cur ip+8)' */
    MOVL  $0x00000000, 4(SP) /* '00' for call address, rest is garbage */
    MOVL  $0x5a909090, 8(SP) /* 'nop,nop,nop,pop edx' to get eip+5 in edx */
    MOVL  $0xc30b628b,12(SP) /* Restore stack ptr and return: 'mov [edx+11] to esp, ret' */

    SUBL  CX, SP      /* cdecl call - allocate 'size' bytes on stack */
    MOVL  SP, DI      /* DI = stack args */

MOVL CX, 0(DI)/* dummy for now @@@ loop over the args is missing - copy 1 dword*/
/*    SHRL  $2, CX      /* CX = NUMBER OF DWORDs to copy */
/*    REP; MOVL 0(SI), 0(DI)  /* COPY DWORDs */


    /* Now we try to fake a call, meaning copy our fake return address, and
       then modifying the program counter manually. This should call the
       function, but jump back into our stack space we reserved above. */
    PUSHL BX
    MOVL  4(BP), BX
    JMP   BX

    /* Note that there is no return here, b/c the return is in the asm code
       above, that has been generated on the fly. */
