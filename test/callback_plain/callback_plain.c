#include "../common/platformInit.h"
#include "../../dyncallback/dyncall_callback.h"
#include <stdio.h>


char cbHandler(DCCallback* cb, DCArgs* args, DCValue* result, void* userdata)
{
  int* ud = (int*)userdata;
  int       arg1 = dcArgs_int     (args);
  float     arg2 = dcArgs_float   (args);
  short     arg3 = dcArgs_short   (args);
  double    arg4 = dcArgs_double  (args);
  long long arg5 = dcArgs_longlong(args);

  printf("reached callback\n");
  printf("userdata (should be 1337): %d\n", *ud);
  printf("1st argument (should be  123): %d\n", arg1);
  printf("2nd argument (should be 23.f): %f\n", arg2);
  printf("3rd argument (should be    3): %d\n", arg3);
  printf("4th argument (should be 1.82): %f\n", arg4);
  printf("5th argument (should be 9909): %lld\n", arg5);

  if(*ud == 1337) *ud = 1;
  if(arg1 ==  123) ++*ud;
  if(arg2 == 23.f) ++*ud;
  if(arg3 ==    3) ++*ud;
  if(arg4 == 1.82) ++*ud;
  if(arg5 == 9909) ++*ud;
  result->s = 1234;
  return 'i';		// @@@ support needed for 's', etc
}


int main()
{
  DCCallback* cb;
  short result = 0;
  int userdata = 1337;

  dcTest_initPlatform();

  printf("about to callback...\n");
  cb = dcNewCallback("if)s", &cbHandler, &userdata);
  result = ((short(*)(int, float, short, double, long long))cb)(123, 23.f, 3, 1.82, 9909);
  dcFreeCallback(cb);
  printf("successfully returned from callback\n");
  printf("return value (should be 1234): %d\n", result);

  printf("result: callback_suite: %s\n", (userdata == 6) && (result == 1234) ? "1" : "0");

  dcTest_deInitPlatform();

  return 0;
}

