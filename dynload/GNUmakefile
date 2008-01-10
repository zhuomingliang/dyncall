#///////////////////////////////////////////////////
#
#	gnu make makefile
#	Copyright 2007 Daniel Adler
#	GNUmakefile
#
#///////////////////////////////////////////////////

TOP=..

include $(TOP)/build/gmake/prolog.gmake

LIBRARY=dynload
INSTALL_HEADERS=dynload.h
INSTALL_LIB=1

ifdef BUILD_OS_windows
MODS += dynload_win32
else

ifdef BUILD_OS_linux
MODS += dynload_unix
endif

endif

include $(TOP)/build/gmake/epilog.gmake

