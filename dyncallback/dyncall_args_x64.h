#ifndef DYNCALLBACK_ARGS_X64_H
#define DYNCALLBACK_ARGS_X64_H

/*
 * dyncall_args_x86.h
 *
 *  Created on: Feb 9, 2009
 *      Author: dadler
 */

#include "dyncall_args.h"

typedef struct
{
	DCint      (*i32)(DCArgs*);
	DClonglong (*i64)(DCArgs*);
	DCfloat    (*f32)(DCArgs*);
	DCdouble   (*f64)(DCArgs*);
} DCArgsVT;

extern DCArgsVT dcArgsVT_sysv;
extern DCArgsVT dcArgsVT_win64;

struct DCArgs
{
	/* callmode */
	// DCArgsVT* vt;

	/* state */
	long long* stack_ptr;
	int ireg_count;
	int freg_count;

	/* reg data */
	long long ireg_data[6];
        double    freg_data[8];
};

#endif /* DYNCALLBACK_ARGS_X64_H */

