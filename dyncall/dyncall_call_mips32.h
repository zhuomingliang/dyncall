/*/////////////////////////////////////////////////////////////////////////////

  dyncall 32bit MIPS family interface
  Copyright 2007 Daniel Adler.

  REVISION
  2008/01/03 initial

/////////////////////////////////////////////////////////////////////////////*/


#ifndef DYNCALL_CALL_MIPS32_H
#define DYNCALL_CALL_MIPS32_H


#include "dyncall_types.h"

#ifdef __cplusplus
extern "C" {
#endif


struct DCRegData_mips32
{
  DCint   mIntData[8];
  DCfloat mSingleData[8];
};

/* 
** arm9e arm mode calling convention calls 
**
** - hybrid return-type call (bool ... pointer)
**
*/

void dcCall_mips32(DCpointer target, struct DCRegData_mips32* mips32data, DCsize stksize, DCpointer stkdata);

#ifdef __cplusplus
}
#endif


#endif /* DYNCALL_CALL_MIPS32_H */
