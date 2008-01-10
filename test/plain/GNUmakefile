#///////////////////////////////////////////////////
#
#	gmake makefile
#	Copyright 2007 Daniel Adler
#	GNUmakefile
#
#///////////////////////////////////////////////////


TOP		= ../..

include $(TOP)/buildsys/gmake/prolog.gmake

APP		= test
MODS		= test_main
CPPFLAGS	= -I$(TOP)/dyncall
LINK_PATHS	= $(TOP)/dyncall/$(BUILD_DIR)
LINK_LIBS       = dyncall_s
LINK		= c++

include $(TOP)/buildsys/gmake/epilog.gmake

