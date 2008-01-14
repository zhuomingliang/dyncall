// 2007-10-11


#include "test_framework.h"
#include "../../dyncall/dyncall.h"
#include "../../dyncall/dyncall_macros.h"

/* ------------------------------------------------------------------------- 
 * test: identity function calls 
 * ------------------------------------------------------------------------- */

#define DEF_FUNCS(API,NAME) \
void     API fun_##NAME##_v() { } \
DCbool   API fun_##NAME##_b(DCbool x) { return x; } \
DCint    API fun_##NAME##_i(DCint x) { return x; }  \
DCfloat  API fun_##NAME##_f(DCfloat x) { return x; } \
DCdouble API fun_##NAME##_d(DCdouble x) { return x; } \
DClonglong   API fun_##NAME##_L(DClonglong x) { return x; } \
DCpointer    API fun_##NAME##_p(DCpointer  x) { return x; }

/* __cdecl */

#ifndef DC__OS_Win32
#define __declspec(X)
#define __cdecl
#endif

DEF_FUNCS(__cdecl,c)

DC_DEFINE_TEST_FUNC_BEGIN(testCallC)
  DCCallVM* pc = dcNewCallVM(4096);
  dcMode(pc,DC_CALL_C_DEFAULT);
  /* void */
  dcReset(pc);
  dcCallVoid(pc, (DCpointer) &fun_c_v);
  /* bool */
  {
    DCbool r; 
    dcReset(pc);
    dcArgBool(pc, DC_TRUE);
    r = dcCallBool(pc, (DCpointer) &fun_c_b);
    DC_TEST(r == DC_TRUE);
  }
  return 1;
  {
    DCbool r;
    dcReset(pc);
    dcArgBool(pc, DC_FALSE);
    r = dcCallBool(pc, (DCpointer) &fun_c_b);
    DC_TEST(r == DC_FALSE);
  }
  /* int */
  {
    DCint r;
    dcReset(pc);
    dcArgInt(pc, 1234);
    r = dcCallInt(pc, (DCpointer) &fun_c_i);
    DC_TEST(r == 1234);
  }
  /* long */
  {
    DClonglong r;
    dcReset(pc);
    dcArgLongLong(pc, 0xCAFEBABEDEADC0DEULL);
    r = dcCallLongLong(pc, (DCpointer) &fun_c_L);
    DC_TEST(r == 0xCAFEBABEDEADC0DEULL);
  }
  /* float */
  {
    DCfloat r;
    dcReset(pc);
    dcArgFloat(pc, 1.234567f);
    r = dcCallFloat(pc, (DCpointer) &fun_c_f);
    DC_TEST(r == 1.234567f);
  }
  /* double */
  {
    DCdouble r;
    dcReset(pc);
    dcArgDouble(pc, 1.23456789);
    r = dcCallDouble(pc, (DCpointer) &fun_c_d);
    DC_TEST(r == 1.23456789);
  }
  /* ptr */
  {
    DCpointer r;
    dcReset(pc);
    dcArgPointer(pc, (DCpointer) &fun_c_b);
    r = dcCallPointer(pc, (DCpointer) &fun_c_p);
    DC_TEST(r == &fun_c_b);
  }
  dcFree(pc);
DC_DEFINE_TEST_FUNC_END


#ifdef DC__OS_Win32
/* win32 __stdcall */

DEF_FUNCS(__stdcall,std)

