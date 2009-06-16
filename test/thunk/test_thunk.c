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
  dcThunkInit(&t, (void*) my_entry);
  printfun* fp = (printfun*) &t;
  fp("stack\n");
}

#include <stdlib.h>

void test_heap()
{
  DCThunk* p = (DCThunk*) malloc( sizeof(DCThunk) );
  dcThunkInit(p, (void*) my_entry);
  printfun* fp = (printfun*) p;
  fp("heap\n");
  free(p);
}

void test_wx()
{
  DCThunk* p;
  int err = dcAllocWX( sizeof(DCThunk), (void**) &p );
  assert(!err);
  dcThunkInit(p, (void*) my_entry);
  printfun* fp = (printfun*) p;
  fp("wx\n");
  dcFreeWX( (void*) p, sizeof(DCThunk) );
}

int main(int argc, char* argv[])
{
  test_wx();
  test_stack();
  test_heap();
  return 0;
}

