#ifndef DYNCALL_ELLIPSE_H
#define DYNCALL_ELLIPSE_H

#include "dyncall_callvm.h"
#include "dyncall_signature.h"
#include "dyncall_value.h"

#include <stdarg.h>

/*
 * formatted call - C ellipsis call interface to CallVM's
 * 
 */

void dcCallF (DCCallVM* vm, DCValue* result, DCpointer funcptr, const DCsigchar* signature, ...);
void dcVCallF(DCCallVM* vm, DCValue* result, DCpointer funcptr, const DCsigchar* signature, va_list args);

#endif /* DYNCALL_ELLIPSE_H */

