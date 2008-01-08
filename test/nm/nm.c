#include "../../dynload/dynload.h"
#include <stdio.h>


int test_main(int argc, char* argv[])
{
  int i, n;
  const char* libpath = argv[1];
  void* handle = dlLoadLibrary(libpath);
  if (argc == 1) {
    fprintf(stderr, "usage : %s <dllpath>\n", argv[0]);
    return -1;
  }
  if (!handle) {
    fprintf(stderr, "unable to open library %s\n", libpath);
  }

  n = dlGetSymbolCount(handle);

  for (i = 0; i < n ; ++i) {
    const char* name = dlGetSymbolNameAt(handle,i);
    printf("%s\n", name);
  }
  dlFreeLibrary(handle);
}

