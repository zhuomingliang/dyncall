#include "_auto_config.h"
#include <assert.h>
#include "invokers.h"
#include "env.h"

/* Callback Invokers implementation. */

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
#include "_auto_invoke_macros.h"
#include "_auto_invokers.h"

/* table of invokers */

typedef void (invoker) (void*);

invoker* invokers[CONFIG_NSIGS] = {
#include "_auto_invoke_table.h"
};


/* Front-End. */

void DoInvoke(int index, void* addr)
{
  invokers[index](addr);
}

