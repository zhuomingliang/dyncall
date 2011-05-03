#include <stdlib.h>
#include "globals.h"

#define VSIZE 1+MAXARGS

char      k_c[VSIZE];
short     k_s[VSIZE];
int       k_i[VSIZE];
long      k_j[VSIZE];
long long k_l[VSIZE];
void*     k_p[VSIZE];
float     k_f[VSIZE];
double    k_d[VSIZE];

const char      *K_c = (const char*)      k_c;
const short     *K_s = (const short*)     k_s;
const int       *K_i = (const int*)       k_i;
const long      *K_j = (const long*)      k_j;
const long long *K_l = (const long long*) k_l;
void* const    *K_p = (void* const)      k_p;
const float     *K_f = (const float*)     k_f;
const double    *K_d = (const double*)    k_d;

char      v_c[VSIZE];
short     v_s[VSIZE];
int       v_i[VSIZE];
long      v_j[VSIZE];
long long v_l[VSIZE];
void*     v_p[VSIZE];
float     v_f[VSIZE];
double    v_d[VSIZE];

char      *V_c = v_c;
short     *V_s = v_s;
int       *V_i = v_i;
long      *V_j = v_j;
long long *V_l = v_l;
void*     *V_p = v_p;
float     *V_f = v_f;
double    *V_d = v_d;

int       fid;

double rand_d() { return ( ( (double) rand() )  / ( (double) RAND_MAX ) ); }

void init_K()
{
  int i;
  for(i=0;i<VSIZE;++i) {
    k_c[i] = (char)      (rand_d() * (1<<7));
    k_i[i] = (int)       (rand_d() * (1<<(sizeof(int)*8-1)));
    k_s[i] = (short)     (rand_d() * (1<<(sizeof(int)*8-1)));
    k_j[i] = (long)      (rand_d() * (1L<<(sizeof(long)*8-1)));
    k_l[i] = (long long) (rand_d() * (1LL<<(sizeof(long long)*8-1)));
    k_p[i] = (void*)     (long) (rand_d() * (1L<<(sizeof(void*)*8-1)));
    k_f[i] = (float)     (rand_d() * __FLT_MAX__);
    k_d[i] = (double)    (rand_d() * __DBL_MAX__);
  }
}

void clear_V()
{
  int i;
  for(i=0;i<VSIZE;++i) {
    V_i[i] = 0;
    V_f[i] = 0;
    V_d[i] = 0;
    V_l[i] = 0;
  }
}
