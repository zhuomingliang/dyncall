#///////////////////////////////////////////////////
#
#	gmake makefile
#	Copyright 2007 Daniel Adler
#	GNUmakefile
#
#///////////////////////////////////////////////////


TOP		= ../..

APP		= suite
AUTOS		= config.h case.h
MODS		= ellipse main
CPPFLAGS	= -I$(TOP)/dyncall
LINK_LIBPATHS   = $(TOP)/dyncall/$(BUILD_DIR)
LINK_LIBS       = dyncall_s 

include $(TOP)/test/testmain/GNUmakerules

.PHONY: config
config: config.h case.h

config.h case.h: mkcase.py
	python mkcase.py >case.h 2>config.h

ifdef BUILD_TOOL_gcc
LINK_LIBS	+= m
endif

