#include "globals.h"

#define ret_v(X) 
#define ret_c(X) return(K_c[X]);
#define ret_s(X) return(K_s[X]);
#define ret_i(X) return(K_i[X]);
#define ret_j(X) return(K_j[X]);
#define ret_l(X) return(K_l[X]);
#define ret_p(X) return(K_p[X]);
#define ret_f(X) return(K_f[X]);
#define ret_d(X) return(K_d[X]);
extern int fid;

#define v void
#define c char
#define s short
#define i int
#define j long
#define l long long
#define p void*
#define f float
#define d double

#include "cases.h"

int G_ncases = sizeof(G_sigtab)/sizeof(G_sigtab[0]);

