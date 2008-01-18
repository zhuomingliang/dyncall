#ifndef DC_TEST_FUNCINFO_H
#define DC_TEST_FUNCINFO_H

#include "../../dyncall/dyncall_signature.h"

struct funcinfo
{
  DCpointer        funcptr;
  const DCsigchar* sig;
};

extern funcinfo gFuncInfos[];

#endif /* DC_TEST_FUNCINFO_H */



