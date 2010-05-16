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


#@@@ add stuff for crosscompiling here.

CC = pcc
LD = pcc

#@@@.if $(BUILD_CONFIG) == "debug"
#@@@ add -g option or similar
#@@@.endif
CPPFLAGS = -D__Plan9__ -D__${objtype}__
CFLAGS   = $CFLAGS -D__Plan9__ -D__${objtype}__ -I$TOP/dyncall -I$TOP/dyncallback -c
#CXXFLAGS = $CXXFLAGS -D__Plan9__
#ASFLAGS  = -D__Plan9__

# Step to transform .S into object files.
%.$O: %.S
	cp $prereq $prereq.c
	pcc -E $CPPFLAGS $prereq.c | sed '{
		/^$/d
		/^#.*/d
		s/^\.(globl|intel_syntax|file|section).*//
		s/(.*):/TEXT \1(SB), $0/g
		s/%//g
		/^[	 ]+/y/abcdefghijklmnopqrstuvwxyz/ABCDEFGHIJKLMNOPQRSTUVWXYZ/
		s/([A-Z]+)[	 ]*E(..)[,	 ]*E(..)/\1L \3, \2/
		s/([A-Z]+)[	 ]*E(..)[,	 ]*([0-9]+)/\1L \3, \2/
		s/([A-Z]+)[	 ]*E(..)[,	 ]*\[E(..)\+([0-9]+)\]/\1L \4(\3), \2/
		s/([A-Z]+)[	 ]*E(..)$/\1L \2/
		s/([A-Z]+)[	 ]*\[E(..)\+([0-9]+)\]/\1L \3(\2)/
	}' > $stem.s # replace with cpp? pcc requires .c suffix
	rm $prereq.c
	$AS $AFLAGS $stem.s

