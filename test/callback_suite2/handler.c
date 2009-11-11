#include "_auto_config.h"
#include <assert.h>
#include "dyncall_callback.h"
#include "env.h"

char handler(DCCallback* that, DCArgs* input, DCValue* output, void* userdata)
{
  DCValue ref;
  const char* signature = (const char*) userdata;
  
  char ch;
  int pos = 0; 
  for(;;) {
    ch  = *signature++;
    if (ch == DC_SIGCHAR_ENDARG) break;
    Args[pos].L = 0xDEADC0DECAFEBABELL;
    switch(ch) {
      case DC_SIGCHAR_BOOL:     Args[pos].B = dcArgs_bool    (input); break;
      case DC_SIGCHAR_INT:      Args[pos].i = dcArgs_int     (input); break;
      case DC_SIGCHAR_LONGLONG: Args[pos].l = dcArgs_longlong(input); break;
      case DC_SIGCHAR_FLOAT:    Args[pos].f = dcArgs_float   (input); break; 
      case DC_SIGCHAR_DOUBLE:   Args[pos].d = dcArgs_double  (input); break;
      case DC_SIGCHAR_POINTER:  Args[pos].p = dcArgs_pointer (input); break;
    }
    ++pos;
  }

  ch = *signature++;

  /* currently, no void result is supported by the suite */
  InitReferenceResult(output, ch);
  switch(ch) {
    case DC_SIGCHAR_BOOL:     return 'i';
    case DC_SIGCHAR_INT:      return 'i';
    case DC_SIGCHAR_POINTER:  return 'i';
    case DC_SIGCHAR_LONGLONG: return 'l';
    case DC_SIGCHAR_FLOAT:    return 'f';
    case DC_SIGCHAR_DOUBLE:   return 'd';
    default: assert(0); return 'v';
  }
}

