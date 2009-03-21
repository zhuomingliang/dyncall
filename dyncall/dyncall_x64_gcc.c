#include "dyncall_call_x64.h"
#if !defined(DC__C_GNU) || !defined(DC__Arch_AMD64)
#error source needs to be compiled with GCC targeting x64 architecture
#endif

void dcCall_x64(DCsize stacksize, DCpointer stackdata, DCpointer regdata_i, DCpointer regdata_f, DCpointer target)
{
__asm__ __volatile__("\n\
  push	%rbx 		/* Preserve rbx and store pointer to function in it. */\n\
  mov	%r8 , %rbx      \n\
                        \n\
  movsd  0(%rcx), %xmm0	/* Copy first 8 floats to xmm0-xmm7 (this makes rcx free to use). */\n\
  movsd  8(%rcx), %xmm1 \n\
  movsd 16(%rcx), %xmm2 \n\
  movsd 24(%rcx), %xmm3 \n\
  movsd 32(%rcx), %xmm4 \n\
  movsd 40(%rcx), %xmm5 \n\
  movsd 48(%rcx), %xmm6 \n\
  movsd 56(%rcx), %xmm7 /* 'movsd' is a 128-bit media instruction here, not a string operation */\n\
                        \n\
  sub   %rdi, %rsp	/* Setup stack frame by subtracting the size of the arguments. */\n\
                        \n\
  mov   %rdi, %rax	/* Align stack. */\n\
  add     $8, %rax      \n\
  and    $15, %rax      \n\
  sub   %rax, %rsp      \n\
                        \n\
  mov   %rdi, %rcx	/* Store number of bytes to copy to stack in rcx (for rep movsb). */\n\
  mov   %rsp, %rdi	/* Store pointer to beginning of stack arguments in rdi (for rep movsb). */\n\
                        \n\
  rep movsb	        /* @@@ should be optimized (e.g. movq) */\n\
                        \n\
  mov    0(%rdx), %rdi  /* Copy first six int/pointer arguments to rdi, rsi, rdx, rcx, r8, r9. */\n\
  mov    8(%rdx), %rsi  \n\
  mov   24(%rdx), %rcx  \n\
  mov   32(%rdx), %r8   \n\
  mov   40(%rdx), %r9   \n\
  mov   16(%rdx), %rdx  /* Set rdx last to not overwrite it to soon. */\n\
                        \n\
  mov     $8, %al	/* Put upper bound of number of used xmm registers in al. */\n\
  call  *%rbx	        /* Invoke function. */\n\
                        \n\
  mov   %rbp, %rsp	/* Restore stack pointer (such that we can pop the preserved values). */\n\
                        \n\
  mov   -8(%rbp), %rbx  \n\
\n\
");
}

