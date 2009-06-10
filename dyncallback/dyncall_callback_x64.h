/*
 * dyncall_callback_x64.h
 *
 *  Created on: Feb 12, 2009
 *      Author: dadler
 */

#ifndef DYNCALL_CALLBACK_X64_H_
#define DYNCALL_CALLBACK_X64_H_

#include "dyncall_callback.h"

#include "dyncall_thunk.h"
#include "dyncall_args_x64.h"

struct DCCallback
{
  DCThunk  	     thunk;	  // offset 0,  size 24
  DCCallbackHandler* handler;	  // offset 24
  void*              userdata;    // offset 32
  // DCArgsVT*	     args_vt;	  // offset 32
  //                              // sizeof 40
};



#endif /* DYNCALL_CALLBACK_X64_H_ */

