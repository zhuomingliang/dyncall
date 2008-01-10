#///////////////////////////////////////////////////
#
#	gmake makefile
#	Copyright 2007 Daniel Adler
#	GNUmakefile
#
#///////////////////////////////////////////////////


TOP		= ../..

include $(TOP)/buildsys/gmake/prolog.gmake

APP		= suite
MODS		= case main
CPPFLAGS	= -I$(TOP)/dyncall
CXX_EXCEPTIONS 	= 0
CXX_RTTI	= 0
LINK_PATHS	= $(TOP)/dyncall/$(BUILD_DIR) 
LINK_LIBS       = dyncall_s 

include $(TOP)/buildsys/gmake/epilog.gmake

# AUTOS		= config.h case.h
.PHONY: config 
config: case.h config.h

config.h case.h: mkcase.py
	python mkcase.py >case.h 2>config.h

