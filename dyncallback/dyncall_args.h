#ifndef DYNCALL_ARGS_H
#define DYNCALL_ARGS_H

/*
 * dyncall args C API
 *
 * dyncall args provides serialized access to arguments of a function call.
 * related concepts: callback
 *
 */

#include "dyncall.h"

#ifndef DC_API
#define DC_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DCArgs DCArgs;

DC_API DCbool      dcArgs_bool     (DCArgs*);
DC_API DCchar      dcArgs_char     (DCArgs*);
DC_API DCshort     dcArgs_short    (DCArgs*);
DC_API DCint       dcArgs_int      (DCArgs*);
DC_API DClong      dcArgs_long     (DCArgs*);
DC_API DClonglong  dcArgs_longlong (DCArgs*);
DC_API DCuchar     dcArgs_uchar    (DCArgs*);
DC_API DCushort    dcArgs_ushort   (DCArgs*);
DC_API DCuint      dcArgs_uint     (DCArgs*);
DC_API DCulong     dcArgs_ulong    (DCArgs*);
DC_API DCulonglong dcArgs_ulonglong(DCArgs*);
DC_API DCfloat     dcArgs_float    (DCArgs*);
DC_API DCdouble    dcArgs_double   (DCArgs*);
DC_API DCpointer   dcArgs_pointer  (DCArgs*);

#ifdef __cplusplus
}
#endif

#endif /* DYNCALL_ARGS_H */
