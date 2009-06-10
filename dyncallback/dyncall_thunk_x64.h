#ifndef DYNCALL_THUNK_X64_H
#define DYNCALL_THUNK_X64_H

struct DCThunk_
{
  unsigned long long code[2];
  unsigned long long entry;
};

#define DCTHUNK_X64_SIZE	24


#endif /* DYNCALL_THUNK_X64_H */

