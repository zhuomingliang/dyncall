#include <assert.h>
#include "_auto_config.h"
#include "dyncall_signature.h"
#include "env.h"

DCValueSet ValueMatrix[CONFIG_MAXARGS];
DCValue    Args[CONFIG_MAXARGS];
DCValue    Result;

void GetReferenceArg(DCValue* output, char ch, int pos)
{
static const int Ki = 134;
static const double Kd = 1.012356;
static const float Kf = 1.20432545f; 
static const int Kp = 0x1020345;
static const DClonglong Kl = 24534543;

  DCValue value;
  output->L = 0xCAFEBABEDEADC0DELL;
  pos = pos + 2;
  switch(ch) {
    case DC_SIGCHAR_BOOL:     output->B = ( (pos*Ki) % 2) ? DC_TRUE : DC_FALSE ; break;
    case DC_SIGCHAR_INT:      output->i = pos*Ki; break;
    case DC_SIGCHAR_FLOAT:    output->f = ( (float) pos ) * Kf; break;
    case DC_SIGCHAR_DOUBLE:   output->d = ( (double) pos ) * Kd; break;
    case DC_SIGCHAR_LONGLONG: output->l = ( (long long) pos ) * Kl; break;
    case DC_SIGCHAR_POINTER:  output->p = (DCpointer) (unsigned long) (pos*Kp); break;
    default: assert(0);
  }
}

void GetReferenceResult(DCValue* output, char ch)
{
  GetReferenceArg(output, ch, -1);
}

void InitEnv()
{
  int pos;
  for(pos = 0 ;pos < CONFIG_MAXARGS ;++pos) {
    DCValue ref;
    GetReferenceArg( &ref, DC_SIGCHAR_BOOL     , pos);     ValueMatrix[pos].B = ref.B;
    GetReferenceArg( &ref, DC_SIGCHAR_INT      , pos);     ValueMatrix[pos].i = ref.i;
    GetReferenceArg( &ref, DC_SIGCHAR_FLOAT    , pos);    ValueMatrix[pos].f = ref.f;
    GetReferenceArg( &ref, DC_SIGCHAR_DOUBLE   , pos);   ValueMatrix[pos].d = ref.d;
    GetReferenceArg( &ref, DC_SIGCHAR_LONGLONG , pos); ValueMatrix[pos].l = ref.l;
    GetReferenceArg( &ref, DC_SIGCHAR_POINTER  , pos);  ValueMatrix[pos].p = ref.p;
  }
}

/* Global Options. */
int OptionVerbose = 0;

