#define DEF_CALL1(RT) \
typedef RT (*f_##RT) (i,i,i,i,i,i,i,i); \
RT call_##RT(void* target,void* regdata, int* data, int size) \
{ \
  f_##RT f = (f_##RT) target; \
  return f(data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]); \
}

#define DEF_CALL(RT) \
typedef RT (*f_##RT) (i,i,i,i,i,i,i,i); \
RT call_##RT(void* target,void* regdata, int* data, int size) \
{ \
  f_##RT f = (f_##RT) target; \
  return f(); \
}

typedef long long llong;
typedef long double ldouble;

DEF_CALL(int)
DEF_CALL(float)
DEF_CALL(double)
DEF_CALL(llong)
DEF_CALL(ldouble)
DEF_CALL(void)