DC_DEFINE_TEST_FUNC_BEGIN(testCallStd)
  DCCallVM* pc = dcNewCallVM(4096);
  dcMode(pc,DC_CALL_C_X86_WIN32_STD);
  /* void */
  dcReset(pc);
  dcCallVoid(pc, (DCpointer) &fun_std_v);
  /* bool */
  {
    DCbool r; 
    dcReset(pc);
    dcArgBool(pc, DC_TRUE);
    r = dcCallBool(pc, (DCpointer) &fun_std_b);
    DC_TEST(r == DC_TRUE);
  }
  {
    DCbool r;
    dcReset(pc);
    dcArgBool(pc, DC_FALSE);
    r = dcCallBool(pc, (DCpointer) &fun_std_b);
    DC_TEST(r == DC_FALSE);
  }
  /* int */
  {
    DCint r;
    dcReset(pc);
    dcArgInt(pc, 1234);
    r = dcCallInt(pc, (DCpointer) &fun_std_i);
    DC_TEST(r == 1234);
  }
  /* long long */
  {
    DClonglong r;
    dcReset(pc);
    dcArgLongLong(pc, 0xCAFEBABEDEADC0DEULL);
    r = dcCallLongLong(pc, (DCpointer) &fun_std_L);
    DC_TEST(r == 0xCAFEBABEDEADC0DEULL);
  }
  /* float */
  {
    DCfloat r;
    dcReset(pc);
    dcArgFloat(pc, 1.234567f);
    r = dcCallFloat(pc, (DCpointer) &fun_std_f);
    DC_TEST(r == 1.234567f);
  }
  /* double */
  {
    DCdouble r;
    dcReset(pc);
    dcArgDouble(pc, 1.23456789);
    r = dcCallDouble(pc, (DCpointer) &fun_std_d);
    DC_TEST(r == 1.23456789);
  }
  /* ptr */
  {
    DCpointer r;
    dcReset(pc);
    dcArgPointer(pc, (DCpointer) &fun_c_b);
    r = dcCallPointer(pc, (DCpointer) &fun_std_p);
    DC_TEST(r == &fun_c_b);
  }
  dcFree(pc);
DC_DEFINE_TEST_FUNC_END

#endif

#ifdef DC__OS_Win32
/* win32 __fastcall */

DEF_FUNCS(__fastcall,fast)

DC_DEFINE_TEST_FUNC_BEGIN(testCallFast)
  DCCallVM* pc = dcNewCallVM(4096);
  dcMode(pc,DC_CALL_C_X86_WIN32_FAST_MS);
  /* void */
  dcReset(pc);
  dcCallVoid(pc, (DCpointer) &fun_fast_v);
  /* bool */
  {
    DCbool r; 
    dcReset(pc);
    dcArgBool(pc, DC_TRUE);
    r = dcCallBool(pc, (DCpointer) &fun_fast_b);
    DC_TEST(r == DC_TRUE);
  }
  {
    DCbool r;
    dcReset(pc);
    dcArgBool(pc, DC_FALSE);
    r = dcCallBool(pc, (DCpointer) &fun_fast_b);
    DC_TEST(r == DC_FALSE);
  }
  /* int */
  {
    DCint r;
    dcReset(pc);
    dcArgInt(pc, 1234);
    r = dcCallInt(pc, (DCpointer) &fun_fast_i);
    DC_TEST(r == 1234);
  }
  /* long long */
  {
    DClonglong r;
    dcReset(pc);
    dcArgLongLong(pc, 0xCAFEBABEDEADC0DEULL);
    r = dcCallLongLong(pc, (DCpointer) &fun_fast_L);
    DC_TEST(r == 0xCAFEBABEDEADC0DEULL);
  }
  /* float */
  {
    DCfloat r;
    dcReset(pc);
    dcArgFloat(pc, 1.234567f);
    r = dcCallFloat(pc, (DCpointer) &fun_fast_f);
    DC_TEST(r == 1.234567f);
  }
  /* double */
  {
    DCdouble r;
    dcReset(pc);
    dcArgDouble(pc, 1.23456789);
    r = dcCallDouble(pc, (DCpointer) &fun_fast_d);
    DC_TEST(r == 1.23456789);
  }
  /* ptr */
  {
    DCpointer r;
    dcReset(pc);
    dcArgPointer(pc, (DCpointer) &fun_c_b);
    r = dcCallPointer(pc, (DCpointer) &fun_fast_p);
    DC_TEST(r == &fun_c_b);
  }
  dcFree(pc);
DC_DEFINE_TEST_FUNC_END
#endif

/* ------------------------------------------------------------------------- 
 * test: identity this calls 
 * ------------------------------------------------------------------------- */

union ValueUnion
{
  DCbool   b;
  DCint    i;
  DClonglong L;
  DCfloat  f;
  DCdouble d;
  DCpointer    p;
};

