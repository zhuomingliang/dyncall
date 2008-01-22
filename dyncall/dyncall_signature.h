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
#define DC_SIGCHAR_POINTER      'S'
/** signature character for end-of-arguments marker */
#define DC_SIGCHAR_ENDARG       ')'

#endif /* DYNCALL_SIGNATURE_H */

