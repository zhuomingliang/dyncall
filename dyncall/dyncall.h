#ifndef DYNCALL_H
#define DYNCALL_H

/*/////////////////////////////////////////////////////////////////////////////
                              
                 dyncall library - ANSI C API - Version 0.2 

//////////////////////////////////////////////////////////////////////////// */

#ifdef __cplusplus
extern "C" {
#endif 

#include "dyncall_types.h"

/* library api */
#define DC_API

/* forward declaration */
typedef struct DCCallVM_    DCCallVM;

/* supported calling conventions */

#define DC_CALL_C_DEFAULT               0
#define DC_CALL_C_X86_WIN32_STD         1
#define DC_CALL_C_X86_WIN32_FAST_MS     2
#define DC_CALL_C_X86_WIN32_THIS_MS     3
#define DC_CALL_C_X86_WIN32_THIS_GNU    4
#define DC_CALL_C_X64_WIN64             5
#define DC_CALL_C_PPC32_DARWIN          6
#define DC_CALL_C_ARM                   7

/* callvm allocation function */

DC_API DCCallVM* dcNewCallVM     (DCsize size);

/* callvm control functions */

DC_API void      dcFree           (DCCallVM* vm);
DC_API void      dcReset          (DCCallVM* vm);
DC_API void      dcMode           (DCCallVM* vm, DCint          mode);

/* argument functions */

DC_API void       dcArgBool       (DCCallVM* vm, DCbool        value);
DC_API void       dcArgChar       (DCCallVM* vm, DCchar        value);
DC_API void       dcArgShort      (DCCallVM* vm, DCshort       value);
DC_API void       dcArgInt        (DCCallVM* vm, DCint         value);
DC_API void       dcArgLong       (DCCallVM* vm, DClong        value);
DC_API void       dcArgLongLong   (DCCallVM* vm, DClonglong    value);
DC_API void       dcArgFloat      (DCCallVM* vm, DCfloat       value);
DC_API void       dcArgDouble     (DCCallVM* vm, DCdouble      value);
DC_API void       dcArgPointer    (DCCallVM* vm, DCpointer     value);

/* call functions */

DC_API void       dcCallVoid      (DCCallVM* vm, DCpointer   funcptr);
DC_API DCbool     dcCallBool      (DCCallVM* vm, DCpointer   funcptr);
DC_API DCchar     dcCallChar      (DCCallVM* vm, DCpointer   funcptr);
DC_API DCshort    dcCallShort     (DCCallVM* vm, DCpointer   funcptr);
DC_API DCint      dcCallInt       (DCCallVM* vm, DCpointer   funcptr);
DC_API DClong     dcCallLong      (DCCallVM* vm, DCpointer   funcptr);
DC_API DClonglong dcCallLongLong  (DCCallVM* vm, DCpointer   funcptr);
DC_API DCfloat    dcCallFloat     (DCCallVM* vm, DCpointer   funcptr);
DC_API DCdouble   dcCallDouble    (DCCallVM* vm, DCpointer   funcptr);
DC_API DCpointer  dcCallPointer   (DCCallVM* vm, DCpointer   funcptr);

#ifdef __cplusplus
}
#endif

#endif /* DYNCALL_H */

