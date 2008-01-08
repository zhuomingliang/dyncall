#///////////////////////////////////////////////////
#
#	gmake makefile
#	Copyright 2007 Daniel Adler
#	GNUmakefile
#
#///////////////////////////////////////////////////


TOP		= ../..

APP		= suite
MODS		= case main
AUTOS		= config.h case.h
CPPFLAGS	= -I$(TOP)/dyncall
#CXXFLAGS	= -fno-exceptions -fno-rtti
LINK_LIBPATHS   = $(TOP)/dyncall/$(BUILD_DIR) 
LINK_LIBS       = dyncall_s m

include $(TOP)/test/testmain/GNUmakerules

.PHONY: config 
config: case.h config.h

config.h case.h: mkcase.py
	python mkcase.py >case.h 2>config.h

