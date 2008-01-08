#///////////////////////////////////////////////////
#
#	testmain stub GNUmakefile
#	Copyright 2007 Daniel Adler
#
#///////////////////////////////////////////////////


TOP	= ../..

include $(TOP)/build/gmake/prolog.gmake

LIBRARY = testmain

ifdef BUILD_OS_PSP
MODS		= main_PSP
PSPSDK		= $(shell psp-config --pspsdk-path)
CPPFLAGS	= -I$(PSPSDK)/include
else
ifdef BUILD_OS_NDS
MODS		= main_NDS
else
MODS		= main_ansic
endif
endif

include $(TOP)/build/gmake/epilog.gmake

