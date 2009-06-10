#ifndef DYNCALL_ALLOC_WX_HPP
#define DYNCALL_ALLOC_WX_HPP

#include "dyncall_types.h"

typedef int DCerror;

DCerror dcAllocWX(DCsize size, void** p);
void    dcFreeWX (void* p, DCsize size);

#endif // DYNCALL_ALLOC_WX_HPP

