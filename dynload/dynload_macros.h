#ifndef DYNLOAD_MACROS_H
#define DYNLOAD_MACROS_H

#if defined(__ELF__)
# define DL__BinaryFormat_elf
# if defined(__LP64__) || defined(_LP64)
#   define DL__BinaryFormat_elf64
# else
#   define DL__BinaryFormat_elf32
# endif
#endif

#endif // DYNLOAD_MACROS_H

