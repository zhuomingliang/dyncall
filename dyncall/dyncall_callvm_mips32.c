/*/////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////*/

/*/////////////////////////////////////////////////////////////////////////////

  dyncall callvm for 32bit MIPS family of processors

  SUPPORTED CALLING CONVENTIONS
  eabi

  REVISION
  2007/12/11 initial

/////////////////////////////////////////////////////////////////////////////*/


#include "dyncall_callvm_mips32.h"
#include "dyncall_alloc.h"



static void dc_callvm_reset_mips32(DCCallVM* in_self)
{
  DCCallVM_mips32* self = (DCCallVM_mips32*)in_self;
  dcVecReset(&self->mVecHead);
  self->mIntRegs = 0;
  self->mSingleRegs = 0;
}

static DCCallVM* dc_callvm_new_mips32(DCCallVM_vt* vt, DCsize size)
{
  /* Store at least 16 bytes (4 words) for internal spill area. Assembly code depends on it. */
  DCCallVM_mips32* self = (DCCallVM_mips32*)dcAllocMem(sizeof(DCCallVM_mips32)+size+16);
  self->mInterface.mVTpointer = vt;
  dcVecInit(&self->mVecHead, size);
  dc_callvm_reset_mips32( (DCCallVM*) self );
  return (DCCallVM*)self;
}


static void dc_callvm_free_mips32(DCCallVM* in_self)
{
  dcFreeMem(in_self);
}

static void dc_callvm_mode_mips32(DCCallVM* in_self,DCint mode)
{
  /* do nothing */
}

/* arg int -- fillup integer register file OR push on stack */

static void dc_callvm_argInt_mips32(DCCallVM* in_self, DCint i)
{
  DCCallVM_mips32* self = (DCCallVM_mips32*)in_self;
  /* fillup integer register file */
  if (self->mIntRegs < 8)
    self->mRegData.mIntData[self->mIntRegs++] = i;
  else
    dcVecAppend(&self->mVecHead, &i, sizeof(DCint));
}

static void dc_callvm_argPointer_mips32(DCCallVM* in_self, DCpointer x)
{
  dc_callvm_argInt_mips32(in_self, * (DCint*) &x );
}

static void dc_callvm_argBool_mips32(DCCallVM* in_self, DCbool x)
{
  dc_callvm_argInt_mips32(in_self, (DCint)x);
}

static void dc_callvm_argChar_mips32(DCCallVM* in_self, DCchar x)
{
  dc_callvm_argInt_mips32(in_self, (DCint)x);
}

static void dc_callvm_argShort_mips32(DCCallVM* in_self, DCshort x)
{
  dc_callvm_argInt_mips32(in_self, (DCint)x);
}

static void dc_callvm_argLong_mips32(DCCallVM* in_self, DClong x)
{
  dc_callvm_argInt_mips32(in_self, (DCint)x);
}

static void dc_callvm_argLongLong_mips32(DCCallVM* in_self, DClonglong Lv)
{
  DCCallVM_mips32* self = (DCCallVM_mips32*)in_self;

  if (self->mIntRegs < 7) {
    DCint* p = (DCint*) &Lv;
    /* skip odd register (align 64 bit) */
    self->mIntRegs += self->mIntRegs & 1;
    self->mRegData.mIntData[self->mIntRegs++] = p[0];
    self->mRegData.mIntData[self->mIntRegs++] = p[1];
  } else {
    self->mIntRegs = 8;
    /* 64 bit values need to be aligned on 8 byte boundaries */
    dcVecSkip(&self->mVecHead, dcVecSize(&self->mVecHead) & 4);
    dcVecAppend(&self->mVecHead, &Lv, sizeof(DClonglong));
  }
}

static void dc_callvm_argFloat_mips32(DCCallVM* in_self, DCfloat x)
{
  DCCallVM_mips32* self = (DCCallVM_mips32*)in_self;
  if (self->mSingleRegs < 8) {
    self->mRegData.mSingleData[self->mSingleRegs++] = x;
  } else {
    dcVecAppend(&self->mVecHead, &x, sizeof(DCfloat) );
  }
}

static void dc_callvm_argDouble_mips32(DCCallVM* in_self, DCdouble x)
{
  DClonglong* p = (DClonglong*) &x;
  dc_callvm_argLongLong_mips32(in_self, *p);
}

/* Call. */
void dc_callvm_call_mips32(DCCallVM* in_self, DCpointer target)
{
  DCCallVM_mips32* self = (DCCallVM_mips32*)in_self;
  dcCall_mips32(target, &self->mRegData, dcVecSize(&self->mVecHead), dcVecData(&self->mVecHead));
}

DCCallVM_vt gVT_mips32 =
{
  &dc_callvm_free_mips32
, &dc_callvm_reset_mips32
, &dc_callvm_mode_mips32
, &dc_callvm_argBool_mips32
, &dc_callvm_argChar_mips32
, &dc_callvm_argShort_mips32 
, &dc_callvm_argInt_mips32
, &dc_callvm_argLong_mips32
, &dc_callvm_argLongLong_mips32
, &dc_callvm_argFloat_mips32
, &dc_callvm_argDouble_mips32
, &dc_callvm_argPointer_mips32
, (DCvoidvmfunc*)       &dc_callvm_call_mips32
, (DCboolvmfunc*)       &dc_callvm_call_mips32
, (DCcharvmfunc*)       &dc_callvm_call_mips32
, (DCshortvmfunc*)      &dc_callvm_call_mips32
, (DCintvmfunc*)        &dc_callvm_call_mips32
, (DClongvmfunc*)       &dc_callvm_call_mips32
, (DClonglongvmfunc*)   &dc_callvm_call_mips32
, (DCfloatvmfunc*)      &dc_callvm_call_mips32
, (DCdoublevmfunc*)     &dc_callvm_call_mips32
, (DCpointervmfunc*)    &dc_callvm_call_mips32
};

DCCallVM* dcNewCallVM_mips32(DCsize size) 
{
  return dc_callvm_new_mips32(&gVT_mips32, size);
}

DCCallVM* dcNewCallVM(DCsize size)
{
  return dcNewCallVM_mips32(size);
}

