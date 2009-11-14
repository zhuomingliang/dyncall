#include "../common/platformInit.h"
#include "../../dyncallback/dyncall_callback.h"
#include <stdio.h>


char cbHandler(DCCallback* cb, DCArgs* args, DCValue* result, void* userdata)
{
  printf("reached callback handler\n");
  printf("userdata passed to callback handler (should be 1337): %i\n", *(int*)userdata);
  (*(int*)userdata) = 1;
  result->s = 1234;
  return 'i';		// @@@ support needed for 's', etc
}


int main()
{
  DCCallback* cb;
  short result = 0;
  int userdata = 1337;

  dcTest_initPlatform();

  printf("about to call callback...\n");

  cb = dcNewCallback("if)s", &cbHandler, &userdata);
  result = ((short(*)(int, float))cb)(123, 23.f);
  dcFreeCallback(cb);

  printf("successfully returned from callback handler\n");
  printf("userdata modified in callback handler (should be 1): %i\n", userdata);
  printf("result: callback_suite: %s\n", (userdata == 1) && (result == 1234) ? "1" : "0");

  dcTest_deInitPlatform();

  return 0;
}

