/*/////////////////////////////////////////////////////////////////////////////

  dyncall callvm for 32bit ARM9E family of processors
  Copyright 2007 Tassilo Philipp.

  SUPPORTED CALLING CONVENTIONS
  armcall

  REVISION
  2007/12/11 initial

/////////////////////////////////////////////////////////////////////////////*/


#include "dyncall_callvm_arm9e_arm.h"
#include "dyncall_alloc.h"


static DCCallVM* dc_callvm_new_arm9e_arm(DCCallVM_vt* vt, DCsize size)
{
  /* Store at least 16 bytes (4 words) for internal spill area. Assembly code depends on it. */
  DCCallVM_arm9e_arm* self = (DCCallVM_arm9e_arm*)dcAllocMem(sizeof(DCCallVM_arm9e_arm)+size+16);
  self->mInterface.mVTpointer = vt;
  dcVecInit(&self->mVecHead, size);
  return (DCCallVM*)self;
}


static void dc_callvm_free_arm9e_arm(DCCallVM* in_self)
{
  dcFreeMem(in_self);
}


static void dc_callvm_reset_arm9e_arm(DCCallVM* in_self)
{
  DCCallVM_arm9e_arm* self = (DCCallVM_arm9e_arm*)in_self;
  dcVecReset(&self->mVecHead);
}

static void dc_callvm_mode_arm9e_arm(DCCallVM* in_self,DCint mode)
{
  /* do nothing */
}


static void dc_callvm_argInt_arm9e_arm(DCCallVM* in_self, DCint x)
{
  DCCallVM_arm9e_arm* self = (DCCallVM_arm9e_arm*)in_self;
  dcVecAppend(&self->mVecHead, &x, sizeof(DCint));
}


static void dc_callvm_argBool_arm9e_arm(DCCallVM* in_self, DCbool x)
{
  dc_callvm_argInt_arm9e_arm(in_self, (DCint)x);
}


static void dc_callvm_argChar_arm9e_arm(DCCallVM* in_self, DCchar x)
{
  dc_callvm_argInt_arm9e_arm(in_self, x);
}


static void dc_callvm_argShort_arm9e_arm(DCCallVM* in_self, DCshort x)
{
  dc_callvm_argInt_arm9e_arm(in_self, x);
}


static void dc_callvm_argLong_arm9e_arm(DCCallVM* in_self, DClong x)
{
  dc_callvm_argInt_arm9e_arm(in_self, x);
}


static void dc_callvm_argLongLong_arm9e_arm(DCCallVM* in_self, DClonglong x)
{
  DCCallVM_arm9e_arm* self = (DCCallVM_arm9e_arm*)in_self;

  /* 64 bit values need to be aligned on 8 byte boundaries (@@@ perhaps
     this is GCC specific - it is not documented int the ATPCS, though) */
  dcVecSkip(&self->mVecHead, dcVecSize(&self->mVecHead) & 4);
  dcVecAppend(&self->mVecHead, &x, sizeof(DClonglong));

  /* Store as if 'x' were two parameters, with the loword as first parameter. */
  /* dcVecAppend(&self->mVecHead, (DCint*)&x+0, sizeof(DCint)); */
  /* dcVecAppend(&self->mVecHead, (DCint*)&x+1, sizeof(DCint)); */
}


static void dc_callvm_argFloat_arm9e_arm(DCCallVM* in_self, DCfloat x)
{
  DCCallVM_arm9e_arm* self = (DCCallVM_arm9e_arm*)in_self;
  dcVecAppend(&self->mVecHead, &x, sizeof(DCfloat));
}


static void dc_callvm_argDouble_arm9e_arm(DCCallVM* in_self, DCdouble x)
{
  DCCallVM_arm9e_arm* self = (DCCallVM_arm9e_arm*)in_self;

  /* 64 bit values need to be aligned on 8 byte boundaries (@@@ perhaps
     this is GCC specific - it is not documented int the ATPCS, though) */
  dcVecSkip(&self->mVecHead, dcVecSize(&self->mVecHead) & 4);
  dcVecAppend(&self->mVecHead, &x, sizeof(DCdouble));
}


static void dc_callvm_argPointer_arm9e_arm(DCCallVM* in_self, DCpointer x)
{
  DCCallVM_arm9e_arm* self = (DCCallVM_arm9e_arm*)in_self;
  dcVecAppend(&self->mVecHead, &x, sizeof(DCpointer));
}


/* Call. */
void dc_callvm_call_arm9e_arm(DCCallVM* in_self, DCpointer target)
{
  DCCallVM_arm9e_arm* self = (DCCallVM_arm9e_arm*)in_self;
  dcCall_arm9e_arm(target, dcVecData(&self->mVecHead), dcVecSize(&self->mVecHead));
}


DCCallVM_vt gVT_arm9e_arm =
{
  &dc_callvm_free_arm9e_arm
, &dc_callvm_reset_arm9e_arm
, &dc_callvm_mode_arm9e_arm
, &dc_callvm_argBool_arm9e_arm
, &dc_callvm_argChar_arm9e_arm
, &dc_callvm_argShort_arm9e_arm 
, &dc_callvm_argInt_arm9e_arm
, &dc_callvm_argLong_arm9e_arm
, &dc_callvm_argLongLong_arm9e_arm
, &dc_callvm_argFloat_arm9e_arm
, &dc_callvm_argDouble_arm9e_arm
, &dc_callvm_argPointer_arm9e_arm
, (DCvoidvmfunc*)       &dc_callvm_call_arm9e_arm
, (DCboolvmfunc*)       &dc_callvm_call_arm9e_arm
, (DCcharvmfunc*)       &dc_callvm_call_arm9e_arm
, (DCshortvmfunc*)      &dc_callvm_call_arm9e_arm
, (DCintvmfunc*)        &dc_callvm_call_arm9e_arm
, (DClongvmfunc*)       &dc_callvm_call_arm9e_arm
, (DClonglongvmfunc*)   &dc_callvm_call_arm9e_arm
, (DCfloatvmfunc*)      &dc_callvm_call_arm9e_arm
, (DCdoublevmfunc*)     &dc_callvm_call_arm9e_arm
, (DCpointervmfunc*)    &dc_callvm_call_arm9e_arm
};

DCCallVM* dcNewCallVM_arm9e_arm(DCsize size) 
{
  return dc_callvm_new_arm9e_arm(&gVT_arm9e_arm, size);
}

DCCallVM* dcNewCallVM(DCsize size)
{
  return dcNewCallVM_arm9e_arm(size);
}

