#include "../common/platformInit.h"
#include "../../dyncallback/dyncall_callback.h"
#include <stdio.h>


char cbHandler(DCCallback* cb, DCArgs* args, DCValue* result, void* userdata)
{
  int* ud = (int*)userdata;
  int   arg1 = dcArgs_int  (args);
  float arg2 = dcArgs_float(args);

  printf("reached callback\n");
  printf("userdata (should be 1337): %d\n", *ud);
  printf("1st argument (should be  123): %d\n", arg1);
  printf("2nd argument (should be 23.f): %d\n", arg2);

  if(*ud == 1337) *ud = 1;
  if(arg1 ==  123) ++*ud;
  if(arg2 == 23.f) ++*ud;
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
  result = ((short(*)(int, float))cb)(123, 23.f);
  dcFreeCallback(cb);
  printf("successfully returned from callback\n");
  printf("return value (should be 1234): %d\n", result);

  printf("result: callback_suite: %s\n", (userdata == 3) && (result == 1234) ? "1" : "0");

  dcTest_deInitPlatform();

  return 0;
}

