
#include "dyncall.h"
#include "dyncall_callvm.h"
#include "dyncall_alloc.h"

void dcReset(DCCallVM* vm)
{ 
  vm->mVTpointer->reset(vm); 
}

void dcFree(DCCallVM* vm) 
{ 
  vm->mVTpointer->free(vm); 
}

void dcMode(DCCallVM* vm,DCint mode) 
{ 
  vm->mVTpointer->mode(vm,mode); 
}

void dcArgBool(DCCallVM* vm,DCbool x) 
{ 
  vm->mVTpointer->argBool(vm, x); 
}

void dcArgChar(DCCallVM* vm,DCchar x)
{ 
  vm->mVTpointer->argChar(vm, x); 
}

void dcArgShort(DCCallVM* vm,DCshort x) 
{ 
  vm->mVTpointer->argShort(vm, x); 
}

void dcArgInt(DCCallVM* vm,DCint x) 
{ 
  vm->mVTpointer->argInt(vm,x); 
}

void dcArgLong(DCCallVM* vm,DClong x) 
{ 
  vm->mVTpointer->argLong(vm,x); 
}

void dcArgLongLong(DCCallVM* vm, DClonglong x) 
{ 
  vm->mVTpointer->argLongLong(vm,x); 
}

void dcArgFloat(DCCallVM* vm, DCfloat x) 
{ 
  vm->mVTpointer->argFloat(vm,x); 
}

void dcArgDouble(DCCallVM* vm, DCdouble x) 
{ 
  vm->mVTpointer->argDouble(vm,x); 
}

void dcArgPointer(DCCallVM* vm, DCpointer x) 
{ 
  vm->mVTpointer->argPointer(vm,x); 
}

void dcCallVoid(DCCallVM* vm, DCpointer funcptr) 
{        
  vm->mVTpointer->callVoid(vm, funcptr); 
}

DCchar dcCallChar(DCCallVM* vm, DCpointer funcptr) 
{ 
  return vm->mVTpointer->callChar(vm, funcptr); 
}

DCbool dcCallBool(DCCallVM* vm, DCpointer funcptr) 
{ 
  return vm->mVTpointer->callBool(vm, funcptr); 
}

DCshort dcCallShort(DCCallVM* vm, DCpointer funcptr) 
{ 
  return vm->mVTpointer->callShort(vm, funcptr); 
}

DCint dcCallInt(DCCallVM* vm, DCpointer funcptr) 
{ 
  return vm->mVTpointer->callInt(vm, funcptr); 
}

DClong dcCallLong(DCCallVM* vm, DCpointer funcptr) 
{ 
  return vm->mVTpointer->callLong(vm, funcptr); 
}

DClonglong dcCallLongLong(DCCallVM* vm, DCpointer funcptr) 
{ 
  return vm->mVTpointer->callLongLong(vm, funcptr); 
}

DCfloat dcCallFloat(DCCallVM* vm, DCpointer funcptr) 
{ 
  return vm->mVTpointer->callFloat(vm, funcptr); 
}

DCdouble dcCallDouble(DCCallVM* vm, DCpointer funcptr) 
{ 
  return vm->mVTpointer->callDouble(vm, funcptr); 
}

DCpointer dcCallPointer(DCCallVM* vm, DCpointer funcptr) 
{ 
  return vm->mVTpointer->callPointer(vm, funcptr); 
}

