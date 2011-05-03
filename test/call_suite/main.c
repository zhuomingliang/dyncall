#include "dyncall.h"
#include "globals.h"
#include <stdio.h>
#include <string.h>
char  linebuf[1024];
void* G_callvm;
extern funptr T[];
int main(int argc, char* argv[])
{
  init_K();
  init_T();
  G_callvm = (DCCallVM*) dcNewCallVM(4096);
  char* line;
  int   i = 1;
  FILE* f;
  f = fopen("cases.txt","r");
  for(;;) {
    int l;
    int s = 0;
    line = fgets(linebuf, sizeof(linebuf),f);
    if (!line) break;
    l = strlen(line);
    line[l-1] = '\0';
    printf("%d:%s:",i,line);
    funptr t = T[i];
    s = invoke(line,t);
    printf("%d\n",s);
    i++;
  }
  fclose(f);
  return 0;
}

