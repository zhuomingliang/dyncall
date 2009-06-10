#include "dyncall_thunk.h"

void dcThunkInit(DCThunk* p, void* entry )
{
  /*
    ppc32 thunk code:
	ori   r2 , r0, LO16(p)
	oris  r2 , r0, HI16(p)
	lwz   r12, 20(r2)
	mtctr r12
	bctr
  */

  p->code_load_lo = 0x6002U;     /* ori   r2, r0,LO16(p) */
  p->addr_self_lo = ( (unsigned short) ( (unsigned int)p ) );
  p->code_load_hi = 0x6402U; 	 /* oris  r2, r0,HI16(p) */
  p->addr_self_hi = (unsigned short) ( ((unsigned int)p) >> 16U );
  p->code_jump[0] = 0x81820014U; /* lwz   r12, 20(r2) */
  p->code_jump[1] = 0x7d8903a6U; /* mtclr r12 */
  p->code_jump[2] = 0x4e800420U; /* bctr */
  p->addr_entry   = entry;
}
