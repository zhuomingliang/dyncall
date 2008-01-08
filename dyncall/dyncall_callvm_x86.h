#ifndef DYNCALL_CALLVM_X86_H
#define DYNCALL_CALLVM_X86_H

/*/////////////////////////////////////////////////////////////////////////////

  dyncall callvm for 32bit X86 architectures
  Copyright 2007 Daniel Adler.

  SUPPORTED CALLING CONVENTIONS
  cdecl,stdcall,fastcall,thiscall,msthiscall

  REVISION
  2007/12/10 initial

/////////////////////////////////////////////////////////////////////////////*/


#include "dyncall_call_x86.h"
#include "dyncall_callvm.h"
#include "dyncall_vector.h"

typedef struct DCCallVM_x86_ DCCallVM_x86;

struct DCCallVM_x86_
{
  DCCallVM  mInterface;
  DCpointer mpCallFunc;
  int       mIntRegs;     /* used by fastcall implementation */
  DCVecHead mVecHead;
};

DCCallVM* dcNewCallVM_x86_cdecl(DCsize size);
DCCallVM* dcNewCallVM_x86_win32_std(DCsize size);
DCCallVM* dcNewCallVM_x86_win32_fast(DCsize size);
DCCallVM* dcNewCallVM_x86_win32_this_ms(DCsize size);

#endif /* DYNCALL_CALLVM_X86_H */

