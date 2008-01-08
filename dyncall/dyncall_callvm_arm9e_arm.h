/*/////////////////////////////////////////////////////////////////////////////

  dyncall callvm for 32bit ARM9E family of processors
  Copyright 2007 Tassilo Philipp.

  SUPPORTED CALLING CONVENTIONS
  armcall

  REVISION
  2007/12/11 initial

/////////////////////////////////////////////////////////////////////////////*/


#ifndef DYNCALL_CALLVM_ARM9E_ARM_H
#define DYNCALL_CALLVM_ARM9E_ARM_H

#include "dyncall_call_arm9e_arm.h"
#include "dyncall_callvm.h"
#include "dyncall_vector.h"


typedef struct
{
  DCCallVM  mInterface;
  DCpointer mpCallFunc;
  DCVecHead mVecHead;
} DCCallVM_arm9e_arm;

DCCallVM* dcNewCallVM_arm9e_arm(DCsize size);


#endif /* DYNCALL_CALLVM_ARM9E_ARM_H */

