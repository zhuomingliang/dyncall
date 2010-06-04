#include "common.h"
#include <assert.h>

#define v0 0
#define v1 1
#define v2 2
#define v3 3
#define v4 4
#define v5 5

void ext()
{
}

int main(int argc, char* argv[])
{
  int result;
  call_f0();
  call_f4();
  call_f8();
  n0();
  n8(1,2,3,4,5,6,7,8);
  result = dispatch(&f,v0,v1,v2,v3,v4,v5);
  assert(result == v0+v1+v2+v3+v4+v5+v0+v1+v2 );
  return 0;
}

