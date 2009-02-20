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

#include "../common/platformInit.h"
#include "../../dynload/dynload.h"
#include <stdio.h>


int main(int argc, char* argv[])
{
  dcTest_initPlatform();

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

  dcTest_deInitPlatform();

  return 0;
}

