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

ifdef BUILD_OS_WINDOWS
MODS += dynload_win32
else

ifdef ($(BUILD_UNIX),1)
MODS += dynload_unix
endif

endif

include $(TOP)/build/gmake/epilog.gmake

