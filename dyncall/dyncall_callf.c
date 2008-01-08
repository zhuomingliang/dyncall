#include "dyncall_callf.h"

void dcVCallF(DCCallVM* vm, DCValue* result, DCpointer funcptr, const DCsigchar* signature, va_list args)
{
  const DCsigchar* ptr = signature;
  DCsigchar ch;
  dcReset(vm);
  while ( (ch=*ptr++) != '\0' && ch != DC_SIGCHAR_ENDARG) {

    switch(ch) {
      case DC_SIGCHAR_BOOL: 
        dcArgBool      (vm, (DCbool)       va_arg( args, DCint  ) ); 
        break;
      case DC_SIGCHAR_CHAR:
        dcArgChar      (vm, (DCchar)       va_arg( args, DCint  ) );
        break;
      case DC_SIGCHAR_SHORT:
        dcArgShort     (vm, (DCshort)      va_arg( args, DCint  ) );
        break;
      case DC_SIGCHAR_INT:
        dcArgInt       (vm, (DCint)        va_arg( args, DCint  ) );
        break;
      case DC_SIGCHAR_LONG:
        dcArgLong      (vm, (DClong)       va_arg( args, DClong ) );
        break;
      case DC_SIGCHAR_LONGLONG:
        dcArgLongLong  (vm, (DClonglong)   va_arg( args, DClonglong ) );
        break;
      case DC_SIGCHAR_FLOAT:
        dcArgFloat     (vm, (DCfloat)      va_arg( args, DCdouble ) );
        break;
      case DC_SIGCHAR_DOUBLE:
        dcArgDouble    (vm, (DCdouble)     va_arg( args, DCdouble ) );
        break;
      case DC_SIGCHAR_POINTER:
        dcArgPointer   (vm, (DCpointer)    va_arg( args, DCpointer ) );
        break;
    }
  }

  switch(*ptr) {
    case DC_SIGCHAR_VOID:                   dcCallVoid      (vm,funcptr); break;
    case DC_SIGCHAR_BOOL:       result->B = dcCallBool      (vm,funcptr); break;
    case DC_SIGCHAR_CHAR:       result->c = dcCallChar      (vm,funcptr); break;
    case DC_SIGCHAR_SHORT:      result->s = dcCallShort     (vm,funcptr); break;
    case DC_SIGCHAR_INT:        result->i = dcCallInt       (vm,funcptr); break;
    case DC_SIGCHAR_LONG:       result->l = dcCallLong      (vm,funcptr); break;
    case DC_SIGCHAR_LONGLONG:   result->l = dcCallLongLong  (vm,funcptr); break;
    case DC_SIGCHAR_FLOAT:      result->f = dcCallFloat     (vm,funcptr); break;
    case DC_SIGCHAR_DOUBLE:     result->d = dcCallDouble    (vm,funcptr); break;
    case DC_SIGCHAR_POINTER:    result->p = dcCallPointer   (vm,funcptr); break;
  }
}

void dcCallF(DCCallVM* vm, DCValue* result, DCpointer funcptr, const DCsigchar* signature, ...)
{
  va_list va;
  va_start(va, signature);
  dcVCallF(vm,result,funcptr,signature,va);
  va_end(va);
}

