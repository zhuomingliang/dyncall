#include "dyncall.h"
#include <stdio.h>

int add1(unsigned char x) { return x + 1; }

int main(int argc, char* argv[])
{
  DCCallVM* vm;
  int result;
  int total;
  vm = dcNewCallVM(4096);
  dcArgChar( vm, (char) 255 );
  result = dcCallInt( vm, &add1 );
  total = (result == 256);
  printf("result: sign: %d\n", total); 
  return 0;
}
