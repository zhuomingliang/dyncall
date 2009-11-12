#include <assert.h>
#include "_auto_config.h"
#include "dyncall_signature.h"
#include "env.h"

DCValueSet ValueMatrix[CONFIG_MAXARGS];
DCValue    Args[CONFIG_MAXARGS];
DCValue    Result;

static const int Ki = 134;
static const double Kd = 1.012356;
static const float Kf = 1.20432545f; 
static const int Kp = 0x1020345;
static const DClonglong Kl = 24534543;

void InitReferenceArg(DCValue* output, char ch, int pos)
{
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

void InitReferenceResult(DCValue* output, char ch)
{
  InitReferenceArg(output, ch, -1);
}

void InitEnv()
{
  int pos;
  for(pos = 0 ;pos < CONFIG_MAXARGS ;++pos) {
    DCValue ref;
    InitReferenceArg( &ref, DC_SIGCHAR_BOOL, pos); ValueMatrix[pos].B = ref.B;
    InitReferenceArg( &ref, DC_SIGCHAR_INT,  pos); ValueMatrix[pos].i = ref.i;
    InitReferenceArg( &ref, DC_SIGCHAR_FLOAT, pos); ValueMatrix[pos].f = ref.f;
    InitReferenceArg( &ref, DC_SIGCHAR_DOUBLE, pos); ValueMatrix[pos].d = ref.d;
    InitReferenceArg( &ref, DC_SIGCHAR_LONGLONG, pos); ValueMatrix[pos].l = ref.l;
    InitReferenceArg( &ref, DC_SIGCHAR_POINTER, pos); ValueMatrix[pos].p = ref.p;
  }
}

/* Global Options. */
int OptionVerbose = 0;

