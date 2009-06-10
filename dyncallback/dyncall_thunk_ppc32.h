#ifndef DYNCALL_THUNK_PPC32_H
#define DYNCALL_THUNK_PPC32_H

struct DCThunk_
{
  unsigned short code_load_lo, addr_self_lo;
  unsigned short code_load_hi, addr_self_hi;
  unsigned int   code_jump[3];
  void*          addr_entry;
};

#define DCTHUNK_SIZE_PPC32 40

#endif // DYNCALL_THUNK_PPC32_H

