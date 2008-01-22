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

#ifndef DYNCALL_SIGNATURE_H
#define DYNCALL_SIGNATURE_H

typedef char DCsigchar;

/** signature character for void */
#define DC_SIGCHAR_VOID         'v'
/** signature character for bool */
#define DC_SIGCHAR_BOOL         'B'
/** signature character for char */
#define DC_SIGCHAR_CHAR         'c'
/** signature character for short */
#define DC_SIGCHAR_SHORT        's'
/** signature character for int */
#define DC_SIGCHAR_INT          'i'
/** signature character for long */
#define DC_SIGCHAR_LONG         'l'
/** signature character for long long */
#define DC_SIGCHAR_LONGLONG     'L'
/** signature character for float */
#define DC_SIGCHAR_FLOAT        'f'
/** signature character for double */
#define DC_SIGCHAR_DOUBLE       'd'
/** signature character for pointer */
#define DC_SIGCHAR_POINTER      'p'
/** signature character for string (abstract datatype) */
#define DC_SIGCHAR_STRING       'S'
/** signature character for end-of-arguments marker */
#define DC_SIGCHAR_ENDARG       ')'

#endif /* DYNCALL_SIGNATURE_H */

