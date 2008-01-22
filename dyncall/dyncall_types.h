#ifndef DC_TYPES_H
#define DC_TYPES_H

#include <stddef.h>

#include "dyncall_config.h"

#ifdef __cplusplus
extern "C" {
#endif 

/* supported argument types */

/** 
 * C void type 
 * Signature character 'v'
 */
typedef void            DCvoid;
/** 
 * C bool type 
 * Signature character 'B'
 */
typedef DC_BOOL         DCbool;
/** 
 * C char type 
 * Signature character 'c'
 */
typedef char            DCchar;
/** 
 * C short type
 * Signature character 's'
 */
typedef short           DCshort;
/**
 * C int type
 * Signature chararcter 'i'
 */
typedef int             DCint;
/**
 * C long type
 * Signature character 'l'
 */
typedef long            DClong;
/**
 * C long long type
 */
typedef DC_LONG_LONG    DClonglong;
typedef float           DCfloat;
typedef double          DCdouble;
typedef DC_POINTER      DCpointer;

/* misc types */

typedef size_t          DCsize;

/* constants */

#define DC_TRUE   1
#define DC_FALSE  0

#ifdef __cplusplus
}
#endif

#endif /* DC_TYPES_H */

