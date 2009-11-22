#include <stdio.h>

void PrintUsage(const char* appName)
{
  fprintf(stdout, "usage:\n\
%s [ -v ] [ from [to] ]\n\
where\n\
  from, to: test range\n\
options\n\
  -v        verbose reports\n\
  -h        help on usage\n\
\n\
", appName);
  fflush(stdout);
}

void PrintHeader()
{
  fprintf(stdout, "case\tsignat.\tresult\n");
}

void PrintCaseInfo(int caseId, const char* signatureString)
{
  fprintf(stdout, "f%d(\t%s", caseId, signatureString);
  fflush(stdout);
}

void PrintCaseResult(int resultId)
{
  fprintf(stdout, " :%d\n", resultId);
  fflush(stdout);
}

void PrintTotalResult(int resultId)
{
  printf("result: callback_suite: %d\n", resultId);
  fflush(stdout);
}

