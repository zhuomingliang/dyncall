dyncall gnu make build system Manual
Copyright 2007 Daniel Adler


configuration:
--------------
The auto-generated file 'ConfigRules' specifies the build configuration.

Two scripts, namely the unix-shell script "configure" and 
windows DOS batch file "configure.bat" will write out this file.


Variables that specify the build environment:

  BUILD_OS    - "Windows","Linux","Darwin"
  BUILD_ARCH  - "X86","PPC32","X64"
  BUILD_TOOL  - "GCC","MSVC"
  BUILD_ASM   
    on x86 arch: nasm,as


site configuration:
-------------------  
  file 'SiteRules' included after 'ConfigRules'


targets:
--------

  all       - build dirs and targets
  clean     - clean up targets and objects
  distclean - clean up auto-generated files too


building with Microsoft Visual C++ tools:
-----------------------------------------
specify the BUILD_TOOL variable in the make option

make BUILD_TOOL=MSVC 



build settings:

  ASM       specifies assembler; on IA32: nasm,as - others default to as

  
project settings:

TOP       points relative to source root
DIRS      directories to sub-process for targets depending on subdirs  
APP       name of application (w/o suffix of prefix) - will be built if set
DLL       name of dynamic library (w/o suffix of prefix) - will be built if set
LIBRARY   name of static library (w/o suffix of prefix) - will be built if set
MODS      specifies modules to link
LDLIBS	  link libraries
LDFLAGS   link flags


Nameclashes:

LIB - on windows


TODO
- separate build configuration file

  the build system currently includes /ConfigRules and /SiteRules -
  it would be nice to have a separate directory for e.g. compiling with
  a "BuildRules" that cover the build job.

  idea:
  mirror the directory tree of Makefiles into a separate build directory.
  put a /BuildRules on top setting e.g. BUILD_TOOLS and let it be included
  in the makefile prolog right after SiteRules.

