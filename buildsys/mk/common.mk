#//////////////////////////////////////////////////////////////////////////////
#
# Copyright (c) 2010 Daniel Adler <dadler@uni-goettingen.de>, 
#                    Tassilo Philipp <tphilipp@potion-studios.com>
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


# --- phony targets ------------------------------------------------------------

#@@@build:V: dirs autos $TARGETS
build:V: dirs $TARGETS

CLEAN_FILES=$TARGETS $OBJS
clean:V: dirs
	echo Cleaning `{pwd}...
	rm -f $CLEAN_FILES || true

AUTO_FILES=$AUTOS $AUTO_DIRS
distclean:V: clean
	echo Cleaning auto-generated files in `{pwd}...
	rm -f $AUTOS $AUTO_DIRS || true


# --- auto generated -----------------------------------------------------------

#@@@autos:V: $AUTOS

# --- handling sub directories -------------------------------------------------

dirs:VQ: $DIRS
	for (i in $DIRS) @{
		echo Handling sub-directory $i...
		cd $i && $MK -f mkfile $MKFLAGS $MKARGS
	}

