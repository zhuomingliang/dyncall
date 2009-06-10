#ifndef DYNCALL_THUNK_X86_H
#define DYNCALL_THUNK_X86_H

struct DCThunk_
{
  unsigned int code_load;
  void*        addr_self;
  unsigned int code_jump;
  void*        addr_entry;
};

#define DCTHUNK_X86_SIZE	16

#endif /* DYNCALL_THUNK_X86_H */
