#include "dyncall_thunk.h"

void dcThunkInit(DCThunk* p, void* entry )
{
  /*
    # x64 thunk code:
    .intel_syntax

    thunk:
        lea   rax, (rip)
        jmp   [rax+16]
        nop
        nop
        nop
    entry:
        .resq 1
   */

  p->code[0] = 0xfffffffff9058d48ULL;
  p->code[1] = 0x9090900000000325ULL;
  p->entry   = (unsigned long long) entry;
}

