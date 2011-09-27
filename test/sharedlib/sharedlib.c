#include "dynload.h"

DLLib* mylib_load(char const *name)
{
  return dlLoadLibrary(name);
}
