#include "dyncall.h"
#include "globals.h"
#include <stdio.h>
int invoke(char const* signature, void* t)
{
  DCCallVM   * p = (DCCallVM*) G_callvm;
  char const * sig = signature;
  char         rtype;
  char         atype;
  int          pos = 0;
  int          s = 0;

  clear_V();
  
  rtype = *sig++;
  dcReset(p);

  while ( (atype = *sig++) != '\0') {
    pos++;
    switch(atype) {
      case 'f': dcArgFloat   (p,K_f[pos]); break;
      case 'i': dcArgInt     (p,K_i[pos]); break;
      case 'd': dcArgDouble  (p,K_d[pos]); break;
      case 'j': dcArgLong    (p,K_j[pos]); break;
      case 'l': dcArgLongLong(p,K_l[pos]); break;
      case 'p': dcArgPointer (p,K_p[pos]); break;
      default: printf("invalid argument signature;"); return 0;
    }
  }
  
  switch(rtype) 
  {
    case 'v': dcCallVoid(p,t); s=1; /*TODO:check that no return-arg was touched.*/ break;
    case 'f': s = (dcCallFloat   (p,t) == K_f[pos]) ; break;
    case 'i': s = (dcCallInt     (p,t) == K_i[pos]) ; break;
    case 'd': s = (dcCallDouble  (p,t) == K_d[pos]) ; break;
    case 'j': s = (dcCallLong    (p,t) == K_j[pos]) ; break;
    case 'l': s = (dcCallLongLong(p,t) == K_l[pos]) ; break;
    case 'p': s = (dcCallPointer (p,t) == K_p[pos]) ; break;
    default: printf("invalid return-type signature;"); return 0;
  }

  if (!s) { printf("return value mismatch;"); return 0; }
  /* test: */
  sig = signature+1;
  pos = 1;
  while ( (atype = *sig++) != '\0') {
    switch(atype) {
      case 'f': s = ( V_f[pos] == K_f[pos] ); break;
      case 'i': s = ( V_i[pos] == K_i[pos] ); break;
      case 'd': s = ( V_d[pos] == K_d[pos] ); break;
      case 'j': s = ( V_j[pos] == K_j[pos] ); break;
      case 'l': s = ( V_l[pos] == K_l[pos] ); break;
      case 'p': s = ( V_p[pos] == K_p[pos] ); break;
      default: printf("invalid return-type signature;"); return 0;
    }
    if (!s) {
      printf("arg mismatch at %d;", pos);
      return 0;
    }
    pos++;
  }
  return 1;
}

