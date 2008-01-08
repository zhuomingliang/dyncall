dyncall gnu make build system Manual
Copyright 2007 Daniel Adler


configuration:
--------------
The auto-generated file 'ConfigRules' specifies the build configuration.

Two scripts, namely the unix-shell script "configure" and 
windows DOS batch file "configure.bat" generate this file.

Variables that specify the build environment:

  BUILD_OS    - "windows","linux","darwin"
  BUILD_ARCH  - "x86","ppc32","x64"
  BUILD_TOOL  - "gcc","msvc"
  BUILD_ASM   - "as", "nasm", "ml"

project configuration
---------------------
  file 'ProjectRules' included after 'ConfigRules'

site configuration:
-------------------  
  file 'SiteRules' included after 'ConfigRules'

phony targets:
--------------

  all       - build dirs and targets
  clean     - clean up targets and objects
  distclean - clean up auto-generated files too
  install   - install


building with Microsoft Visual C++ tools:
-----------------------------------------
specify the BUILD_TOOL variable in the make option

make BUILD_TOOL=msvc



build settings:

  ASM       specifies assembler; on IA32: nasm,as - others default to as

  
project settings:

TOP           points relative to source root
DIRS          directories to sub-process for targets depending on subdirs  
APP           name of application (w/o suffix of prefix) - will be built if set
DLL           name of dynamic library (w/o suffix of prefix) - will be built if set
LIBRARY       name of static library (w/o suffix of prefix) - will be built if set
MODS          specifies modules to link
LDLIBS	      link libraries
LDFLAGS       link flags
LINK_LIBPATHS paths
LINK_LIBS     libraries


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

