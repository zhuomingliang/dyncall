#include "../common/platformInit.h"
#include "../../dyncallback/dyncall_thunk.h"
#include "../../dyncallback/dyncall_callback_arm32_arm.h"
#include "../../dyncallback/dyncall_callback.h"
#include <stdio.h>


char cbHandler(DCCallback* cb, DCArgs* args, DCValue* result, void* userdata)
{
  int* ud = (int*)userdata;
  int       arg1 = dcbArgInt     (args);
  float     arg2 = dcbArgFloat   (args);
  short     arg3 = dcbArgShort   (args);
  double    arg4 = dcbArgDouble  (args);
  long long arg5 = dcbArgLongLong(args);

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
  cb = dcbNewCallback("ifsdl)s", &cbHandler, &userdata);
  result = ((short(*)(int, float, short, double, long long))cb)(123, 23.f, 3, 1.82, 9909ll);
  dcbFreeCallback(cb);
  printf("successfully returned from callback\n");
  printf("return value (should be 1234): %d\n", result);

  printf("result: callback_plain: %s\n", (userdata == 6) && (result == 1234) ? "1" : "0");

  dcTest_deInitPlatform();

  return 0;
}

