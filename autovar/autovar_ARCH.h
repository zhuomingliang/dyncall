#ifndef AUTOVAR_ARCH_H
#define AUTOVAR_ARCH_H

/* Check architecture. */
#if defined(_M_IX86) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) || defined(__386__) || defined(__i386)
# define ARCH_X86
#elif defined(_M_X64_) || defined(_M_AMD64) || defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) 
# define ARCH_X64
#elif defined(_M_IA64) || defined(__ia64__)
# define ARCH_IA64
#elif defined(_M_PPC) || defined(__powerpc__) || defined(__powerpc) || defined(__POWERPC__) || defined(__ppc__) || defined(__power__)
# define ARCH_PPC
#elif defined(__ppc64__) || defined(_ARCH_PPC64) || defined(__power64__)
# define ARCH_PPC64
#elif defined(__mips64__)
# define ARCH_MIPS64
#elif defined(_M_MRX000) || defined(__mips__)
# define ARCH_MIPS
#elif defined(__arm__)
# define ARCH_ARM
# if defined(__thumb__)
#   define ARCH_THUMB
# endif
#elif defined(__sh__)
# define ARCH_SH
#elif defined(__sparcv9)
# define ARCH_SPARC64
#elif defined(__sparc)
# define ARCH_SPARC
#endif

#endif /* AUTOVAR_ARCH_H */
