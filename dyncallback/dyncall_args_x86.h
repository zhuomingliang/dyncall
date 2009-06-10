/*
 * dyncall_args_x86.h
 *
 *  Created on: Feb 9, 2009
 *      Author: dadler
 */

#ifndef DYNCALL_ARGS_X86_H_
#define DYNCALL_ARGS_X86_H_

#include "dyncall_args.h"

typedef struct
{
	DCint      (*i32)(DCArgs*);
	DClonglong (*i64)(DCArgs*);
	DCfloat    (*f32)(DCArgs*);
	DCdouble   (*f64)(DCArgs*);
} DCArgsVT;

extern DCArgsVT dcArgsVT_default;
extern DCArgsVT dcArgsVT_fast_ms;
extern DCArgsVT dcArgsVT_fast_gnu;

struct DCArgs
{
	/* callmode */
	DCArgsVT* vt;

	/* state */
	int* stack_ptr;

	/* fast data */
	int  fast_data[2];
	int  fast_count;
};

#endif /* DYNCALL_ARGS_X86_H_ */
