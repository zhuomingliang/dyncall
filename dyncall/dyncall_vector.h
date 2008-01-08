#ifndef DC_VEC_HEAD_H
#define DC_VEC_HEAD_H

#include "dyncall_types.h"

typedef struct DCVecHead_ DCVecHead;

struct DCVecHead_
{
  DCsize mTotal;
  DCsize mSize;
};

#define DC_SIZEOF_DCVector(size) (sizeof(DCVecHead)+size)

#define dcVecInit(p,size)   (p)->mTotal=size;(p)->mSize=0
#define dcVecReset(p)       (p)->mSize=0
#define dcVecResize(p,size) (p)->mSize=(size)
#define dcVecSkip(p,size)   (p)->mSize+=(size)
#define dcVecData(p)        ( (unsigned char*) (((DCVecHead*)(p))+1) )
#define dcVecAt(p,index)    ( dcVecData(p)+index )
#define dcVecSize(p)        ( (p)->mSize )

/*
#include <string.h>
 #define dcVecAppend(p,s,n) memcpy( dcVecData(p)+p->mSize, s, n );mSize+=n
*/

void dcVecAppend(DCVecHead* pHead, const void* source, size_t length);

#endif /* DC_VEC_HEAD_H */

