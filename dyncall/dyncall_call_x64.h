/*/////////////////////////////////////////////////////////////////////////////

  dyncall x64
  Copyright 2007 Tassilo Philipp.

  REVISION
  2007/12/11 initial

/////////////////////////////////////////////////////////////////////////////*/


#ifndef DYNCALL_CALL_X64_H
#define DYNCALL_CALL_X64_H


#include "dyncall.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 
** x64 SystemV calling convention 
**
** - hybrid return-type call (bool ... pointer)
**
*/

#if defined(DC_UNIX)
void dcCall_x64(DCsize stacksize, DCpointer stackdata, DCpointer regdata_i, DCpointer regdata_f, DCpointer target);
#elif defined(DC_WINDOWS)
void dcCall_x64(DCsize stacksize, DCpointer stackdata, DCpointer regdata, DCpointer target);
#else
#error Unsupported OS.
#endif

#ifdef __cplusplus
}
#endif


#endif /* DYNCALL_CALL_X64_H */

