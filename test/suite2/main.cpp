#include "../../dyncall/dyncall.h"
#include "config.h"
#include "../../dyncall/dyncall_value.h"
#include "funcinfo.h"
#include <stdlib.h>
#include <stdio.h>

int   getId();
DCpointer getFunc(int x);
DCValue* getArg(int pos);


typedef double precise;


DCbool    valueBool[MAXARGS];
DCchar    valueChar[MAXARGS];
DCshort    valueShort[MAXARGS];
DCint     valueInt[MAXARGS];
DClong     valueLong[MAXARGS];
DClonglong    valueLongLong[MAXARGS];
DCdouble  valueDouble[MAXARGS];
DCpointer     valuePointer[MAXARGS];
DCfloat   valueFloat[MAXARGS];


void clearValues();

void init()
{
  for (int i = 0 ; i < MAXARGS ; ++i ) {

    valueBool[i] = DCbool( (i % 1) ? DC_TRUE : DC_FALSE );
    valueChar[i] = DCchar(i);
    valueShort[i] = DCshort(i);
    valueInt[i] = DCint(i);
    valueLong[i] = DClong(i);
    valueLongLong[i] = DClonglong(i);
    valueDouble[i] = DCdouble(i);
    valuePointer[i] = DCpointer(i);
    valueFloat[i] = DCfloat(i);
  }
}


bool test(int x)
{
  bool r = true;
  clearValues();

  DCCallVM* pCall;

  funcinfo* fi = &gFuncInfos[x];

  const DCsigchar* sig = &fi->sig[2];
  const DCsigchar* ptr = sig;
  DCsigchar ch;
  int pos;
 
  pos = 0;

  pCall = dcNewCallVM(4096);
 
  while ( (ch=*ptr++) != '\0' ) {
    switch(ch) {
      case DC_SIGCHAR_BOOL: dcArgBool( pCall, valueBool[pos] ); break;
      case DC_SIGCHAR_CHAR: dcArgChar( pCall, valueChar[pos] ); break;
      case DC_SIGCHAR_SHORT: dcArgShort( pCall, valueShort[pos] ); break;
      case DC_SIGCHAR_INT: dcArgInt( pCall, valueInt[pos] ); break;
      case DC_SIGCHAR_LONG: dcArgLong( pCall, valueLong[pos] ); break;
      case DC_SIGCHAR_LONGLONG: dcArgLongLong( pCall, valueLongLong[pos] ); break;
      case DC_SIGCHAR_FLOAT: dcArgFloat( pCall, valueFloat[pos] ); break;
      case DC_SIGCHAR_DOUBLE: dcArgDouble( pCall, valueDouble[pos] ); break;
      case DC_SIGCHAR_POINTER: dcArgPointer( pCall, valuePointer[pos] ); break;
    }
    ++pos;
  }

  dcCallVoid( pCall, fi->funcptr );

 
  if ( getId() == x ) { 

    ptr = sig;
    pos = 0;
    while( ( ch=*ptr++ ) != '\0' ) {

      switch(ch) {
        case DC_SIGCHAR_BOOL: if ( getArg(pos)->B != valueBool  [pos] ) r = false; break;
        case DC_SIGCHAR_CHAR: if ( getArg(pos)->c != valueChar  [pos] ) r = false; break;
        case DC_SIGCHAR_SHORT: if ( getArg(pos)->s != valueShort  [pos] ) r = false; break;
        case DC_SIGCHAR_INT: if ( getArg(pos)->i != valueInt   [pos] ) r = false; break;
        case DC_SIGCHAR_LONG: if ( getArg(pos)->l != valueLong [pos] ) r = false; break;
        case DC_SIGCHAR_LONGLONG: if ( getArg(pos)->L != valueLongLong  [pos] ) r = false; break;
        case DC_SIGCHAR_FLOAT: if ( getArg(pos)->f != valueFloat [pos] ) r = false; break;
        case DC_SIGCHAR_DOUBLE: if ( getArg(pos)->d != valueDouble[pos] ) r = false; break;
        case DC_SIGCHAR_POINTER: if ( getArg(pos)->p != valuePointer   [pos] ) r = false; break;
      }
      ++pos;
    }

  } else {
    r = false;
  }

  printf("%d-%s:%d\n", x, sig, r);
   
  dcFree(pCall);

  return r;
}


bool run_range(int from, int to)
{
  bool r = true;
  for (int i = from ; i < to ; ++i )
    r &= test(i);
  return r;
}

extern "C" {

int test_main(int argc, char* argv[])
{
  bool success = false;
  init();
  if (argc == 2) {
    int index = atoi(argv[1]);
    success = run_range( index, index+1 ); 
  } else if (argc == 3) {
    int from = atoi(argv[1]);
    int to   = atoi(argv[2])+1;
    success = run_range(from,to);
  } else {
    success = run_range(0,NCASES);
  }
  return (success) ? 0 : -1;
}

}  // extern "C"

