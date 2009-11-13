#include "_auto_config.h"
#include <assert.h>
#include "invokers.h"
#include "env.h"

/* auto-generated invokers code */

/* type short-cuts */

typedef DCvoid      v;

typedef DCbool      B;

typedef DCchar      c;
typedef DCshort     s;
typedef DCint       i;
typedef DClong      j;
typedef DClonglong  l;

typedef DCuchar     C;
typedef DCushort    S;
typedef DCuint      I;
typedef DCulong     J;
typedef DCulonglong L;

typedef DCfloat     f;
typedef DCdouble    d;

typedef DCpointer   p;

typedef DCstring    Z;

#define A ValueMatrix

#define F0(ID,R)          void ID(void* addr) { Result.R = ((R(*)())addr)\
  (); }
#define F1(ID,R,A0)       void ID(void* addr) { Result.R = ((R(*)(A0))addr)\
  (A[0].A0); }
#define F2(ID,R,A0,A1)    void ID(void* addr) { Result.R = ((R(*)(A0,A1))addr)\
  (A[0].A0 , A[1].A1 ); }
#define F3(ID,R,A0,A1,A2) void ID(void* addr) { Result.R = ((R(*)(A0,A1,A2))addr)\
  (A[0].A0 , A[1].A1 , A[2].A2); }
#define F4(ID,R,A0,A1,A2,A3) void ID(void* addr) { Result.R = ((R(*)(A0,A1,A2,A3))addr)\
  (A[0].A0 , A[1].A1 , A[2].A2, A[3].A3); }
#define F5(ID,R,A0,A1,A2,A3,A4) void ID(void* addr) { Result.R = ((R(*)(A0,A1,A2,A3,A4))addr)\
  (A[0].A0 , A[1].A1 , A[2].A2, A[3].A3, A[4].A4); }
#define F6(ID,R,A0,A1,A2,A3,A4,A5) void ID(void* addr) { Result.R = ((R(*)(A0,A1,A2,A3,A4,A5))addr)\
  (A[0].A0 , A[1].A1 , A[2].A2, A[3].A3, A[4].A4, A[5].A5); }
#define F7(ID,R,A0,A1,A2,A3,A4,A5,A6) void ID(void* addr) { Result.R = ((R(*)(A0,A1,A2,A3,A4,A5,A6))addr)\
  (A[0].A0 , A[1].A1 , A[2].A2, A[3].A3, A[4].A4, A[5].A5, A[6].A6); }
#define F8(ID,R,A0,A1,A2,A3,A4,A5,A6,A7) void ID(void* addr) { Result.R = ((R(*)(A0,A1,A2,A3,A4,A5,A6,A7))addr)\
  (A[0].A0 , A[1].A1 , A[2].A2, A[3].A3, A[4].A4, A[5].A5, A[6].A6, A[7].A7); }
#define F9(ID,R,A0,A1,A2,A3,A4,A5,A6,A7,A8) void ID(void* addr) { Result.R = ((R(*)(A0,A1,A2,A3,A4,A5,A6,A7,A8))addr)\
  (A[0].A0 , A[1].A1 , A[2].A2, A[3].A3, A[4].A4, A[5].A5, A[6].A6, A[7].A7, A[8].A8); }
#define F10(ID,R,A0,A1,A2,A3,A4,A5,A6,A7,A8,A9) void ID(void* addr) { Result.R = ((R(*)(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9))addr)\
  (A[0].A0 , A[1].A1 , A[2].A2, A[3].A3, A[4].A4, A[5].A5, A[6].A6, A[7].A7, A[8].A8, A[9].A9); }

// #include "_auto_invokers.h"

#undef A
#undef F0
#undef F1
#undef F2
#undef F3
#undef F4
#undef F5
#undef F6
#undef F7
#undef F8
#undef F9
#undef F10

#define A ValueMatrix
#include "_auto_invoke_macros.h"
#include "_auto_invokers.h"
/* table of invokers */


/*
#define F0(ID,R) &ID,
#define F1(ID,R,A1) &ID,
#define F2(ID,R,A1,A2) &ID,
#define F3(ID,R,A1,A2,A3) &ID,
#define F4(ID,R,A0,A1,A2,A3) &ID,
#define F5(ID,R,A0,A1,A2,A3,A4) &ID, 
#define F6(ID,R,A0,A1,A2,A3,A4,A5) &ID, 
#define F7(ID,R,A0,A1,A2,A3,A4,A5,A6) &ID, 
#define F8(ID,R,A0,A1,A2,A3,A4,A5,A6,A7) &ID,
#define F9(ID,R,A0,A1,A2,A3,A4,A5,A6,A7,A8) &ID, 
#define F10(ID,R,A0,A1,A2,A3,A4,A5,A6,A7,A8,A9) &ID, 
*/

typedef void (invoker)(void*);

invoker* invokers[CONFIG_NSIGS] = {
// #include "_auto_invokers.h"
#include "_auto_invoke_table.h"
};

/* front-end */

void DoInvoke(int index, void* addr)
{
  invokers[index](addr);
}

