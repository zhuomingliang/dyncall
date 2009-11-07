#include "../common/platformInit.h"
#include "../../dyncallback/dyncall_callback.h"


char cbHandler(DCCallback* cb, DCArgs* args, DCValue* result, void* userdata)
{
  (*(int*)userdata) = 1;
  result->s = 1234;
  return 's';		// @@@ support needed
}


int main()
{
  DCCallback* cb;
  short result = 0;
  int success = 0;

  dcTest_initPlatform();

  cb = dcNewCallback("if)s", &cbHandler, &success);
  result = ((short(*)(int, float))cb)(123, 23.f);
  dcFreeCallback(cb);

  printf("result: callback_suite: %s\n", success && (result == 1234) ? "1" : "0");

  dcTest_deInitPlatform();

  return 0;
}

