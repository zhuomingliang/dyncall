#///////////////////////////////////////////////////
#
#	gmake makefile
#	Copyright 2007 Daniel Adler
#	GNUmakefile
#
#///////////////////////////////////////////////////


TOP		= ../..

include $(TOP)/buildsys/gmake/prolog.gmake

APP		= ellipsis
AUTOS		= config.h case.h
MODS		= ellipsis main
CPPFLAGS	= -I$(TOP)/dyncall
CXX_EXCEPTIONS	= 0
CXX_RTTI	= 0
LINK_PATHS	= $(TOP)/dyncall/$(BUILD_DIR)
LINK_LIBS       = dyncall_s 

include $(TOP)/buildsys/gmake/epilog.gmake

.PHONY: config
config: config.h case.h

config.h case.h: mkcase.py
	python mkcase.py >case.h 2>config.h

ifdef BUILD_TOOL_gcc
LINK_LIBS	+= m
endif

