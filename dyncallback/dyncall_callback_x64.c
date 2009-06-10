#include "dyncall_callback_x64.h"
#include "dyncall_args_x64.h"

#include "dyncall_alloc_wx.h"
#include "dyncall_signature.h"

extern void dcCallbackThunkEntry();

void dcInitCallback(DCCallback* pcb, const char* signature, DCCallbackHandler* handler, void* userdata)
{
  pcb->handler  = handler;
  pcb->userdata = userdata;
}

DCCallback* dcNewCallback(const char* signature, DCCallbackHandler* handler, void* userdata)
{
  int err;
  DCCallback* pcb;
  err = dcAllocWX( sizeof(DCCallback), (void**) &pcb);
  if (err != 0) return 0;
  dcThunkInit( &pcb->thunk, dcCallbackThunkEntry );
  dcInitCallback(pcb, signature, handler, userdata);
  return pcb;
}

void dcFreeCallback(DCCallback* pcb)
{
  dcFreeWX( pcb , sizeof(DCCallback) );
}

