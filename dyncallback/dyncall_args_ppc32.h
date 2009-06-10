#ifndef DYNCALLBACK_ARGS_PPC32_H
#define DYNCALLBACK_ARGS_PPC32_H

#include "dyncall_args.h"

struct DCArgs
{
  int*   stack_ptr;
  int    ireg_count;
  int    freg_count;
  int    ireg_data[8];
  double freg_data[11];
};

#endif /* DYNCALLBACK_ARGS_PPC32_H */

