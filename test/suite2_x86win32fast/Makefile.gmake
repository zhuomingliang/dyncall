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

#///////////////////////////////////////////////////
#
#	gmake makefile
#	GNUmakefile
#
#///////////////////////////////////////////////////


TOP		= ../..

include $(TOP)/buildsys/gmake/prolog.gmake

case.o: case.cpp case.h config.h
case.h: design.cfg
design.cfg: rand.py

TARGET_APP	= suite2_x86win32fast
UNITS		= case main
CPPFLAGS	= -I$(TOP)/dyncall
CXX_EXCEPTIONS	= 0
CXX_RTTI	= 0
LINK_DIRS	= $(TOP)/dyncall/$(BUILD_DIR) 
LINK_LIBS       = dyncall_s 
LINKER		= c

include $(TOP)/buildsys/gmake/epilog.gmake

.PHONY: config
config: 
	python rand.py >design.cfg
	python mkcase.py >case.h 2>config.h
