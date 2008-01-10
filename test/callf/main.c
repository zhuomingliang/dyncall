/* test dcCallF API 
 * Copyright 2007 Daniel Adler.
 */

#include "../../dyncall/dyncall_callf.h"
#include <stdio.h>

/* sample void function */

void vf_iii(int x,int y,int z)
{
  printf("%d %d %d\n", x, y, z);
}

/* main */

int main(int argc, char* argv[])
{
  DCCallVM* vm;
  DCValue r;

  /* allocate call vm */
  vm = dcNewCallVM(4096);

  /* call using 'formatted' API */
  dcCallF(vm, &r, &vf_iii, "iii)v", 1, 2, 3);

  /* free vm */
  dcFree(vm);
  
  return 0;
}

