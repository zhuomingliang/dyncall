#ifndef DYNCALL_THUNK_H
#define DYNCALL_THUNK_H

/**
 ** dyncall thunks
 **
 ** thunks are small-size hybrid code/data objects, created at run-time to
 ** be used as function pointers with associated data and entry functions.
 **
 ** The header contains code, that does load its address into a designated scratch
 ** register and will jump to a thunk function.
 **
 ** Thunk entry procedures are compiled functions, that are called as a result of
 ** a thunk function.
 ** There is one thunk entry currently for supporting callbacks.
 **
 ** Thunk context register ( ::= an available scratch register in the calling convention):
 **
 ** x86:  eax
 ** x64:  rax
 ** ppc:   r2
 **
 **/

#include "dyncall_macros.h"

typedef struct DCThunk_ DCThunk;

void   dcThunkInit(DCThunk* p, void* entry );

#if defined DC__Arch_Intel_x86
#include "dyncall_thunk_x86.h"
#endif

#if defined DC__Arch_AMD64
#include "dyncall_thunk_x64.h"
#endif

#if defined DC__Arch_PowerPC
#include "dyncall_thunk_ppc32.h"
#endif

#endif /* DYNCALL_THUNK_H */

