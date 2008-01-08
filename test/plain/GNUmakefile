#///////////////////////////////////////////////////
#
#	gmake makefile
#	Copyright 2007 Daniel Adler
#	GNUmakefile
#
#///////////////////////////////////////////////////


TOP		= ../..

APP		= test
MODS		= test_main
CPPFLAGS	= -I$(TOP)/dyncall
LINK_LIBPATHS   = $(TOP)/dyncall/$(BUILD_DIR)
LINK_LIBS       = dyncall_s 

include $(TOP)/test/testmain/GNUmakerules

ifdef BUILD_TOOL_gcc
LINK_LIBS	+= stdc++
endif

ifdef BUILD_TOOL_psp
LINK_LIBS	+= c
endif

