/*/////////////////////////////////////////////////////////////////////////////

  dyncall callvm for ppc32 architecture
  Copyright 2007 Daniel Adler.

  SUPPORTED CALLING CONVENTIONS
  ppc32/osx 

  REVISION
  2007/12/11 initial

/////////////////////////////////////////////////////////////////////////////*/

#include "dyncall_callvm_ppc32.h"
#include "dyncall_call_ppc32.h"
#include "dyncall_alloc.h"
#include "dyncall_macros.h"
#include "dyncall_types.h"

#if defined(__APPLE__)
  #define DC__OS_MACOSX
#endif

#if defined(DC__OS_MACOSX)

#else

#error Unsupported ppc32 OS.

#endif

static void dc_callvm_free_ppc32(DCCallVM* in_self)
{
  dcFreeMem(in_self);
}

static void dc_callvm_reset_ppc32(DCCallVM* in_self)
{
  DCCallVM_ppc32* self = (DCCallVM_ppc32*)in_self;
  dcVecReset(&self->mVecHead);
  self->mIntRegs   = 0;
  self->mFloatRegs = 0;
}

static void dc_callvm_mode_ppc32(DCCallVM* in_self,DCint mode)
{
  /* do nothing */
}

/* arg int -- fillup integer register file AND push on stack (for ellipse) */

static void dc_callvm_argInt_ppc32(DCCallVM* in_self, DCint i)
{
  DCCallVM_ppc32* self = (DCCallVM_ppc32*)in_self;
  /* fillup integer register file */
  if (self->mIntRegs < 8)
    self->mRegData.mIntData[self->mIntRegs++] = i;
  /* push onto stack */
  dcVecAppend(&self->mVecHead,&i,sizeof(DCint));
}

static void dc_callvm_argLongLong_ppc32(DCCallVM* in_self, DClonglong L)
{
  DCint* p = (DCint*) &L;
  dc_callvm_argInt_ppc32( in_self, p[0] ); 
  dc_callvm_argInt_ppc32( in_self, p[1] ); 
}


static void dc_callvm_argBool_ppc32(DCCallVM* in_self, DCbool x)
{
  /* promote to integer */
  dc_callvm_argInt_ppc32( in_self, (x == 0) ? DC_FALSE : DC_TRUE );
}


static void dc_callvm_argChar_ppc32(DCCallVM* in_self, DCchar ch)
{
  /* promote to integer */
  dc_callvm_argInt_ppc32(in_self, (DCint) ch);
}


static void dc_callvm_argShort_ppc32(DCCallVM* in_self, DCshort s)
{
  /* promote to integer */
  dc_callvm_argInt_ppc32(in_self, (DCint) s);
}


static void dc_callvm_argLong_ppc32(DCCallVM* in_self, DClong l)
{
  /* promote to integer */
  dc_callvm_argInt_ppc32(in_self, (DCint) l);
}

static void dc_callvm_argFloat_ppc32(DCCallVM* in_self, DCfloat f)
{
  DCCallVM_ppc32* self = (DCCallVM_ppc32*)in_self;
  if (self->mFloatRegs < 13) {
    self->mRegData.mFloatData[self->mFloatRegs++] = (DCdouble) (f);
  }
  /* skip one integer register file entry (write in - for ellipse calls) */
  if (self->mIntRegs < 8) 
    self->mRegData.mIntData[self->mIntRegs++] = *( (DCint*) &f );
  /* push on stack */
  dcVecAppend(&self->mVecHead, &f, sizeof(DCfloat));
}


static void dc_callvm_argDouble_ppc32(DCCallVM* in_self, DCdouble d)
{
  DCCallVM_ppc32* self = (DCCallVM_ppc32*)in_self;
  if (self->mFloatRegs < 13) {
    self->mRegData.mFloatData[self->mFloatRegs++] = d;
    /* skip two integer register file entries */
    if (self->mIntRegs < 8) 
      self->mRegData.mIntData[self->mIntRegs++] = ( (DCint*) &d )[0];
    if (self->mIntRegs < 8) 
      self->mRegData.mIntData[self->mIntRegs++] = ( (DCint*) &d )[1];
  }
  /* push on stack */
  dcVecAppend(&self->mVecHead, &d, sizeof(DCdouble));
}

static void dc_callvm_argPointer_ppc32(DCCallVM* in_self, DCpointer p)
{
  /* promote to integer */
  dc_callvm_argInt_ppc32(in_self, (DCint) p);
}

#ifndef max
#define max(a,b) (a>=b)?a:b
#endif

/* Call. */
void dc_callvm_call_ppc32(DCCallVM* in_self, DCpointer target)
{
  DCCallVM_ppc32* self = (DCCallVM_ppc32*)in_self;
  dcCall_ppc32(
    target
   ,&self->mRegData
   ,max( dcVecSize(&self->mVecHead) , 8*4 )
   ,dcVecData(&self->mVecHead)
  );
}


DCCallVM_vt gVT_ppc32 =
{
  &dc_callvm_free_ppc32
, &dc_callvm_reset_ppc32
, &dc_callvm_mode_ppc32
, &dc_callvm_argBool_ppc32
, &dc_callvm_argChar_ppc32
, &dc_callvm_argShort_ppc32 
, &dc_callvm_argInt_ppc32
, &dc_callvm_argLong_ppc32
, &dc_callvm_argLongLong_ppc32
, &dc_callvm_argFloat_ppc32
, &dc_callvm_argDouble_ppc32
, &dc_callvm_argPointer_ppc32
, (DCvoidvmfunc*)       &dc_callvm_call_ppc32
, (DCboolvmfunc*)       &dc_callvm_call_ppc32
, (DCcharvmfunc*)       &dc_callvm_call_ppc32
, (DCshortvmfunc*)      &dc_callvm_call_ppc32
, (DCintvmfunc*)        &dc_callvm_call_ppc32
, (DClongvmfunc*)       &dc_callvm_call_ppc32
, (DClonglongvmfunc*)   &dc_callvm_call_ppc32
, (DCfloatvmfunc*)      &dc_callvm_call_ppc32
, (DCdoublevmfunc*)     &dc_callvm_call_ppc32
, (DCpointervmfunc*)    &dc_callvm_call_ppc32
};


DCCallVM* dcNewCallVM_ppc32(DCsize size) 
{
  DCCallVM_ppc32* self = (DCCallVM_ppc32*)dcAllocMem(sizeof(DCCallVM_ppc32)+size);
  self->mInterface.mVTpointer = &gVT_ppc32;
  self->mIntRegs              = 0;
  self->mFloatRegs            = 0;
  dcVecInit(&self->mVecHead, size);
  return (DCCallVM*)self;
}

DCCallVM* dcNewCallVM(DCsize size)
{
  return dcNewCallVM_ppc32(size);
}

