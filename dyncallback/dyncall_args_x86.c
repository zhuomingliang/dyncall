/*
 Package: dyncall
 Library: dyncallback
 File: dyncallback/dyncall_args_x86.c
 Description: Callback's Arguments VM - Implementation for x86
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
#include "dyncall_args_x86.h"

// ----------------------------------------------------------------------------
// C API implementation:

// base operations:

DCint      dcArgs_int     (DCArgs* p) { return p->vt->i32(p); }
DClonglong dcArgs_longlong(DCArgs* p) { return p->vt->i64(p); }
DCfloat    dcArgs_float   (DCArgs* p) { return p->vt->f32(p); }
DCdouble   dcArgs_double  (DCArgs* p) { return p->vt->f64(p); }

// promote to integer: bool, char, short, long and pointer

DCbool     dcArgs_bool    (DCArgs* p) { return ( dcArgs_int(p) == 0 ) ? 0 : 1; }
DCchar     dcArgs_char    (DCArgs* p) { return (char)  dcArgs_int(p); }
DCshort    dcArgs_short   (DCArgs* p) { return (short) dcArgs_int(p); }
DClong     dcArgs_long    (DCArgs* p) { return (long)  dcArgs_int(p); }
DCpointer  dcArgs_pointer (DCArgs* p) { return (DCpointer) dcArgs_int(p); }

// unsigned types

DCuint      dcArgs_uint     (DCArgs* p) { return (DCuint)   dcArgs_int(p); }
DCuchar     dcArgs_uchar    (DCArgs* p) { return (DCuchar)  dcArgs_char(p); }
DCushort    dcArgs_ushort   (DCArgs* p) { return (DCushort) dcArgs_short(p); }
DCulong     dcArgs_ulong    (DCArgs* p) { return (DCulong)  dcArgs_long(p); }
DCulonglong dcArgs_ulonglong(DCArgs* p) { return (DCulonglong) dcArgs_longlong(p); }

// ----------------------------------------------------------------------------
// virtual tables:

// cdecl calling convention
#define inline

inline int default_i32(DCArgs* args)
{
	return *args->stack_ptr++;
}

inline long long default_i64(DCArgs* args)
{
	long long result = * (long long*) args->stack_ptr;
	args->stack_ptr += 2;
	return result;
}

inline float default_f32(DCArgs* args)
{
	float result = * ( (float*) args->stack_ptr );
	args->stack_ptr++;
	return result;
}

inline double default_f64(DCArgs* args)
{
	double result = * ( (double*) args->stack_ptr );
	args->stack_ptr += 2;
	return  result;
}

DCArgsVT dcArgsVT_default   = { default_i32, default_i64, default_f32, default_f64 };

// fastcall (microsoft) calling convention:

inline int fast_i32(DCArgs* args)
{
	if (args->fast_count < 2)
		return args->fast_data[args->fast_count++];
	else
		return default_i32(args);
}

DCArgsVT dcArgsVT_fast_ms = { fast_i32, default_i64, default_f32, default_f64 };

// fastcall (gnu) calling convention

inline long long fast_gnu_i64(DCArgs* args)
{
	args->fast_count = 2;
	return default_i64(args);
}

DCArgsVT dcArgsVT_fast_gnu = { fast_i32, fast_gnu_i64, default_f32, default_f64 };
