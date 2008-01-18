#///////////////////////////////////////////////////
#
#	gmake makefile
#	Copyright 2007 Daniel Adler
#	GNUmakefile
#
#///////////////////////////////////////////////////


TOP		= ../..

include $(TOP)/buildsys/gmake/prolog.gmake

APP		= suite2
AUTOS		= case.h
MODS		= case main
CPPFLAGS	= -I$(TOP)/dyncall
CXX_EXCEPTIONS	= 0
CXX_RTTI	= 0
LINK_PATHS	= $(TOP)/dyncall/$(BUILD_DIR) 
LINK_LIBS       = dyncall_s 
LINKER		= c

include $(TOP)/buildsys/gmake/epilog.gmake

$(AUTOS): mkcase.py
	python mkcase.py >case.h 2>config.h

config: case.h
case.o: case.cpp case.h config.h
case.h: design.cfg
design.cfg: rand.py
	python rand.py >$@

