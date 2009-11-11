#include "_auto_config.h"
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
#include "_auto_invokers.h"

#undef A
#undef F0(ID,R)
#undef F1(ID,R,A1)
#undef F2(ID,R,A1,A2)
#undef F3(ID,R,A1,A2,A3)

/* table of invokers */

typedef void (invoker)(void*);

#define F0(ID,R) &ID,
#define F1(ID,R,A1) &ID,
#define F2(ID,R,A1,A2) &ID,
#define F3(ID,R,A1,A2,A3) &ID,

invoker* invokers[CONFIG_NSIGS] = {
#include "_auto_invokers.h"
};

/* front-end */

void DoInvoke(int id, void* addr)
{
  invokers[id](addr);
}

