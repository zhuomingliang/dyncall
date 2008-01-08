dyncall make based build system
-------------------------------

The build system tries to roughly get BSD make and GNU make under some basic structure.
Each subproject should have two files:
	GNUmakefile (for GNU make)
	BSDmakefile (for BSD make)

These makefiles should look like the following pseudocode - adapt styles for the different
make systems


-- snip ---->

TOP = <relative path back to top directory>
INCLUDE "$(TOP)/{g,bsd}make/build/prolog.{g,bsd}make"

  .. BUILD_OS_XXX, BUILD_ARCH_XXX have been set    ..
  .. project settings e.g. MODS, APP, DLL, LIBRARY ..


INCLUDE "$(TOP)/{g,bsd}make/build/prolog.{g,bsd}make"

<---- snap --



See {g,bsd}make/README.txt for details about a given make system.
