#include "dyncall_value.h"
#include "dyncall_value_set.h"

/* test related */

void InitEnv(); /* initializes ValueMatrix */
void InitReferenceArg(DCValue* output, char type, int argpos);
void InitReferenceResult(DCValue* output, char type);

extern DCValueSet    ValueMatrix[CONFIG_MAXARGS];
extern DCValue       Args[CONFIG_MAXARGS];
extern DCValue       Result;

/* Global Options. */
extern int OptionVerbose;


