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
  printf(": 1\n");
}

typedef void (printfun)(const char*);

void test_stack()
{
  DCThunk t;
  printfun* fp;
  dcInitThunk(&t, (void*)&my_entry);
  fp = (printfun*)&t;
  fp("stack");
}

#include <stdlib.h>

void test_heap()
{
  printfun* fp;
  DCThunk* p = (DCThunk*)malloc(sizeof(DCThunk));
  if(!p) {
    printf("0\n");
    return;
  }
  dcInitThunk(p, (void*)&my_entry);
  fp = (printfun*)p;
  fp("heap");
  free(p);
}

void test_wx()
{
  DCThunk* p;
  printfun* fp;
  int err = dcAllocWX(sizeof(DCThunk), (void**)&p);
  if(err || !p) {
    printf("0\n");
    return;
  }
  dcInitThunk(p, (void*)&my_entry);
  fp = (printfun*)p;
  fp("wx");
  dcFreeWX((void*)p, sizeof(DCThunk));
}

int main()
{
  dcTest_initPlatform();

  printf("Allocating ...\n");
  printf("... W^X memory: ");
  test_wx();
  printf("... heap memory: ");
  test_heap();
  printf("... stack memory: ");
  test_stack();

  dcTest_deInitPlatform();

  return 0;
}

