/*/////////////////////////////////////////////////////////////////////////////

  dyncall callvm for 32bit MIPS family of processors
  Copyright 2007 Daniel Adler.

  SUPPORTED CALLING CONVENTIONS
  @@@

  REVISION
  2008/01/03 initial

/////////////////////////////////////////////////////////////////////////////*/


#ifndef DYNCALL_CALLVM_MIPS32_H
#define DYNCALL_CALLVM_MIPS32_H

#include "dyncall_call_mips32.h"
#include "dyncall_callvm.h"
#include "dyncall_vector.h"


typedef struct
{
  DCCallVM  mInterface;
  int mIntRegs;
  int mSingleRegs;
  struct DCRegData_mips32 mRegData;
  DCVecHead mVecHead;
} DCCallVM_mips32;

DCCallVM* dcNewCallVM_mips32(DCsize size);


#endif /* DYNCALL_CALLVM_MIPS32_H */

