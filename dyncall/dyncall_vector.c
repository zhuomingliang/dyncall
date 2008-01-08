#include "dyncall_vector.h"
#include <string.h>

void dcVecAppend(DCVecHead* pHead, const void* pData, size_t size)
{
  if (pHead->mSize+size <= pHead->mTotal) 
  {
    void* dst = (char*)dcVecData(pHead) + pHead->mSize;
    memcpy(dst, pData, size); /* @@@ heavy for small types. */
    pHead->mSize += size;
  } 
}

