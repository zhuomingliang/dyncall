/*

 Copyright (c) 2007-2010 Daniel Adler <dadler@uni-goettingen.de>, 
                         Tassilo Philipp <tphilipp@potion-studios.com>

 Permission to use, copy, modify, and distribute this software for any
 purpose with or without fee is hereby granted, provided that the above
 copyright notice and this permission notice appear in all copies.

 THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

*/


#include "../common/platformInit.h"
#include "test_framework.h"
#include "../../dyncall/dyncall.h"
#include <stdio.h>

/* ------------------------------------------------------------------------- 
 * test: identity function calls 
 * ------------------------------------------------------------------------- */

#define DEF_FUNCS(API,NAME) \
void       API fun_##NAME##_v()             {           } \
DCbool     API fun_##NAME##_b(DCbool x)     { return x; } \
DCint      API fun_##NAME##_i(DCint x)      { return x; } \
DClong     API fun_##NAME##_j(DClong x)     { return x; } \
DClonglong API fun_##NAME##_l(DClonglong x) { return x; } \
DCfloat    API fun_##NAME##_f(DCfloat x)    { return x; } \
DCdouble   API fun_##NAME##_d(DCdouble x)   { return x; } \
DCpointer  API fun_##NAME##_p(DCpointer  x) { return x; }

/* __cdecl */

#if !defined(DC__OS_Win32)
#  define __declspec(X)
#  define __cdecl
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
    DClong r;
    dcReset(pc);
    dcArgLong(pc, 0xCAFEBABEUL);
    r = dcCallLong(pc, (DCpointer) &fun_c_j);
    DC_TEST(r == (DClong)0xCAFEBABEUL);
  }
  /* long long */
  {
    DClonglong r;
    dcReset(pc);
    dcArgLongLong(pc, 0xCAFEBABEDEADC0DEULL);
    r = dcCallLongLong(pc, (DCpointer) &fun_c_l);
    DC_TEST(r == (DClonglong)0xCAFEBABEDEADC0DEULL);
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
  /* long */
  {
    DClong r;
    dcReset(pc);
    dcArgLong(pc, 0xCAFEBABEUL);
    r = dcCallLong(pc, (DCpointer) &fun_std_j);
    DC_TEST(r == 0xCAFEBABEUL);
  }
  /* long long */
  {
    DClonglong r;
    dcReset(pc);
    dcArgLongLong(pc, 0xCAFEBABEDEADC0DEULL);
    r = dcCallLongLong(pc, (DCpointer) &fun_std_l);
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
#ifdef DC__C_GNU
  dcMode(pc,DC_CALL_C_X86_WIN32_FAST_GNU);
#else
  dcMode(pc,DC_CALL_C_X86_WIN32_FAST_MS);
#endif
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
  /* long */
  {
    DClong r;
    dcReset(pc);
    dcArgLong(pc, 0xCAFEBABEUL);
    r = dcCallLong(pc, (DCpointer) &fun_fast_j);
    DC_TEST(r == 0xCAFEBABEUL);
  }
  /* long long */
  {
    DClonglong r;
    dcReset(pc);
    dcArgLongLong(pc, 0xCAFEBABEDEADC0DEULL);
    r = dcCallLongLong(pc, (DCpointer) &fun_fast_l);
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


int main(int argc, char* argv[])
{
  dcTest_initPlatform();

  int b = TRUE;
  
  b = b && testCallC();
  printf("C:%d\n",b);

#if defined(DC__OS_Win32)
  
  b = b && testCallStd();
  printf("Std:%d\n",b);

  b = b && testCallFast();
#ifdef DC__C_GNU
  printf("FastGNU:%d\n",b);
#else
  printf("FastMS:%d\n",b);
#endif

#endif

  printf("result: plain: %d\n", b);

  dcTest_deInitPlatform();

  return b;
}

