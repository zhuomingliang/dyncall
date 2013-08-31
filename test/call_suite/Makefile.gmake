TOP		= ../..
GMAKE_TOP	= $(TOP)/buildsys/gmake
include $(GMAKE_TOP)/prolog.gmake

# On my Windows, lua is only available as lua5.1 from make
ifdef BUILD_OS_windows
LUA		 = lua5.1
else
LUA		 = lua
endif

TARGET_APP	 = call_suite

UNITS		 = globals invoke cases main
CPPFLAGS  	+= -I$(TOP)/dyncall
LINK_DIRS	+= $(TOP)/dyncall/$(BUILD_DIR)
LINK_LIBS 	+= dyncall_s

include $(GMAKE_TOP)/epilog.gmake

.PHONY: config config-random config-design

config: config-random

config-random: 
	$(LUA) rand-sig.lua >cases.txt
	$(LUA) mk-cases.lua <cases.txt >cases.h 

config-design:
	$(LUA) mk-cases.lua <cases.txt >cases.h 


