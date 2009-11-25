/*

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

/*

  dyncall callvm for 32bit ARM32 family of processors

  SUPPORTED CALLING CONVENTIONS
  armcall

  REVISION
  2007/12/11 initial

*/


#include "dyncall_callvm_arm32_arm.h"
#include "dyncall_alloc.h"


static DCCallVM* dc_callvm_new_arm32_arm(DCCallVM_vt* vt, DCsize size)
{
  /* Store at least 16 bytes (4 words) for internal spill area. Assembly code depends on it. */
  DCCallVM_arm32_arm* self = (DCCallVM_arm32_arm*)dcAllocMem(sizeof(DCCallVM_arm32_arm)+size+16);
  self->mInterface.mVTpointer = vt;
  dcVecInit(&self->mVecHead, size);
  return (DCCallVM*)self;
}


static void dc_callvm_free_arm32_arm(DCCallVM* in_self)
{
  dcFreeMem(in_self);
}


static void dc_callvm_reset_arm32_arm(DCCallVM* in_self)
{
  DCCallVM_arm32_arm* self = (DCCallVM_arm32_arm*)in_self;
  dcVecReset(&self->mVecHead);
}

static void dc_callvm_mode_arm32_arm(DCCallVM* in_self,DCint mode)
{
  /* do nothing */
}


static void dc_callvm_argInt_arm32_arm(DCCallVM* in_self, DCint x)
{
  DCCallVM_arm32_arm* self = (DCCallVM_arm32_arm*)in_self;
  dcVecAppend(&self->mVecHead, &x, sizeof(DCint));
}


static void dc_callvm_argBool_arm32_arm(DCCallVM* in_self, DCbool x)
{
  dc_callvm_argInt_arm32_arm(in_self, (DCint)x);
}


static void dc_callvm_argChar_arm32_arm(DCCallVM* in_self, DCchar x)
{
  dc_callvm_argInt_arm32_arm(in_self, x);
}


static void dc_callvm_argShort_arm32_arm(DCCallVM* in_self, DCshort x)
{
  dc_callvm_argInt_arm32_arm(in_self, x);
}


static void dc_callvm_argLong_arm32_arm(DCCallVM* in_self, DClong x)
{
  dc_callvm_argInt_arm32_arm(in_self, x);
}


static void dc_callvm_argLongLong_arm32_arm(DCCallVM* in_self, DClonglong x)
{
  DCCallVM_arm32_arm* self = (DCCallVM_arm32_arm*)in_self;

  /* 64 bit values need to be aligned on 8 byte boundaries (@@@ seems to be 'eabi'
     specific (at least, the NDS needs it) - it is not documented int the ATPCS, though) */
#if defined(DC__C_GNU) && defined(DC__OS_NDS)
  dcVecSkip(&self->mVecHead, dcVecSize(&self->mVecHead) & 4);
#endif
  dcVecAppend(&self->mVecHead, &x, sizeof(DClonglong));

  /* Store as if 'x' were two parameters, with the loword as first parameter. */
  /* dcVecAppend(&self->mVecHead, (DCint*)&x+0, sizeof(DCint)); */
  /* dcVecAppend(&self->mVecHead, (DCint*)&x+1, sizeof(DCint)); */
}


static void dc_callvm_argFloat_arm32_arm(DCCallVM* in_self, DCfloat x)
{
  DCCallVM_arm32_arm* self = (DCCallVM_arm32_arm*)in_self;
  dcVecAppend(&self->mVecHead, &x, sizeof(DCfloat));
}


static void dc_callvm_argDouble_arm32_arm(DCCallVM* in_self, DCdouble x)
{
  DCCallVM_arm32_arm* self = (DCCallVM_arm32_arm*)in_self;

  /* 64 bit values need to be aligned on 8 byte boundaries (@@@ seems to be 'eabi'
     specific (at least, the NDS needs it) - it is not documented int the ATPCS, though) */
#if defined(DC__C_GNU) && defined(DC__OS_NDS)
  dcVecSkip(&self->mVecHead, dcVecSize(&self->mVecHead) & 4);
#endif
  dcVecAppend(&self->mVecHead, &x, sizeof(DCdouble));
}


static void dc_callvm_argPointer_arm32_arm(DCCallVM* in_self, DCpointer x)
{
  DCCallVM_arm32_arm* self = (DCCallVM_arm32_arm*)in_self;
  dcVecAppend(&self->mVecHead, &x, sizeof(DCpointer));
}


/* Call. */
void dc_callvm_call_arm32_arm(DCCallVM* in_self, DCpointer target)
{
  DCCallVM_arm32_arm* self = (DCCallVM_arm32_arm*)in_self;
  dcCall_arm32_arm(target, dcVecData(&self->mVecHead), dcVecSize(&self->mVecHead));
}


DCCallVM_vt gVT_arm32_arm =
{
  &dc_callvm_free_arm32_arm
, &dc_callvm_reset_arm32_arm
, &dc_callvm_mode_arm32_arm
, &dc_callvm_argBool_arm32_arm
, &dc_callvm_argChar_arm32_arm
, &dc_callvm_argShort_arm32_arm 
, &dc_callvm_argInt_arm32_arm
, &dc_callvm_argLong_arm32_arm
, &dc_callvm_argLongLong_arm32_arm
, &dc_callvm_argFloat_arm32_arm
, &dc_callvm_argDouble_arm32_arm
, &dc_callvm_argPointer_arm32_arm
, (DCvoidvmfunc*)       &dc_callvm_call_arm32_arm
, (DCboolvmfunc*)       &dc_callvm_call_arm32_arm
, (DCcharvmfunc*)       &dc_callvm_call_arm32_arm
, (DCshortvmfunc*)      &dc_callvm_call_arm32_arm
, (DCintvmfunc*)        &dc_callvm_call_arm32_arm
, (DClongvmfunc*)       &dc_callvm_call_arm32_arm
, (DClonglongvmfunc*)   &dc_callvm_call_arm32_arm
, (DCfloatvmfunc*)      &dc_callvm_call_arm32_arm
, (DCdoublevmfunc*)     &dc_callvm_call_arm32_arm
, (DCpointervmfunc*)    &dc_callvm_call_arm32_arm
};

DCCallVM* dcNewCallVM_arm32_arm(DCsize size) 
{
  return dc_callvm_new_arm32_arm(&gVT_arm32_arm, size);
}

DCCallVM* dcNewCallVM(DCsize size)
{
  return dcNewCallVM_arm32_arm(size);
}

