#include "dyncall_args_ppc32.h"

DClonglong  dcArgs_longlong (DCArgs* p) { return 0; }
DCulonglong dcArgs_ulonglong(DCArgs* p) { return (DCulonglong) dcArgs_longlong(p); }

DCint       dcArgs_int      (DCArgs* p) { return 0; }
DCuint      dcArgs_uint     (DCArgs* p) { return (DCuint)  dcArgs_int(p);  }
DClong      dcArgs_long     (DCArgs* p) { return (DClong)  dcArgs_uint(p); }
DCchar      dcArgs_char     (DCArgs* p) { return (DCchar)  dcArgs_uint(p); }
DCuchar     dcArgs_uchar    (DCArgs* p) { return (DCuchar)     dcArgs_uint(p);     }
DCshort     dcArgs_short    (DCArgs* p) { return (DCshort) dcArgs_uint(p); }
DCushort    dcArgs_ushort   (DCArgs* p) { return (DCushort)    dcArgs_uint(p);    }
DCbool      dcArgs_bool     (DCArgs* p) { return (DCbool)  dcArgs_uint(p); }

DCulong     dcArgs_ulong    (DCArgs* p) { return (DCulong)     dcArgs_uint(p);     }


DCpointer   dcArgs_pointer  (DCArgs* p) { return (DCpointer)   dcArgs_uint(p); }

DCdouble    dcArgs_double   (DCArgs* p) { return 0; }
DCfloat     dcArgs_float    (DCArgs* p) { return (float) dcArgs_double(p); }

