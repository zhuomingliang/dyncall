TOP = ../..
include $(TOP)/MakeProlog

TARGET_APP	= malloc_wx
UNITS		= test_wx
CPPFLAGS  	+= -I$(TOP)/dyncall -I$(TOP)/dyncallback 
LINK_DIRS	+= $(TOP)/dyncallback/$(BUILD_DIR)
LINK_LIBS 	+= dyncallback_s

include $(TOP)/MakeEpilog
