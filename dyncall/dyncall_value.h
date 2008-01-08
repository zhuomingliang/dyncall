#ifndef DYNCALL_VALUE_H
#define DYNCALL_VALUE_H

#include "dyncall_types.h"

typedef union DCValue_ DCValue;

union DCValue_
{
  DCbool B;
  DCchar c;
  DCshort s;
  DCint i;
  DClong l;
  DClonglong L;
  DCfloat f;
  DCdouble d;
  DCpointer p;
};


#endif /* DYNCALL_VALUE_H */

