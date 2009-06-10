#ifndef DYNCALL_CALLBACK_H
#define DYNCALL_CALLBACK_H

#include "dyncall_signature.h"

#include "dyncall_args.h"
#include "dyncall_value.h"

typedef struct DCCallback DCCallback;

typedef char (DCCallbackHandler)( DCCallback* pcb, DCArgs* args, DCValue* result, void* userdata );

DCCallback* dcNewCallback(const char* signature, DCCallbackHandler* funcptr, void* userdata);
void        dcInitCallback(DCCallback* pcb, const char* signature, DCCallbackHandler* handler, void* userdata);
void        dcFreeCallback(DCCallback*);

#endif // DYNCALL_CALLBACK_H
