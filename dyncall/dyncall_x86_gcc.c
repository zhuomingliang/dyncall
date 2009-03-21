#include "dyncall_call_x86.h"
#if !defined(DC__C_GNU) || !defined(DC__Arch_Intel_x86)
#error this source requires a GCC compiler AND x86 architecture
#endif

void dcCall_x86_cdecl(DCpointer funptr, DCpointer args, DCsize size)
{
  asm volatile("\n\
      push %esi               /* save esi, edi */               \n\
      push %edi                                                 \n\
                                                                \n\
      mov  12(%ebp),%esi      /* esi = pointer on args */       \n\
      mov  16(%ebp),%ecx      /* ecx = size */                  \n\
                                                                \n\
      sub  %ecx, %esp         /* cdecl call: allocate 'size' bytes on stack */\n\
      mov  %esp, %edi         /* edi = stack args */            \n\
                                                                \n\
      shr  $0x2, %ecx 		          /* ecx = number of DWORDs */      \n\
      rep movsd               /* copy DWORDs */                 \n\
                                                                \n\
      call *8(%ebp)            /* call function */               \n\
                                                                \n\
      add  16(%ebp),%esp      /* cdecl call: cleanup stack */   \n\
                                                                \n\
      pop  %edi               /* restore edi, esi */            \n\
      pop  %esi                                                 \n\                                                                \n\
");
}

void dcCall_x86_win32_std    (DCpointer target, DCpointer stackdata, DCsize size)  { }
void dcCall_x86_win32_fast   (DCpointer target, DCpointer stackdata, DCsize size)  { }
void dcCall_x86_win32_msthis (DCpointer target, DCpointer stackdata, DCsize size)  { }
