dyncall bsdmake build system manual
Copyright 2007 Tassilo Philipp

configuration:

Prior to running "make" the library, one should run "configure" first.
This will create the file 'ConfigRules' defining some variables identifying
the system to build the library for.

BUILD_OS   - "{Free,Net,Open,DragonFly}BSD","SunOS","Darwin"
BUILD_ARCH - "X86","PPC32","X64"
BUILD_TOOL - "GCC","PCC"
BUILD_ASM
  default: as
  on x86 and x64 arch: nasm, as


site configuration:

  file 'SiteRules' overrides 'ConfigRules'


targets:

  all       - build dirs and targets
  clean     - clean up targets and objects
  distclean - cleans targets, objects and auto-generated files


build settings:

  ASM - specifies assembler; defaults to as@@@


project settings:

TOP       points relative to source root
DIRS      directories to sub-process for targets depending on subdirs
APP       name of application (w/o suffix of prefix) - will be built if set
DLL       name of dynamic library (w/o suffix of prefix) - will be built if set
LIBRARY   name of static library (w/o suffix of prefix) - will be built if set
MODS      specifies modules to link
LDLIBS    link libraries
LDFLAGS   link flags

