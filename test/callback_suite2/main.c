#include <assert.h>
#include <stdio.h>
#include "_auto_config.h"

/* test one case, returns error code */
int DoTest(int id);

#define MAX_ERRORS 1

/* capture total results for failure (0) and success (1) */
int totalErrorCodes[MAX_ERRORS];

void test_range(int from, int to)
{
  int i;
  for(i = from ; i <= to ; ++i )
  {
    int status = DoTest(i);
    totalErrorCodes[status]++;
  }
}

void InitEnv();

int main(int argc, char* argv[] )
{
  InitEnv();

  int from = 1;
  int to = CONFIG_NSIGS;
  int n = (to - from) + 1;
  
  if (argc == 2)
    from = to = atoi(argv[1]);
  else if (argc == 3) {
    from = atoi(argv[1]);
    to   = atoi(argv[2]);
  }


  assert(from <= to);
  assert(from > 0);
  assert(to   <= CONFIG_NSIGS);

  test_range(from, to);

  printf("result:%d\n", (totalErrorCodes[1] == n) ? 1 : 0 );

  return 0;
}

