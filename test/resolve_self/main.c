#include "../../dynload/dynload.h"
#include <assert.h>

double add_dd_d(double x, double y) 
{
  return x+y;
}

int main(int argc, char* argv[])
{
  void* address;
  double result;
  DLLib* pLib = dlLoadLibrary(NULL);
  assert(pLib);

  address = dlFindSymbol(pLib, "add_dd_d");
  assert(address);
  result = ( (double (*) (double,double) ) address ) (20.0, 3.0);
  assert(result == 23);
  return 0;
}
