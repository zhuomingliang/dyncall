# dyncall library GNUmakefile
# Copyright 2007 Daniel Adler.

TOP         = ..
include $(TOP)/build/gmake/prolog.gmake

# targets

LIBRARY         = dyncall
INSTALL_HEADERS = dyncall.h dyncall_types.h dyncall_config.h
# modules

MODS = dyncall 

# feature formated call API
MODS += dyncall_callf

# common utilities
MODS += dyncall_vector

# arch-specific modules

ifdef BUILD_ARCH_x86
MODS += dyncall_callvm_x86

ifndef BUILD_TOOL_msvc
MODS += dyncall_x86_$(BUILD_ASM)
else
MODS += dyncall_x86_win32
endif

nasm_FLAGS += -DBUILD_OS=$(BUILD_OS)=1 -DBUILD_ARCH_$(BUILD_ARCH)=1
endif

ifdef BUILD_ARCH_ppc32
MODS += dyncall_callvm_ppc32
MODS += dyncall_ppc32
endif

ifdef BUILD_ARCH_arm9e
MODS += dyncall_callvm_arm9e_arm
MODS += dyncall_arm9e_arm
endif

ifdef BUILD_ARCH_x64
MODS += dyncall_callvm_x64
MODS += dyncall_x64_system_v
endif

ifdef BUILD_ARCH_mips32
MODS += dyncall_callvm_mips32
MODS += dyncall_mips32
LDFLAGS += -L$(PSPSDK)/lib
LDLIBS += -lpsplibc
endif

include $(TOP)/build/gmake/epilog.gmake

