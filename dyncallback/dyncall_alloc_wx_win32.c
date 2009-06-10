#include "dyncall_alloc_wx.h"
#include <windows.h>
#include <assert.h>

int dcAllocWX(size_t size, void** ptr)
{
  LPVOID p = VirtualAlloc(0, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
  if (p == NULL) return -1;
  *ptr = p;
  return 0;
}

void dcFreeWX(void* p, size_t size)
{
  BOOL b = VirtualFree( p, 0, MEM_RELEASE);
  assert(b);
}
