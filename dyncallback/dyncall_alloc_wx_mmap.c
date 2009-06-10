#include "dyncall_alloc_wx.h"

#include <sys/types.h>
#include <sys/mman.h>

int dcAllocWX(size_t size, void** pp)
{
  void* p = mmap(0, size, PROT_EXEC|PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANON, -1, 0);
  if (p == ( (void*)-1 ) ) return -1;
  *pp = p;
  return 0;
}

void dcFreeWX(void* p, size_t size)
{
  munmap(p, size);
}
