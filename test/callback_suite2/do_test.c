#include <assert.h>
#include "_auto_config.h"
#include "invokers.h"
#include "dyncall_callback.h"
#include "sigstrings.h"
#include "env.h"
#include "print.h"
#include <stdio.h>

int CompareValues(char type, DCValue* a, DCValue* b)
{
  int isequal = 0;
  switch(type) 
  {
    case DC_SIGCHAR_BOOL:      isequal = (a->B == b->B) ? 1 : 0 ; break;
    case DC_SIGCHAR_INT:       isequal = (a->i == b->i) ? 1 : 0 ; break;
    case DC_SIGCHAR_LONGLONG:  isequal = (a->l == b->l) ? 1 : 0 ; break;
    case DC_SIGCHAR_FLOAT:     isequal = (a->f == b->f) ? 1 : 0 ; break;
    case DC_SIGCHAR_DOUBLE:    isequal = (a->d == b->d) ? 1 : 0 ; break;
    case DC_SIGCHAR_POINTER:   isequal = (a->p == b->p) ? 1 : 0 ; break;
    default: assert(0);
  }
  return isequal;
}

int Compare(const char* signature)
{
  DCValue ref;
  int total = 1;
  int pos;
  int isequal;
  char ch;

  /* check arguments */

  pos = 0;

  for(;;) {

    ch  = *signature++;
    
    if (ch == DC_SIGCHAR_ENDARG) break;
    GetReferenceArg(&ref, ch, pos);
    isequal = CompareValues( ch, &ref, &Args[pos] );
    if ( !isequal ) {
      if (OptionVerbose) { total = 0; fprintf(stdout, " @%d ", pos); }
      else return 0;
    }
    ++ pos;
  }
    
  ch  = *signature++;

  /* check result */

  GetReferenceResult(&ref, ch);

  isequal = CompareValues(ch, &ref, &Result);
  if (!isequal) {
    if (OptionVerbose) { total = 0; fprintf(stdout, " @-1 "); }
    else return 0;
  }

  return total;
}


extern DCCallbackHandler handler; /* see handler.c for implementation */

int DoTest(int id)
{
  int index, result;
  const char* signature;
  DCCallback* pcb;

  assert( id > 0 && id <= CONFIG_NSIGS );
  index = id - 1;
  
  signature = GetSignature(index);
  PrintCaseInfo(id,signature);

  pcb = dcNewCallback( signature, handler, (void*) signature );
  assert(pcb != NULL);
  DoInvoke(index, (void*) pcb);
  result = Compare(signature); 
  PrintCaseResult(result);
  dcFreeCallback(pcb);
  return result;
}

