#include "dyncall.h"
#include "globals.h"
#include <stdio.h>
#include <string.h>
char  linebuf[1024];
void* G_callvm;
  
void run_test(int i) {  
  char const * sig;
  void * target;
  int success;
  sig = G_sigtab[i];
  target = G_funtab[i];
  printf("%d:%s:",i,sig);
  success = invoke(sig,target);
  printf("%d\n",success);
}

void run_all() {
  int i;
  for(i=0;i<G_ncases;++i) {
    run_test(i);
  }
}

int main(int argc, char* argv[])
{
  init_K(G_maxargs);
  G_callvm = (DCCallVM*) dcNewCallVM(4096);
  run_all();
  return 0;
}

