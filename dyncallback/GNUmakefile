TOP = ..
include $(TOP)/MakeProlog

TARGET_LIB	 = dyncallback
INSTALL_LIB	 = 1

# uses some dyncall headers - no other dependencies.

CPPFLAGS	 += -I$(TOP)/dyncall

# component: thunks

INSTALL_HEADERS	+= dyncall_thunk.h dyncall_thunk_x86.h dyncall_thunk_ppc32.h dyncall_thunk_x64.h
UNITS += dyncall_thunk 

# component: write-and-executable memory allocation

INSTALL_HEADERS	+= dyncall_alloc_wx.h
UNITS += dyncall_alloc_wx

# component: unmarshall arguments at callee-site

INSTALL_HEADERS += dyncall_args.h
UNITS += dyncall_args

# architecture: callback

INSTALL_HEADERS += dyncall_callback.h
UNITS += dyncall_callback

ifdef BUILD_TOOL_gcc
UNITS += dyncall_callback_arch
endif

ifdef BUILD_TOOL_msvc
ifdef BUILD_ARCH_x86
UNITS += dyncall_callback_x86_msvc
endif
ifdef BUILD_ARCH_x64
UNITS += dyncall_callback_x64_masm
endif
endif


include $(TOP)/MakeEpilog

