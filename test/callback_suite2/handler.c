#include "_auto_config.h"
#include <assert.h>
#include "dyncall_callback.h"
#include "env.h"
#include "signature_utils.h"

char handler(DCCallback* that, DCArgs* input, DCValue* output, void* userdata)
{
  DCValue ref;
  const char* signature = (const char*) userdata;
  
  char ch;

  signature = SignatureSkipCallPrefix(signature);

  int pos = 0; 
  for(;;) {
    ch = *signature++;
    if (ch == DC_SIGCHAR_ENDARG) break;
    Args[pos].L = 0xDEADC0DECAFEBABELL;
    switch(ch) {
      case DC_SIGCHAR_BOOL:     Args[pos].B = dcArgs_bool     (input); break;
      case DC_SIGCHAR_CHAR:     Args[pos].c = dcArgs_char     (input); break;
      case DC_SIGCHAR_UCHAR:    Args[pos].C = dcArgs_uchar    (input); break;
      case DC_SIGCHAR_SHORT:    Args[pos].s = dcArgs_short    (input); break;
      case DC_SIGCHAR_USHORT:   Args[pos].S = dcArgs_ushort   (input); break;
      case DC_SIGCHAR_INT:      Args[pos].i = dcArgs_int      (input); break;
      case DC_SIGCHAR_UINT:     Args[pos].I = dcArgs_uint     (input); break;
      case DC_SIGCHAR_LONG:     Args[pos].l = dcArgs_long     (input); break;
      case DC_SIGCHAR_ULONG:    Args[pos].L = dcArgs_ulong    (input); break;
      case DC_SIGCHAR_LONGLONG: Args[pos].l = dcArgs_longlong (input); break;
      case DC_SIGCHAR_ULONGLONG:Args[pos].L = dcArgs_ulonglong(input); break;
      case DC_SIGCHAR_FLOAT:    Args[pos].f = dcArgs_float    (input); break; 
      case DC_SIGCHAR_DOUBLE:   Args[pos].d = dcArgs_double   (input); break;
      case DC_SIGCHAR_POINTER:  Args[pos].p = dcArgs_pointer  (input); break;
    }
    ++pos;
  }

  ch = *signature++;

  /* currently, no void result is supported by the suite */
  GetReferenceResult(output, ch);
  switch(ch) {
    case DC_SIGCHAR_BOOL:     return 'i';
    case DC_SIGCHAR_CHAR:     return 'i';
    case DC_SIGCHAR_UCHAR:    return 'i';
    case DC_SIGCHAR_SHORT:    return 'i';
    case DC_SIGCHAR_USHORT:   return 'i';
    case DC_SIGCHAR_INT:      return 'i';
    case DC_SIGCHAR_UINT:     return 'i';
    case DC_SIGCHAR_LONG:     return (sizeof(long) == 4) ? 'i' : 'l';
    case DC_SIGCHAR_ULONG:    return (sizeof(long) == 4) ? 'i' : 'l';
    case DC_SIGCHAR_LONGLONG: return 'l';
    case DC_SIGCHAR_ULONGLONG:return 'L';
    case DC_SIGCHAR_FLOAT:    return 'f';
    case DC_SIGCHAR_DOUBLE:   return 'd';
    case DC_SIGCHAR_POINTER:  return (sizeof(void*) == 4) ? 'i' : 'l';
    default: assert(0); return 'v';
  }
}

