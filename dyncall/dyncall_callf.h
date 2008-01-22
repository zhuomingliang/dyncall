#ifndef DYNCALL_CALLF_H
#define DYNCALL_CALLF_H

#include "dyncall.h"
#include "dyncall_signature.h"
#include "dyncall_value.h"

#include <stdarg.h>

/** \defgroup FormattedCalls Formatted function calls (C ellipsis call interface) */
/*@{*/

/** Formatted function call
 *  @param vm Pointer on opaque CallVM structure.
 *  @param result Variant structure to store return value.
 *  @param funcptr pointer on target function.
 *  @param signature signature string that encodes the parameter types and return type.
 *  @param ... ellipsis call variable arguments.
 **/
void dcCallF (DCCallVM* vm, DCValue* result, DCpointer funcptr, const DCsigchar* signature, ...);

/** Formatted function call
 *  @param vm Pointer on opaque CallVM structure.
 *  @param result Variant structure to store return value.
 *  @param funcptr pointer on target function.
 *  @param signature signature string that encodes the parameter types and return type.
 *  @param args va_list of arguments.
 **/
void dcVCallF(DCCallVM* vm, DCValue* result, DCpointer funcptr, const DCsigchar* signature, va_list args);

/*@}*/

#endif /* DYNCALL_CALLF_H */

