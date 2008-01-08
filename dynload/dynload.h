/*/////////////////////////////////////////////////////////////////////////////

  dynload.h
  Copyright 2007 Daniel Adler.

/////////////////////////////////////////////////////////////////////////////*/


#ifndef DYNLOAD_H
#define DYNLOAD_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void* dlLoadLibrary(const char* libpath);
void  dlFreeLibrary(void* libhandle);
void* dlFindSymbol(void* libhandle, const char* symbol);

size_t      dlGetSymbolCount(void* libhandle);
const char* dlGetSymbolNameAt(void* libhandle, size_t index);
void*       dlGetSymbolValueAt(void* libhandle, size_t index);

#ifdef __cplusplus
}
#endif

#endif /* DYNLOAD_H */

