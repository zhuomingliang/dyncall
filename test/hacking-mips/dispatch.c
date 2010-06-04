#include "common.h"
int dispatch(fp funptr, int a0, int a1, int a2, int a3, int a4, int a5)
{
  return funptr(a0,a1,a2,a3,a4,a5);
/*
  int result1 = funptr(a0,a1,a2,a3,a4,a5);
  return result1 + a0 + a1 + a2;
*/
}
