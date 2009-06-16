#include "../../dyncallback/dyncall_alloc_wx.h"
#include <stdio.h>

int main(int argc, char* argv)
{
  int err;
  void* ptr;
  err = dcAllocWX(23, &ptr);
  if (!err) dcFreeWX(ptr, 23);
  printf("result: test_alloc_wx: %d\n", (!err) ? 1 : 0 );
  return err;
}

