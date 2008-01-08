#ifndef DYNCALL_CALLVM_PPC32_H
#define DYNCALL_CALLVM_PPC32_H

/*/////////////////////////////////////////////////////////////////////////////

  dyncall callvm for 32bit ppc architectures
  Copyright 2007 Daniel Adler.

  SUPPORTED CALLING CONVENTIONS
  standard and ... (ellipse) calls

  REVISION
  2007/12/11 initial

/////////////////////////////////////////////////////////////////////////////*/


#include "dyncall_call_ppc32.h"
#include "dyncall_callvm.h"
#include "dyncall_vector.h"

typedef struct DCCallVM_ppc32_ DCCallVM_ppc32;


struct DCCallVM_ppc32_
{
  DCCallVM  mInterface;
  int       mIntRegs;
  int       mFloatRegs;
  struct DCRegData_ppc32 mRegData;
  DCVecHead mVecHead;
};

DCCallVM* dcNewCallVM_ppc32(DCsize size);

#endif /* DYNCALL_CALLVM_PPC32_H */

