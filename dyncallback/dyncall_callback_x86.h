/*
 * dyncall_callback_x86.h
 *
 *  Created on: Feb 9, 2009
 *      Author: dadler
 */

#ifndef DYNCALL_CALLBACK_X86_H_
#define DYNCALL_CALLBACK_X86_H_

#include "dyncall_callback.h"

#include "dyncall_thunk.h"
#include "dyncall_args_x86.h"

struct DCCallback
{
	DCThunk  			      thunk;			    // offset 0,  size 16
	DCCallbackHandler*	handler;		    // offset 16
	DCArgsVT*		 	      args_vt;		    // offset 20
	size_t   			      stack_cleanup;	// offset 24
	void*               userdata;		    // offset 28
};

int dcCleanupSize_x86_cdecl   (const char* args_signature);
int dcCleanupSize_x86_std     (const char* args_signature);
int dcCleanupSize_x86_fast_ms (const char* args_signature);
int dcCleanupSize_x86_fast_gnu(const char* args_signature);

#endif /* DYNCALL_CALLBACK_X86_H_ */
