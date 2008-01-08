#///////////////////////////////////////////////////
#
#	gmake makefile
#	Copyright 2007 Daniel Adler
#	GNUmakefile
#
#///////////////////////////////////////////////////


TOP		= ../..

APP		= suite2
AUTOS		= case.h
MODS		= case main
CPPFLAGS	= -I$(TOP)/dyncall
CXXFLAGS	= -fno-exceptions -fno-rtti
LINK_LIBPATHS   = $(TOP)/dyncall/$(BUILD_DIR) 
LINK_LIBS       = dyncall_s testmain_s m

include $(TOP)/test/testmain/GNUmakerules

$(AUTOS): mkcase.py
	python mkcase.py >case.h 2>config.h

config: case.h
case.o: case.cpp case.h config.h
case.h: design.cfg
design.cfg: rand.py
	python rand.py >$@

