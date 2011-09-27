#ifndef AUTOVAR_CC_H
#define AUTOVAR_CC_H

/* Compiler specific defines. Do not change the order, because  */
/* some of the compilers define flags for compatible ones, too. */

#if defined(__INTEL_COMPILER)
#define CC_INTEL
#elif defined(_MSC_VER)
#define CC_MSVC
#elif defined(__GNUC__)
#define CC_GNU
#elif defined(__WATCOMC__)
#define CC_WATCOM
#elif defined(__PCC__)
#define CC_PCC
#elif defined(__SUNPRO_C)
#define CC_SUN
#endif

#endif /* AUTOVAR_CC_H */

