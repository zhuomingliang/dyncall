# Package: dyncall
# File: dyncall/test/suite2/GNUmakefile
# Description: Test suite 2 GNUmakefile
# License:
#
# Copyright (c) 2007,2011 Daniel Adler <dadler@uni-goettingen.de>, 
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

TOP		= ../..
GMAKE_TOP	= $(TOP)/buildsys/gmake
include $(GMAKE_TOP)/prolog.gmake

TARGET_APP	= suite2
UNITS		= case main
CPPFLAGS       += -I$(TOP)/dyncall
CXX_EXCEPTIONS	= 0
CXX_RTTI	= 0
LINK_DIRS	= $(TOP)/dyncall/$(BUILD_DIR) 
LINK_LIBS       = dyncall_s 
LINKER		= c

include $(GMAKE_TOP)/epilog.gmake

.PHONY: config config-random config-stress1 config-ints

config: config-stress1

config-random:
	python rand.py >design.cfg
	python mkcase.py >case.h 2>config.h

config-stress1:
	cp stress1.cfg design.cfg
	python mkcase.py >case.h 2>config.h

config-ints:
	cp ints.cfg design.cfg
	python mkcase.py >case.h 2>config.h

