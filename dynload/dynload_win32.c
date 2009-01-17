/*/////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////*/

/*/////////////////////////////////////////////////////////////////////////////

  dynload_win32.c

  dynload module for .dll files

/////////////////////////////////////////////////////////////////////////////*/


#include "dynload.h"

#include <windows.h>

void* dlLoadLibrary(const char* libPath)
{
  return LoadLibrary(libPath);
}

void* dlFindSymbol(void* libHandle, const char* symbol)
{
  return (void*) GetProcAddress( (HINSTANCE)libHandle, symbol);
}

void  dlFreeLibrary(void* libHandle)
{
  FreeLibrary( (HINSTANCE)libHandle );
}

size_t dlGetSymbolCount(void* handle)
{
  unsigned char* ptr = (unsigned char*) handle;
  IMAGE_DOS_HEADER*       pDOSHeader      = (IMAGE_DOS_HEADER*) ptr;  
  IMAGE_NT_HEADERS*       pNTHeader       = (IMAGE_NT_HEADERS*) ( ptr + pDOSHeader->e_lfanew );  
  IMAGE_DATA_DIRECTORY*   pExportsDataDir = &pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
  IMAGE_EXPORT_DIRECTORY* pExports        = (IMAGE_EXPORT_DIRECTORY*) (ptr + pExportsDataDir->VirtualAddress);  
  return pExports->NumberOfNames;
}

const char* dlGetSymbolNameAt(void* handle, size_t index)
{
  unsigned char* ptr = (unsigned char*) handle;
  IMAGE_DOS_HEADER*       pDOSHeader      = (IMAGE_DOS_HEADER*) ptr;  
  IMAGE_NT_HEADERS*       pNTHeader       = (IMAGE_NT_HEADERS*) ( ptr + pDOSHeader->e_lfanew );  
  IMAGE_DATA_DIRECTORY*   pExportsDataDir = &pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
  IMAGE_EXPORT_DIRECTORY* pExports        = (IMAGE_EXPORT_DIRECTORY*) (ptr + pExportsDataDir->VirtualAddress);  
  ptrdiff_t* pNames = (ptrdiff_t*) ( ptr + ( (ptrdiff_t)pExports->AddressOfNames) );
  return (const char*) ( ptr + pNames[index] );
}

void* dlGetSymbolValueAt(void* handle, size_t index)
{
  unsigned char* ptr = (unsigned char*) handle;
  IMAGE_DOS_HEADER*       pDOSHeader      = (IMAGE_DOS_HEADER*) ptr;  
  IMAGE_NT_HEADERS*       pNTHeader       = (IMAGE_NT_HEADERS*) ( ptr + pDOSHeader->e_lfanew );  
  IMAGE_DATA_DIRECTORY*   pExportsDataDir = &pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
  IMAGE_EXPORT_DIRECTORY* pExports        = (IMAGE_EXPORT_DIRECTORY*) (ptr + pExportsDataDir->VirtualAddress);  
  ptrdiff_t* pFuncs = (ptrdiff_t*) ( ptr+( (ptrdiff_t) pExports->AddressOfFunctions) );
  return (void*) ( ptr + pFuncs[index] );
}

