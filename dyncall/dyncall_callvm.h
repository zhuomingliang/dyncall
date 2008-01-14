#ifndef DYNCALL_CALLVM_H
#define DYNCALL_CALLVM_H

#include "dyncall.h"

/* --- callvm virtual function table --------------------------------------- */

typedef struct DCCallVM_vt_ DCCallVM_vt;

struct DCCallVM_
{
  DCCallVM_vt* mVTpointer;
};

struct DCCallVM_vt_
{
  void         (*free)           (DCCallVM* vm);
  void         (*reset)          (DCCallVM* vm);
  void         (*mode)           (DCCallVM* vm,DCint        mode);
  void         (*argBool)        (DCCallVM* vm,DCbool          B);
  void         (*argChar)        (DCCallVM* vm,DCchar          c);
  void         (*argShort)       (DCCallVM* vm,DCshort         s);
  void         (*argInt)         (DCCallVM* vm,DCint           i);
  void         (*argLong)        (DCCallVM* vm,DClong          l);
  void         (*argLongLong)    (DCCallVM* vm,DClonglong      L);
  void         (*argFloat)       (DCCallVM* vm,DCfloat         f);
  void         (*argDouble)      (DCCallVM* vm,DCdouble        d);
  void         (*argPointer)     (DCCallVM* vm,DCpointer       p);
  void         (*callVoid)       (DCCallVM* vm,DCpointer funcptr);
  DCbool       (*callBool)       (DCCallVM* vm,DCpointer funcptr);
  DCchar       (*callChar)       (DCCallVM* vm,DCpointer funcptr);
  DCshort      (*callShort)      (DCCallVM* vm,DCpointer funcptr);
  DCint        (*callInt)        (DCCallVM* vm,DCpointer funcptr);
  DClong       (*callLong)       (DCCallVM* vm,DCpointer funcptr);
  DClonglong   (*callLongLong)   (DCCallVM* vm,DCpointer funcptr);
  DCfloat      (*callFloat)      (DCCallVM* vm,DCpointer funcptr);
  DCdouble     (*callDouble)     (DCCallVM* vm,DCpointer funcptr);
  DCpointer    (*callPointer)    (DCCallVM* vm,DCpointer funcptr);
};

typedef DCvoid       (DCvoidvmfunc)      (DCCallVM* vm,DCpointer funcptr); 
typedef DCbool       (DCboolvmfunc)      (DCCallVM* vn,DCpointer funcptr);
typedef DCchar       (DCcharvmfunc)      (DCCallVM* vm,DCpointer funcptr);
typedef DCshort      (DCshortvmfunc)     (DCCallVM* vm,DCpointer funcptr);
typedef DCint        (DCintvmfunc)       (DCCallVM* vm,DCpointer funcptr);
typedef DClong       (DClongvmfunc)      (DCCallVM* vm,DCpointer funcptr);
typedef DClonglong   (DClonglongvmfunc)  (DCCallVM* vm,DCpointer funcptr);
typedef DCfloat      (DCfloatvmfunc)     (DCCallVM* vm,DCpointer funcptr);
typedef DCdouble     (DCdoublevmfunc)    (DCCallVM* vm,DCpointer funcptr);
typedef DCpointer    (DCpointervmfunc)   (DCCallVM* vm,DCpointer funcptr);

#endif /* DYNCALL_CALLVM_H */

