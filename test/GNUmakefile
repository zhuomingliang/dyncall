#///////////////////////////////////////////////////
#
#	tests GNUmakefile
#	Copyright 2007 Daniel Adler
#
#///////////////////////////////////////////////////


TOP	=  ..
include $(TOP)/buildsys/gmake/prolog.gmake
DIRS	+= suite ellipsis suite2 callf plain

ifdef BUILD_OS_windows
DIRS	+= suite_x86win32fast
DIRS	+= suite_x86win32std
DIRS	+= suite2_x86win32fast
DIRS	+= suite2_x86win32std
endif

include $(TOP)/buildsys/gmake/epilog.gmake

