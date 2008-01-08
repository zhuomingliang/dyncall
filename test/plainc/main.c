#include "../testmain/stdio.h"

#include "../../dyncall/dyncall.h"

void foo()
{
  printf("foo\n");
}
void iii(int a, int b, int c)
{
  printf("%d %d %d\n", a,b,c);
}

int a;

void iiiiiiiiii(int a,int b, int c, int d, int e, int f, int g, int h, int i, int j)
{
  a = g;
  a += h;
  a += i;
  a += j;
//  printf("%d %d %d %d %d %d %d %d %d %d\n", a,b,c,d,e,f,g,h,i,j);
}

int test_main(int argc, char* argv)
{
  printf("hello\n");
  DCCallVM* vm = dcNewCallVM(4096);
  // dcCallVoid(vm, &foo);
  // dcReset(vm);
  dcArgInt(vm, 3);
  dcArgInt(vm, 2);
  dcArgInt(vm, 1);
  dcCallVoid(vm, &iii);
  dcFree(vm);
  iiiiiiiiii(1,2,3,4,5,6,7,8,9,10);
  printf("done\n");
  printf("%d\n", a);
  return 0;
}


