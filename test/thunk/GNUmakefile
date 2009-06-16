TOP = ../..
include $(TOP)/MakeProlog

TARGET_APP	 = thunk
UNITS		 = test_thunk
CPPFLAGS  	+= -I$(TOP)/dyncallback -I$(TOP)/dyncall
LINK_DIRS	+= $(TOP)/dyncallback/$(BUILD_DIR)
LINK_LIBS 	+= dyncallback_s

include $(TOP)/MakeEpilog

