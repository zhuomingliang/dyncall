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

  dyncall callvm for 32bit ARM9E family of processors

  SUPPORTED CALLING CONVENTIONS
  armthumbcall

  REVISION
  2007/12/11 initial

*/


#include "dyncall_callvm_arm9e_thumb.h"
#include "dyncall_alloc.h"


static DCCallVM* dc_callvm_new_arm9e_thumb(DCCallVM_vt* vt, DCsize size)
{
  /* Store at least 16 bytes (4 words) for internal spill area. Assembly code depends on it. */
  DCCallVM_arm9e_thumb* self = (DCCallVM_arm9e_thumb*)dcAllocMem(sizeof(DCCallVM_arm9e_thumb)+size+16);
  self->mInterface.mVTpointer = vt;
  dcVecInit(&self->mVecHead, size);
  return (DCCallVM*)self;
}


static void dc_callvm_free_arm9e_thumb(DCCallVM* in_self)
{
  dcFreeMem(in_self);
}


static void dc_callvm_reset_arm9e_thumb(DCCallVM* in_self)
{
  DCCallVM_arm9e_thumb* self = (DCCallVM_arm9e_thumb*)in_self;
  dcVecReset(&self->mVecHead);
}

static void dc_callvm_mode_arm9e_thumb(DCCallVM* in_self,DCint mode)
{
  /* do nothing */
}


static void dc_callvm_argInt_arm9e_thumb(DCCallVM* in_self, DCint x)
{
  DCCallVM_arm9e_thumb* self = (DCCallVM_arm9e_thumb*)in_self;
  dcVecAppend(&self->mVecHead, &x, sizeof(DCint));
}


static void dc_callvm_argBool_arm9e_thumb(DCCallVM* in_self, DCbool x)
{
  dc_callvm_argInt_arm9e_thumb(in_self, (DCint)x);
}


static void dc_callvm_argChar_arm9e_thumb(DCCallVM* in_self, DCchar x)
{
  dc_callvm_argInt_arm9e_thumb(in_self, x);
}


static void dc_callvm_argShort_arm9e_thumb(DCCallVM* in_self, DCshort x)
{
  dc_callvm_argInt_arm9e_thumb(in_self, x);
}


static void dc_callvm_argLong_arm9e_thumb(DCCallVM* in_self, DClong x)
{
  dc_callvm_argInt_arm9e_thumb(in_self, x);
}


static void dc_callvm_argLongLong_arm9e_thumb(DCCallVM* in_self, DClonglong x)
{
  DCCallVM_arm9e_thumb* self = (DCCallVM_arm9e_thumb*)in_self;

  /* 64 bit values need to be aligned on 8 byte boundaries (@@@ perhaps
     this is GCC specific - it is not documented int the ATPCS, though) */
  dcVecSkip(&self->mVecHead, dcVecSize(&self->mVecHead) & 4);
  dcVecAppend(&self->mVecHead, &x, sizeof(DClonglong));
}


static void dc_callvm_argFloat_arm9e_thumb(DCCallVM* in_self, DCfloat x)
{
  DCCallVM_arm9e_thumb* self = (DCCallVM_arm9e_thumb*)in_self;
  dcVecAppend(&self->mVecHead, &x, sizeof(DCfloat));
}


static void dc_callvm_argDouble_arm9e_thumb(DCCallVM* in_self, DCdouble x)
{
  DCCallVM_arm9e_thumb* self = (DCCallVM_arm9e_thumb*)in_self;

  /* 64 bit values need to be aligned on 8 byte boundaries (@@@ perhaps
     this is GCC specific - it is not documented int the ATPCS, though) */
  dcVecSkip(&self->mVecHead, dcVecSize(&self->mVecHead) & 4);
  dcVecAppend(&self->mVecHead, &x, sizeof(DCdouble));
}


static void dc_callvm_argPointer_arm9e_thumb(DCCallVM* in_self, DCpointer x)
{
  DCCallVM_arm9e_thumb* self = (DCCallVM_arm9e_thumb*)in_self;
  dcVecAppend(&self->mVecHead, &x, sizeof(DCpointer));
}


/* Call. */
void dc_callvm_call_arm9e_thumb(DCCallVM* in_self, DCpointer target)
{
  DCCallVM_arm9e_thumb* self = (DCCallVM_arm9e_thumb*)in_self;
  dcCall_arm9e_thumb(target, dcVecData(&self->mVecHead), dcVecSize(&self->mVecHead));
}


DClong dc_callvm_call_arm9e_thumb_word(DCCallVM* in_self, DCpointer target)
{
  DCCallVM_arm9e_thumb* self = (DCCallVM_arm9e_thumb*)in_self;
  return dcCall_arm9e_thumb_word(target, dcVecData(&self->mVecHead), dcVecSize(&self->mVecHead));
}


DClonglong dc_callvm_call_arm9e_thumb_dword(DCCallVM* in_self, DCpointer target)
{
  DCCallVM_arm9e_thumb* self = (DCCallVM_arm9e_thumb*)in_self;
  return dcCall_arm9e_thumb_dword(target, dcVecData(&self->mVecHead), dcVecSize(&self->mVecHead));
}



DCCallVM_vt gVT_arm9e_thumb =
{
  &dc_callvm_free_arm9e_thumb
, &dc_callvm_reset_arm9e_thumb
, &dc_callvm_mode_arm9e_thumb
, &dc_callvm_argBool_arm9e_thumb
, &dc_callvm_argChar_arm9e_thumb
, &dc_callvm_argShort_arm9e_thumb 
, &dc_callvm_argInt_arm9e_thumb
, &dc_callvm_argLong_arm9e_thumb
, &dc_callvm_argLongLong_arm9e_thumb
, &dc_callvm_argFloat_arm9e_thumb
, &dc_callvm_argDouble_arm9e_thumb
, &dc_callvm_argPointer_arm9e_thumb
, (DCvoidvmfunc*)       &dc_callvm_call_arm9e_thumb
, (DCboolvmfunc*)       &dc_callvm_call_arm9e_thumb_word
, (DCcharvmfunc*)       &dc_callvm_call_arm9e_thumb_word
, (DCshortvmfunc*)      &dc_callvm_call_arm9e_thumb_word
, (DCintvmfunc*)        &dc_callvm_call_arm9e_thumb_word
, (DClongvmfunc*)       &dc_callvm_call_arm9e_thumb_word
, (DClonglongvmfunc*)   &dc_callvm_call_arm9e_thumb_dword
, (DCfloatvmfunc*)      &dc_callvm_call_arm9e_thumb_word
, (DCdoublevmfunc*)     &dc_callvm_call_arm9e_thumb_dword
, (DCpointervmfunc*)    &dc_callvm_call_arm9e_thumb_word
};

DCCallVM* dcNewCallVM_arm9e_thumb(DCsize size) 
{
  return dc_callvm_new_arm9e_thumb(&gVT_arm9e_thumb, size);
}

DCCallVM* dcNewCallVM(DCsize size)
{
  return dcNewCallVM_arm9e_thumb(size);
}