class Value
{
public:
  virtual void     __cdecl setBool(DCbool x) { mValue.b = x; }
  virtual DCbool   __cdecl getBool() { return mValue.b; }
  virtual void     __cdecl setInt(DCint x) { mValue.i = x; }
  virtual DCint    __cdecl getInt() { return mValue.i; }
  virtual void     __cdecl setLongLong(DClonglong x) { mValue.L = x; }
  virtual DClonglong   __cdecl getLongLong() { return mValue.L; }
  virtual void     __cdecl setFloat(DCfloat x) { mValue.f = x; }
  virtual DCfloat  __cdecl getFloat() { return mValue.f; }
  virtual void     __cdecl setDouble(DCdouble x) { mValue.d = x; }
  virtual DCdouble __cdecl getDouble() { return mValue.d; }
  virtual void     __cdecl setPtr(DCpointer x) { mValue.p = x; }
  virtual DCpointer    __cdecl getPtr() { return mValue.p; }
private:
  ValueUnion mValue;
};

class ValueMS
{
public:
  virtual void     setBool(DCbool x) { mValue.b = x; }
  virtual DCbool   getBool() { return mValue.b; }
  virtual void     setInt(DCint x) { mValue.i = x; }
  virtual DCint    getInt() { return mValue.i; }
  virtual void     setLongLong(DClonglong x) { mValue.L = x; }
  virtual DClonglong   getLongLong() { return mValue.L; }
  virtual void     setFloat(DCfloat x) { mValue.f = x; }
  virtual DCfloat  getFloat() { return mValue.f; }
  virtual void     setDouble(DCdouble x) { mValue.d = x; }
  virtual DCdouble getDouble() { return mValue.d; }
  virtual void     setPtr(DCpointer x) { mValue.p = x; }
  virtual DCpointer    getPtr() { return mValue.p; }
private:
  ValueUnion mValue;
};

template<typename T>
void testCallValue(DCCallVM* pc)
{
  T o;
  T* pThis = &o;
  DCpointer* vtbl =  *( (DCpointer**) pThis );
  
  /* set/get bool (TRUE) */

  dcReset(pc);
  dcArgPointer(pc, pThis);
  dcArgBool(pc,DC_TRUE);
  dcCallVoid(pc, vtbl[0] );
  dcReset(pc);
  dcArgPointer(pc, pThis);
  DC_TEST( dcCallBool(pc, vtbl[1] ) == DC_TRUE );

  /* set/get bool (FALSE) */

  dcReset(pc);
  dcArgPointer(pc, pThis);
  dcArgBool(pc,DC_FALSE);
  dcCallVoid(pc, vtbl[0] );
  dcReset(pc);
  dcArgPointer(pc, pThis);
  DC_TEST( dcCallBool(pc, vtbl[1] ) == DC_FALSE );

  /* set/get int */

  dcReset(pc);
  dcArgPointer(pc, pThis);
  dcArgInt(pc,1234);
  dcCallVoid(pc, vtbl[2] );
  dcReset(pc);
  dcArgPointer(pc, pThis);
  DC_TEST( dcCallInt(pc, vtbl[3] ) == 1234 );

  /* set/get long */

  dcReset(pc);
  dcArgPointer(pc, pThis);
  dcArgLongLong(pc,0xCAFEBABEDEADC0DEULL);
  dcCallVoid(pc, vtbl[4] );
  dcReset(pc);
  dcArgPointer(pc, pThis);
  DC_TEST( dcCallLongLong(pc, vtbl[5] ) == 0xCAFEBABEDEADC0DEULL );

  /* set/get float */

  dcReset(pc);
  dcArgPointer(pc, pThis);
  dcArgFloat(pc,1.2345f);
  dcCallVoid(pc, vtbl[6] );
  dcReset(pc);
  dcArgPointer(pc, pThis);
  DC_TEST( dcCallFloat(pc, vtbl[7] ) == 1.2345f );

  /* set/get double */

  dcReset(pc);
  dcArgPointer(pc, pThis);
  dcArgDouble(pc,1.23456789);
  dcCallVoid(pc, vtbl[8] );
  dcReset(pc);
  dcArgPointer(pc, pThis);
  DC_TEST( dcCallDouble(pc, vtbl[9] ) == 1.23456789 );

  /* set/get pointer */

  dcReset(pc);
  dcArgPointer(pc, pThis);
  dcArgPointer(pc, (DCpointer) 0xCAFEBABE );
  dcCallVoid(pc, vtbl[10] );
  dcReset(pc);
  dcArgPointer(pc, pThis);
  DC_TEST( dcCallPointer(pc, vtbl[11] ) == ( (DCpointer) 0xCAFEBABE ) );

  dcFree(pc);
}

