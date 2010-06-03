#//////////////////////////////////////////////////////////////////////////////
#
# Copyright (c) 2007,2009 Daniel Adler <dadler@uni-goettingen.de>, 
#                         Tassilo Philipp <tphilipp@potion-studios.com>
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#
#//////////////////////////////////////////////////////////////////////////////

TOP = ../..
include $(TOP)/MakeProlog

RESULT_FLAGS	 = -v


# On my Windows, lua is only available as lua5.1 from make
ifdef BUILD_OS_windows
LUA		 = lua5.1
else
LUA		 = lua
endif

TARGET_APP	 = callback_suite

UNITS		 = env handler sigstrings invokers do_test main print signature_utils
CPPFLAGS  	+= -I$(TOP)/dyncallback -I$(TOP)/dyncall
LINK_DIRS	+= $(TOP)/dyncallback/$(BUILD_DIR)
LINK_LIBS 	+= dyncallback_s

include $(TOP)/MakeEpilog

CONFIG_FILES	= _auto_config.h _auto_sigstrings.h _auto_invokers.h \
		   _auto_invoke_macros.h _auto_invoke_table.h 
CONFIG_FILES	+= _auto_signatures.txt

.PHONY: config clean-config config-random config-stress1

config: clean-config $(CONFIG_FILES)

config-random:
	cp config-random.lua config.lua
	$(MAKE) config

config-stress1:
	cp config-stress1.lua config.lua
	$(MAKE) config

clean-config: clean
	$(RM) $(CONFIG_FILES)

_auto_signatures.txt: 
	$(LUA) make-signatures.lua >$@

_auto_invokers.h: _auto_signatures.txt 
	$(LUA) make-invokers.lua <$< >$@

_auto_sigstrings.h: _auto_signatures.txt
	$(LUA) make-cstrings.lua <$< >$@

_auto_config.h: 
	$(LUA) make-config.lua >$@

_auto_invoke_macros.h:
	$(LUA) make-invoke-macros.lua >$@

_auto_invoke_table.h:
	$(LUA) make-invoke-table.lua >$@

