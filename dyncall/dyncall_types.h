#ifndef DC_TYPES_H
#define DC_TYPES_H

#include <stddef.h>

#include "dyncall_config.h"

#ifdef __cplusplus
extern "C" {
#endif 

/** /defgroup SupportedTypes supported argument types */
/*@{*/

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
/**
 * C float type
 */
typedef float           DCfloat;
/**
 * C double type
 */
typedef double          DCdouble;
/** 
 * C pointer type
 */
typedef DC_POINTER      DCpointer;

/*@}*/

/** misc types */

/**
 * C size type
 */
typedef size_t          DCsize;

/** /defgroup Constants constants */
/*@{*/

/** integer constant for boolean TRUE encoding */
#define DC_TRUE   1
/** integer constant for boolean FALSE encoding */
#define DC_FALSE  0

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* DC_TYPES_H */

