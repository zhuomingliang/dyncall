/*/////////////////////////////////////////////////////////////////////////////

 Copyright (c) 2007,2008 Daniel Adler <dadler@uni-goettingen.de>, 
                         Tassilo Philipp <tphilipp@potion-studios.com>

 Permission to use, copy, modify, and distribute this software for any
 purpose with or without fee is hereby granted, provided that the above
 copyright notice and this permission notice appear in all copies.

 THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

/////////////////////////////////////////////////////////////////////////////*/

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

