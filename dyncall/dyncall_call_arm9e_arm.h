/*/////////////////////////////////////////////////////////////////////////////

  dyncall 32bit ARM9E family interface
  Copyright 2007 Tassilo Philipp.

  REVISION
  2007/12/11 initial

/////////////////////////////////////////////////////////////////////////////*/


#ifndef DYNCALL_CALL_ARM9_ARM_H
#define DYNCALL_CALL_ARM9_ARM_H


#include "dyncall_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 
** arm9e arm mode calling convention calls 
**
** - hybrid return-type call (bool ... pointer)
**
*/

void dcCall_arm9e_arm(DCpointer target, DCpointer stackdata, DCsize size);

#ifdef __cplusplus
}
#endif


#endif /* DYNCALL_CALL_ARM9_ARM_H */
