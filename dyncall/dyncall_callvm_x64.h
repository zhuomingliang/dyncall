/*/////////////////////////////////////////////////////////////////////////////

  dyncall callvm for x64 architecture
  Copyright 2007 Tassilo Philipp.

  SUPPORTED CALLING CONVENTIONS
  MS Windows x64 calling convention, AMD64 SystemV ABI 

  REVISION
  2007/12/11 initial

/////////////////////////////////////////////////////////////////////////////*/


#ifndef DYNCALL_CALLVM_X64_H
#define DYNCALL_CALLVM_X64_H

#include "dyncall_macros.h"
#include "dyncall_call_x64.h"
#include "dyncall_callvm.h"
#include "dyncall_vector.h"


#if defined(DC_WINDOWS)

typedef long long int64;	// llp64

#define numIntRegs   4
#define numFloatRegs 4 

typedef union
{
  int i;
  int f;
} DCRegCount_x64;

typedef union
{
  int64  i[numIntRegs  ];
  double f[numFloatRegs];
} DCRegData_x64;

#elif defined(DC_UNIX)

typedef long int64;		// lp64

#define numIntRegs   6
#define numFloatRegs 8

typedef struct
{
  int i;
  int f;
} DCRegCount_x64;

typedef struct
{
  int64  i[numIntRegs  ];
  double f[numFloatRegs];
} DCRegData_x64;

#else

#error Unsupported OS.

#endif


typedef struct
{
  DCCallVM       mInterface;  /* This CallVM interface.                                  */
  DCpointer      mpCallFunc;  /* Function to call.                                       */
  DCRegCount_x64 mRegCount;   /* Number of int/sse registers used for parameter passing. */
  DCRegData_x64  mRegData;    /* Parameters to be passed via registers.                  */
  DCVecHead      mVecHead;    /* Parameters to be pushed onto stack.                     */
} DCCallVM_x64;

DCCallVM* dcNewCallVM_x64(DCsize size);


#endif /* DYNCALL_CALLVM_X64_H */

