/*//////////////////////////////////////////////////////////////////////

	dyncall_ppc32.h
	Copyright 2007 Daniel Adler.

*///////////////////////////////////////////////////////////////////////


#ifndef DYNCALL_PPC32_H
#define DYNCALL_PPC32_H

#include "dyncall_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct DCRegData_ppc32
{
  DCint     mIntData[8];
  DCdouble  mFloatData[13];
};

/* 
** PowerPC 32-bit calling convention call
**
** - hybrid return-type call (bool ... pointer)
**
*/

void     dcCall_ppc32    (DCpointer target, struct DCRegData_ppc32* ppc32data, DCsize stksize, DCpointer stkdata);

#ifdef __cplusplus
}
#endif

#endif /* DYNCALL_PPC32_H */

