portasm - a toolkit for writing portable generic sources in assembler

Supported Architectures and Tool-chains:

x86
  gas, apple's as, masm
x64
  gas, apple's as, masm
ppc
  gas, apple's as
arm
  gas, apple's as


Usage:

include portasm-ARCH.S and then use macros for implementation of
procedures:

Macros:

BEGIN_ASM and END_ASM
BEGIN_PROC and END_PROC
GLOBAL


