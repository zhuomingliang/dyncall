#include "dyncall_signature.h"

const char* SignatureSkipCallPrefix(const char* signature)
{
  if ( signature[0] == DC_SIGCHAR_CC_PREFIX ) {
    signature += 2;
  }
  return signature;
}
