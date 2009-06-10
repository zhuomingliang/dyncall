#include "dyncall_thunk.h"

void dcThunkInit(DCThunk* p, void* entry )
{
  /*
    x86 thunk code:
	nop
	nop
	nop
	mov %eax, p
	jmp [%eax+12]
	nop
   */

  p->code_load  = 0xb8909090UL; /* nop;nop;nop;mov %eax, ... */
  p->addr_self  = p;
  p->code_jump  = 0x900C60ffUL; /* jmp [%eax+12] ; nop */
  p->addr_entry = entry;
}
