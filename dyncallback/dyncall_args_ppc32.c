/*
 Package: dyncall
 Library: dyncallback
 File: dyncallback/dyncall_args_ppc32.c
 Description: Callback's Arguments VM - Implementation for ppc32
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
#include "dyncall_args_ppc32.h"

DClonglong  dcArgs_longlong (DCArgs* p) { return 0; }
DCulonglong dcArgs_ulonglong(DCArgs* p) { return (DCulonglong)dcArgs_longlong(p); }

DCint       dcArgs_int      (DCArgs* p) 
{
  DCint value;
  if (p->ireg_count < 8)
    value = p->ireg_data[p->ireg_count++];
  else
    value = *( (int*) p->stackptr );
  p->stackptr += sizeof(int);
  return value;
}
DCuint      dcArgs_uint     (DCArgs* p) { return (DCuint)  dcArgs_int(p);  }
DClong      dcArgs_long     (DCArgs* p) { return (DClong)  dcArgs_uint(p); }
DCulong     dcArgs_ulong    (DCArgs* p) { return (DCulong) dcArgs_uint(p); }
DCchar      dcArgs_char     (DCArgs* p) { return (DCchar)  dcArgs_uint(p); }
DCuchar     dcArgs_uchar    (DCArgs* p) { return (DCuchar) dcArgs_uint(p); }
DCshort     dcArgs_short    (DCArgs* p) { return (DCshort) dcArgs_uint(p); }
DCushort    dcArgs_ushort   (DCArgs* p) { return (DCushort)dcArgs_uint(p); }
DCbool      dcArgs_bool     (DCArgs* p) { return (DCbool)  dcArgs_uint(p); }

DCpointer   dcArgs_pointer  (DCArgs* p) { return (DCpointer)dcArgs_uint(p); }

DCdouble    dcArgs_double   (DCArgs* p) 
{ 
  DCdouble result;
  if (p->ireg_count < 7) { 
    p->ireg_count+=2;
  } else if (p->ireg_count == 7) {
    p->ireg_count = 8;
  }
  if (p->freg_count < 13) {
    result = p->freg_data[p->freg_count++];
  } else {
    result = * ( (double*) p->stackptr );
  }
  p->stackptr += sizeof(double);
  return result;
}
DCfloat     dcArgs_float    (DCArgs* p)
{ 
  DCfloat result;
  if (p->ireg_count < 8)
    p->ireg_count++;
  if (p->freg_count < 13) {
    result = (DCfloat) p->freg_data[p->freg_count++];
  } else {
    result = * ( (float*) p->stackptr );
  }
  p->stackptr += sizeof(float);
  return result; 
}

