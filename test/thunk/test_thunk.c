#include "../common/platformInit.h"
#include "../../dyncall/dyncall.h"
#include "../../dyncallback/dyncall_thunk.h"
#include "../../dyncallback/dyncall_alloc_wx.h"

/**
 ** test: thunks with several allocation modes
 **       such as on stack, on heap and explicit wx
 **
 **/

#include <stdio.h>
#include <assert.h>
#include <errno.h>

void my_entry(const char* text)
{
  printf(text);
}

typedef void (printfun)(const char*);

void test_stack()
{
  DCThunk t;
  printfun* fp;
  dcThunkInit(&t, (void*)&my_entry);
  fp = (printfun*)&t;
  fp("stack\n");
}

#include <stdlib.h>

void test_heap()
{
  printfun* fp;
  DCThunk* p = (DCThunk*)malloc( sizeof(DCThunk));
  dcThunkInit(p, (void*)&my_entry);
  fp = (printfun*)p;
  fp("heap\n");
  free(p);
}

void test_wx()
{
  DCThunk* p;
  printfun* fp;
  int err = dcAllocWX(sizeof(DCThunk), (void**) &p);
  assert(!err);
  dcThunkInit(p, (void*)&my_entry);
  fp = (printfun*)p;
  fp("wx\n");
  dcFreeWX((void*)p, sizeof(DCThunk));
}

int main()
{
  dcTest_initPlatform();

  test_wx();
  test_heap();
  test_stack();
  dcTest_deInitPlatform();

  return 0;
}

