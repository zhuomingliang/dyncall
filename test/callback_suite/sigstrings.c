#include "_auto_config.h"

const char* sigstrings[CONFIG_NSIGS] = 
{
#include "_auto_sigstrings.h"
};

const char* GetSignature(int index)
{
  return sigstrings[index];
}

