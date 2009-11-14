#include "../common/platformInit.h"
#include "../../dyncallback/dyncall_callback.h"
#include <stdio.h>


char cbHandler(DCCallback* cb, DCArgs* args, DCValue* result, void* userdata)
{
  int* ud = (int*)userdata;

  printf("reached callback\n");

  if(*ud == 1337) *ud = 1;
  if(dcArgs_int  (args) ==  123) ++*ud;
  if(dcArgs_float(args) == 23.f) ++*ud;
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

  printf("result: callback_suite: %s\n", (userdata == 3) && (result == 1234) ? "1" : "0");

  dcTest_deInitPlatform();

  return 0;
}

