/*/////////////////////////////////////////////////////////////////////////////

  dyncall 32bit ARM9E family interface
  Copyright 2007 Daniel Adler.

  REVISION
  2007/12/10 initial

/////////////////////////////////////////////////////////////////////////////*/


#ifndef DYNCALL_CALL_X86_H
#define DYNCALL_CALL_X86_H


#include "dyncall_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 
** x86 calling convention calls 
**
** - hybrid return-type call (bool ... pointer)
**
*/

void dcCall_x86_cdecl        (DCpointer target, DCpointer stackdata, DCsize size);
void dcCall_x86_win32_std    (DCpointer target, DCpointer stackdata, DCsize size);
void dcCall_x86_win32_fast   (DCpointer target, DCpointer stackdata, DCsize size);
void dcCall_x86_win32_msthis (DCpointer target, DCpointer stackdata, DCsize size);

#ifdef __cplusplus
}
#endif


#endif /* DYNCALL_CALL_X86_H */
