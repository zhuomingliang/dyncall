#ifndef DC_TYPES_H
#define DC_TYPES_H

#include <stddef.h>
#include "dyncall_config.h"

/* supported argument types */

typedef void            DCvoid;
typedef DC_BOOL         DCbool;
typedef char            DCchar;
typedef short           DCshort;
typedef int             DCint;
typedef long            DClong;
typedef DC_LONG_LONG    DClonglong;
typedef float           DCfloat;
typedef double          DCdouble;
typedef DC_POINTER      DCpointer;

/* misc types */

typedef size_t          DCsize;

/* constants */

#define DC_TRUE   1
#define DC_FALSE  0

#endif /* DC_TYPES_H */

