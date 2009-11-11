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
    printf("%d:%d\n", i, status );
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

  assert(n <= CONFIG_NSIGS);

  test_range(from, to);

  printf("result:", (totalErrorCodes[0] == n) ? 1 : 0 );

  return 0;
}

