/*
 Package: dyncall
 Library: dyncallback
 File: dyncallback/dyncall_args_arm32_arm.c
 Description: Callback's Arguments VM - Implementation for ARM32 (ARM mode)
 License:
 Copyright (c) 2007-2009 Daniel Adler <dadler@uni-goettingen.de>,
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
*/

#include "dyncall_args_arm32_arm.h"


static void arm_align_64(DCArgs* args)
{
  /* Look at signature to see if current calling convention needs alignment */
  /* or not (e.g. EABI has different alignment). If nothing specified, fall */
  /* back to default behaviour for this platform.                           */
  /* @@@ check signature string */

  int sig =
#if defined(DC__OS_NDS)
    0; /* EABI */
#else
    1; /* ATPCS */
#endif

  if(sig == 0) {
    if(args->reg_count < 4)
      args->reg_count = (args->reg_count+1)&~1;
    if(args->reg_count >= 4 && (int)args->stack_ptr & 4)
      ++args->stack_ptr;
  }
}


static void* arm_word(DCArgs* args)
{
  if(args->reg_count < 4)
    return &args->reg_data[args->reg_count++];
  else
    return (void*)args->stack_ptr++;
}


static DCdouble arm_double(DCArgs* args)
{
  union {
    DCdouble d;
    DClong   l[2];
  } d;
  arm_align_64(args);
  d.l[0] = *(DClong*)arm_word(args);
  d.l[1] = *(DClong*)arm_word(args);
  return d.d;
}


static DClonglong arm_longlong(DCArgs* args)
{
  union {
    DClonglong ll;
    DClong     l[2];
  } ll;
  arm_align_64(args);
  ll.l[0] = *(DClong*)arm_word(args);
  ll.l[1] = *(DClong*)arm_word(args);
  return ll.ll;
}



// ----------------------------------------------------------------------------
// C API implementation:


// base operations:

DClonglong  dcArgs_longlong (DCArgs* p) { return arm_longlong(p); }
DClong      dcArgs_long     (DCArgs* p) { return *(DClong*)arm_word(p); }
DCint       dcArgs_int      (DCArgs* p) { return (DCint)   dcArgs_long(p); }
DCchar      dcArgs_char     (DCArgs* p) { return (DCchar)  dcArgs_long(p); }
DCshort     dcArgs_short    (DCArgs* p) { return (DCshort) dcArgs_long(p); }
DCbool      dcArgs_bool     (DCArgs* p) { return (dcArgs_long(p) == 0) ? 0 : 1; }

DCuint      dcArgs_uint     (DCArgs* p) { return (DCuint)     dcArgs_int(p);      }
DCuchar     dcArgs_uchar    (DCArgs* p) { return (DCuchar)    dcArgs_char(p);     }
DCushort    dcArgs_ushort   (DCArgs* p) { return (DCushort)   dcArgs_short(p);    }
DCulong     dcArgs_ulong    (DCArgs* p) { return (DCulong)    dcArgs_long(p);     }
DCulonglong dcArgs_ulonglong(DCArgs* p) { return (DCulonglong)dcArgs_longlong(p); }


DCpointer   dcArgs_pointer  (DCArgs* p) { return (DCpointer)  dcArgs_long(p); }

DCdouble    dcArgs_double   (DCArgs* p) { return arm_double(p); }
DCfloat     dcArgs_float    (DCArgs* p) { return *(DCfloat*)  arm_word(p); }

