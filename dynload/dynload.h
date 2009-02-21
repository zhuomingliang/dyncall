/*

 Copyright (c) 2007-2009 Daniel Adler <dadler@uni-goettingen.de>, 
                         Tassilo Philipp <tphilipp@potion-studios.com>

 Permission to use, copy, modify, and distribute this software for any
 purpose with or without fee is hereby granted, provided that the above
 copyright notice and this permission notice appear in all copies.

 THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

*/

/*

  dynload library API

  Abstraction to module loading.
  Work is in progress to allow for enumeration of symbols.

  REVISION
  2007/12/11 initial

*/


#ifndef DYNLOAD_H
#define DYNLOAD_H

#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* --- public api ---------------------------------------------------------- */

/* shared library loading and explicit symbol resolving */

typedef struct DLLib_ DLLib;

DLLib* dlLoadLibrary(const char* libpath);
void   dlFreeLibrary(DLLib* pLib);
void*  dlFindSymbol(DLLib* pLib, const char* pSymbolName);

/* symbol table enumeration */

typedef struct DLSyms_ DLSyms;

size_t      dlSyms_sizeof();
void        dlSymsInit   (DLSyms* pSyms, DLLib* pLib);
void        dlSymsCleanup(DLSyms* pSyms);

int         dlSymsCount  (DLSyms* pSyms);
const char* dlSymsName   (DLSyms* pSyms, int index);
void*       dlSymsValue  (DLSyms* pSyms, int index);

#ifdef __cplusplus
}
#endif

#endif /* DYNLOAD_H */

