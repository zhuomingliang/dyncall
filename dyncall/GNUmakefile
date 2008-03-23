#//////////////////////////////////////////////////////////////////////////////
#
# Copyright (c) 2007,2008 Daniel Adler <dadler@uni-goettingen.de>, 
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

# dyncall library GNUmakefile

TOP = ..

TARGET_LIB = dyncall

UNITS = dyncall dyncall_vector dyncall_callf

INSTALL_HEADERS	= \
	dyncall_macros.h \
	dyncall_config.h \
	dyncall_types.h \
	dyncall.h \
	dyncall_signature.h \
	dyncall_value.h \
	dyncall_callf.h
INSTALL_LIB = 1

include $(TOP)/MakeProlog

# --- x86 family --------------------------------------------------------------

ifdef BUILD_ARCH_x86

UNITS += dyncall_callvm_x86

ifdef BUILD_ASM_nasm

UNITS += dyncall_x86_nasm

else # !nasm

ifdef BUILD_TOOL_msvc

UNITS += dyncall_x86_windows

else # !msvc

ifdef BUILD_OS_darwin
UNITS += dyncall_x86_darwin
else
UNITS += dyncall_x86_as
endif

endif # !msvc
endif # !nasm
endif # x86

ifdef BUILD_ARCH_x64
UNITS += dyncall_callvm_x64
UNITS += dyncall_x64_system_v
endif


# --- powerpc -----------------------------------------------------------------

ifdef BUILD_ARCH_ppc32
UNITS += dyncall_callvm_ppc32
UNITS += dyncall_ppc32
endif

# --- arm ---------------------------------------------------------------------

ifdef BUILD_ARCH_arm9e
UNITS += dyncall_callvm_arm9e_arm
UNITS += dyncall_arm9e_arm
endif

# --- mips --------------------------------------------------------------------

ifdef BUILD_ARCH_mips32
UNITS += dyncall_callvm_mips32
UNITS += dyncall_mips32
ifdef BUILD_TOOL_pspsdk
ASFLAGS += -c
endif
endif

# -----------------------------------------------------------------------------

include $(TOP)/MakeEpilog

