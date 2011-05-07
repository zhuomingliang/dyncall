#include "dyncall.h"
#include <sys/syscall.h> 
DCCallVM* callvm;

void syscallvm_init()
{
  callvm = dcNewCallVM(4096);
  dcMode(callvm, DC_CALL_SYS_DEFAULT);
}

int syscall_write(int fd, char* buf, size_t len)
{
  dcReset(callvm);
  dcArgInt(callvm, fd);
  dcArgPointer(callvm, buf);
  dcArgInt(callvm, len);
  return dcCallInt(callvm, (DCpointer)(ptrdiff_t)SYS_write);
}

int main(int argc, char* argv[])
{
  syscallvm_init();
  syscall_write(1/*stdout*/, "syscall: result: 1\n", 19);
  return 0;
}

