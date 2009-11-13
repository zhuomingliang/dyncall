#include "dyncall_value.h"
#include "dyncall_value_set.h"

/* test related */

void InitEnv(); /* initializes ValueMatrix */


/* function of type and position */
void GetReferenceArg(DCValue* output, char type, int argpos);
/* function of type (position = -1) */
void GetReferenceResult(DCValue* output, char type);

extern DCValueSet    ValueMatrix[CONFIG_MAXARGS];
extern DCValue       Args[CONFIG_MAXARGS];
extern DCValue       Result;

/* Global Options. */
extern int OptionVerbose;


