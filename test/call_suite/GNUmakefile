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
CPPFLAGS  	+= -I$(TOP)/dyncallback -I$(TOP)/dyncall
LINK_DIRS	+= $(TOP)/dyncall/$(BUILD_DIR)
LINK_LIBS 	+= dyncall_s

include $(GMAKE_TOP)/epilog.gmake

CONFIG_FILES	= cases.txt config.h cases.h

.PHONY: config clean-config config-random config-stress1

config: clean-config $(CONFIG_FILES)

clean-config: clean
	$(RM) $(CONFIG_FILES)

cases.txt: 
	$(LUA) rand-sig.lua >$@ 

cases.h: cases.txt
	$(LUA) mk-cases.lua >$@ <cases.txt

config.h:
	$(LUA) mk-config.lua >$@

