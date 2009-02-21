#include "dynload.h"

#include <windows.h>

struct DLLib_
{
  IMAGE_DOS_HEADER dos_header;
};

struct DLSyms_
{
  const char* pBase;
  ptrdiff_t* pNames;
  ptrdiff_t* pFuncs;
  size_t     count;
};

size_t dlSyms_sizeof()
{
  return sizeof(DLSyms);
}

void dlSymsInit(DLSyms* pResolver, DLLib* pLib)
{
  const char* ptr = (const char*) pLib;
  IMAGE_DOS_HEADER*       pDOSHeader      = (IMAGE_DOS_HEADER*) ptr;  
  IMAGE_NT_HEADERS*       pNTHeader       = (IMAGE_NT_HEADERS*) ( ptr + pDOSHeader->e_lfanew );  
  IMAGE_DATA_DIRECTORY*   pExportsDataDir = &pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
  IMAGE_EXPORT_DIRECTORY* pExports        = (IMAGE_EXPORT_DIRECTORY*) (ptr + pExportsDataDir->VirtualAddress);  
  pResolver->pBase  = ptr;
  pResolver->pNames = (ptrdiff_t*) ( ptr + ( (ptrdiff_t)pExports->AddressOfNames) );
  pResolver->pFuncs = (ptrdiff_t*) ( ptr+( (ptrdiff_t) pExports->AddressOfFunctions) );
  pResolver->count  = (size_t)       pExports->NumberOfNames;
}

void dlSymsCleanup(DLSyms* pResolver)
{
  /* do nothing. */
}

int dlSymsCount(DLSyms* pResolver)
{
/*
  unsigned char* ptr = (unsigned char*) handle;
  IMAGE_DOS_HEADER*       pDOSHeader      = (IMAGE_DOS_HEADER*) ptr;  
  IMAGE_NT_HEADERS*       pNTHeader       = (IMAGE_NT_HEADERS*) ( ptr + pDOSHeader->e_lfanew );  
  IMAGE_DATA_DIRECTORY*   pExportsDataDir = &pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
  IMAGE_EXPORT_DIRECTORY* pExports        = (IMAGE_EXPORT_DIRECTORY*) (ptr + pExportsDataDir->VirtualAddress);  
  return pExports->NumberOfNames;
*/
  return pResolver->count;
}

const char* dlSymsName(DLSyms* pResolver, int index)
{
/*
  unsigned char* ptr = (unsigned char*) handle;
  IMAGE_DOS_HEADER*       pDOSHeader      = (IMAGE_DOS_HEADER*) ptr;  
  IMAGE_NT_HEADERS*       pNTHeader       = (IMAGE_NT_HEADERS*) ( ptr + pDOSHeader->e_lfanew );  
  IMAGE_DATA_DIRECTORY*   pExportsDataDir = &pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
  IMAGE_EXPORT_DIRECTORY* pExports        = (IMAGE_EXPORT_DIRECTORY*) (ptr + pExportsDataDir->VirtualAddress);  
  ptrdiff_t* pNames = (ptrdiff_t*) ( ptr + ( (ptrdiff_t)pExports->AddressOfNames) );
  return (const char*) ( ptr + pNames[index] );
*/
  return (const char*) ( ( (const char*) pResolver->pBase ) + pResolver->pNames[index] );
}

void* dlSymsValue(DLSyms* pResolver, int index)
{
/*
  unsigned char* ptr = (unsigned char*) handle;
  IMAGE_DOS_HEADER*       pDOSHeader      = (IMAGE_DOS_HEADER*) ptr;  
  IMAGE_NT_HEADERS*       pNTHeader       = (IMAGE_NT_HEADERS*) ( ptr + pDOSHeader->e_lfanew );  
  IMAGE_DATA_DIRECTORY*   pExportsDataDir = &pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
  IMAGE_EXPORT_DIRECTORY* pExports        = (IMAGE_EXPORT_DIRECTORY*) (ptr + pExportsDataDir->VirtualAddress);  
  ptrdiff_t* pFuncs = (ptrdiff_t*) ( ptr+( (ptrdiff_t) pExports->AddressOfFunctions) );
  return (void*) ( ptr + pFuncs[index] );
*/
  return (void*) ( pResolver->pBase + pResolver->pFuncs[index] );
}

