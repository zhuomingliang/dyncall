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

# default: dump-fail

TOP = ../..
include $(TOP)/MakeProlog

RESULT_FLAGS	 = -v

TARGET_APP	 = callback_suite2
AUTOS		 = _auto_config.h _auto_sigstrings.h _auto_invokers.h \
		   _auto_invoke_macros.h _auto_invoke_table.h _results.txt

# Comment to have user-designed cases:
AUTOS		+= _auto_signatures.txt

UNITS		 = env handler sigstrings invokers do_test main print
CPPFLAGS  	+= -I$(TOP)/dyncallback -I$(TOP)/dyncall
LINK_DIRS	+= $(TOP)/dyncallback/$(BUILD_DIR)
LINK_LIBS 	+= dyncallback_s
AUTO_HEADERS	 = $(AUTOS)

include $(TOP)/MakeEpilog

invokers.o: _auto_config.h _auto_invokers.h
sigstrings.o: _auto_config.h _auto_sigstrings.h

_auto_signatures.txt: 
	lua make-signatures.lua >$@

_auto_invokers.h: _auto_signatures.txt 
	lua make-invokers.lua <$< >$@

_auto_sigstrings.h: _auto_signatures.txt
	lua make-cstrings.lua <$< >$@

_auto_config.h: 
	lua make-config.lua >$@

_auto_invoke_macros.h:
	lua make-invoke-macros.lua >$@

_auto_invoke_table.h:
	lua make-invoke-table.lua >$@

clean-autos: clean
	$(RM) $(AUTOS)

_results.txt: $(APP_FILE)
	$(APP_FILE) $(RESULT_FLAGS) >$@

.PHONY: results
results: _results.txt

.PHONY: run
run: $(APP_FILE)
	$(APP_FILE)

dump-results: _results.txt
	@cat _results.txt

dump-fail: _results.txt
	grep ":0" <$< || echo "<none>"

dump-ok: _results.txt
	grep ":1" <$< || echo "<none>"

%.c_pp: %.c
	$(CPP) $(CPPFLAGS) $< >$@

