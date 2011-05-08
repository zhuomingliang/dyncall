#include "dyncall.h"
#include "globals.h"
#include <stdio.h>
#include <string.h>
char  linebuf[1024];
void* G_callvm;
  
int run_test(int i) {  
  char const * sig;
  void * target;
  int success;
  sig = G_sigtab[i];
  target = G_funtab[i];
  printf("%d:%s:",i,sig);
  success = invoke(sig,target);
  printf("%d\n",success);
  return success;
}

int run_all() {
  int i;
  int failure = 0;
  for(i=0;i<G_ncases;++i) {
    failure |= !( run_test(i) );
  }
  return !failure;
}

int main(int argc, char* argv[])
{
  int total;
  init_K(G_maxargs);
  G_callvm = (DCCallVM*) dcNewCallVM(4096);
  total = run_all();
  if (total) printf("result: call_suite: %d\n", total);
  return 0;
}

