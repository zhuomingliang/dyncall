/*
 Package: dyncall
 Library: dyncallback
 File: dyncallback/dyncall_thunk_ppc32.c
 Description: Thunk - Implementation for ppc32
 License:

 Copyright (c) 2007-2009 Daniel Adler <dadler@uni-goettingen.de>,
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
#include "dyncall_thunk.h"

void dcThunkInit(DCThunk* p, void* entry)
{
  /*
    ppc32 thunk code:
      ori   r2 , r0, LO16(p)
      oris  r2 , r0, HI16(p)
      lwz   r12, 20(r2)
      mtctr r12
      bctr
  */

  p->code_load_lo = 0x6002U;     /* ori   r2, r0, LO16(p) */
  p->addr_self_lo = ( (unsigned short) ( (unsigned int)p ) );
  p->code_load_hi = 0x6402U; 	 /* oris  r2, r0, HI16(p) */
  p->addr_self_hi = (unsigned short) ( ((unsigned int)p) >> 16U );
  p->code_jump[0] = 0x81820014U; /* lwz   r12, 20(r2) */
  p->code_jump[1] = 0x7d8903a6U; /* mtclr r12 */
  p->code_jump[2] = 0x4e800420U; /* bctr */
  p->addr_entry   = entry;
}