#ifdef DC__OS_Win32
DC_DEFINE_TEST_FUNC_BEGIN(testCallThisMS)
  DCCallVM* pc = dcNewCallVM(4096);
  dcMode(pc,DC_CALL_C_X86_WIN32_THIS_MS);
  testCallValue<ValueMS>(pc); 
DC_DEFINE_TEST_FUNC_END
#endif

DC_DEFINE_TEST_FUNC_BEGIN(testCallThisC)
  DCCallVM* pc = dcNewCallVM(4096);
  testCallValue<Value>(pc); 
DC_DEFINE_TEST_FUNC_END

DC_DEFINE_TEST_FUNC_BEGIN(testCallThis)

  DCCallVM* pc = dcNewCallVM(4096);
#ifdef _MSC_VER
  dcMode(pc,DC_CALL_C_X86_WIN32_THIS_MS);
#else
  dcMode(pc,DC_CALL_C_X86_WIN32_THIS_GNU);
#endif

  Value* pThis = new Value();
  DCpointer* vtbl =  *( (DCpointer**) pThis );
  
  /* set/get bool (TRUE) */

  dcReset(pc);
  dcArgPointer(pc, pThis);
  dcArgBool(pc,DC_TRUE);
  dcCallVoid(pc, vtbl[0] );
  dcReset(pc);
  dcArgPointer(pc, pThis);
  DC_TEST( dcCallBool(pc, vtbl[1] ) == DC_TRUE );

  /* set/get bool (FALSE) */

  dcReset(pc);
  dcArgPointer(pc, pThis);
  dcArgBool(pc,DC_FALSE);
  dcCallVoid(pc, vtbl[0] );
  dcReset(pc);
  dcArgPointer(pc, pThis);
  DC_TEST( dcCallBool(pc, vtbl[1] ) == DC_FALSE );

  /* set/get int */

  dcReset(pc);
  dcArgPointer(pc, pThis);
  dcArgInt(pc,1234);
  dcCallVoid(pc, vtbl[2] );
  dcReset(pc);
  dcArgPointer(pc, pThis);
  DC_TEST( dcCallInt(pc, vtbl[3] ) == 1234 );

  /* set/get long */

  dcReset(pc);
  dcArgPointer(pc, pThis);
  dcArgLongLong(pc,0xCAFEBABEDEADC0DEULL);
  dcCallVoid(pc, vtbl[4] );
  dcReset(pc);
  dcArgPointer(pc, pThis);
  DC_TEST( dcCallLongLong(pc, vtbl[5] ) == 0xCAFEBABEDEADC0DEULL );

  /* set/get float */

  dcReset(pc);
  dcArgPointer(pc, pThis);
  dcArgFloat(pc,1.2345f);
  dcCallVoid(pc, vtbl[6] );
  dcReset(pc);
  dcArgPointer(pc, pThis);
  DC_TEST( dcCallFloat(pc, vtbl[7] ) == 1.2345f );

  /* set/get double */

  dcReset(pc);
  dcArgPointer(pc, pThis);
  dcArgDouble(pc,1.23456789);
  dcCallVoid(pc, vtbl[8] );
  dcReset(pc);
  dcArgPointer(pc, pThis);
  DC_TEST( dcCallDouble(pc, vtbl[9] ) == 1.23456789 );

  /* set/get pointer */

  dcReset(pc);
  dcArgPointer(pc, pThis);
  dcArgPointer(pc, (DCpointer) 0xCAFEBABE );
  dcCallVoid(pc, vtbl[10] );
  dcReset(pc);
  dcArgPointer(pc, pThis);
  DC_TEST( dcCallPointer(pc, vtbl[11] ) == ( (DCpointer) 0xCAFEBABE ) );


  dcFree(pc);

DC_DEFINE_TEST_FUNC_END

#include <cstdio>

extern "C" {

int main(int argc, char* argv[])
{
  int b = TRUE;
  
  b = b && testCallC();
  printf("C:%d\n",b);
  b = b && testCallThisC();
  printf("ThisC:%d\n",b);
#ifdef DC__OS_Win32
#ifdef _MSC_VER
  b = b && testCallThisMS();
  printf("ThisMS:%d\n",b);
#endif
  b = b && testCallStd();
  printf("Std:%d\n",b);
  b = b && testCallFast();
  printf("Fast:%d\n",b);
#endif
  printf("ok\n");
  return b;
}

}  // extern "C"

