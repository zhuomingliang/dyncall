/*/////////////////////////////////////////////////////////////////////////////

  dynload_unix.c
  Copyright 2007 Daniel Adler.

  dynload module for .so files

/////////////////////////////////////////////////////////////////////////////*/


#include "dynload.h"

#include <dlfcn.h>

void* dlLoadLibrary(const char* libPath)
{
  return dlopen(libPath,RTLD_NOW);
}

void* dlFindSymbol(void* libHandle, const char* symbol)
{
  return dlsym(libHandle, symbol);
}

void  dlFreeLibrary(void* libHandle)
{
  dlclose(libHandle);
}

