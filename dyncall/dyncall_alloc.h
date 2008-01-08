#ifndef DYNCALL_ALLOC_H
#define DYNCALL_ALLOC_H

/* dyncall memory allocation 
 * Copyright 2007 Daniel Adler.
 * uses stdlib malloc/free
 **/

#ifndef dcAllocMem
#include <stdlib.h>
#define dcAllocMem malloc
#endif

#ifndef dcFreeMem
#define dcFreeMem  free
#endif

#endif /* DYNCALL_ALLOC_H */

