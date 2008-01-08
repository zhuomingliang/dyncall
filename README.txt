dynamic function call library
=============================
Copyright (C) 2007 D. Adler and T. Philipp
This project is under BSD License.

TODO
- build tool gcc/mingw: build .lib files to link with microsoft
- R bindings: support DC_CHAR, DC_SHORT
- python,R upgrade:
  - callvm objects
  - mode method
- java port
- build/gmake absolute BUILD_DIR linking failed
 
  e.g. 

  SiteRules:
  BUILD_DIR=$(TOP)/out_$(BUILD_CONFIG)

  test/plain:
  LDFLAGS=-L$(TOP)/$(BUILD_DIR)/dyncall

  but dyncall library is in $(TOP)/out_$(BUILD_CONFIG)


- rename test/ellipse -> test/ellipsis
- remove DC_CALL_DEFAULT_CXX_THIS ? DC_CALL_X86_WIN32_THIS_MS
- DC_CALL_PPC32_OSX_DEFAULT -> DC_CALL_PPC32_DARWIN_DEFAULT ??
- support for dcMode in bindings 
- bindings/R/rdc: support for short,char,longlong etc
- splitting test cases
- 'restrict' C89 support useful?
- memory check dyncall/dyncall_vector.h
- gmake -- remove "-include"
- gmake -- NASM_flags ... 
- binding update: support for multiple calling conventions
- manual: API, concepts
- write test engine - mixing plain and suite2 
  namely: designable tests for multiple arguments, return values, calling conventions and C++ calls

- repo: move to another system?
  - migrate to subversion

- remove long double for now (temporarily)

- correct versioning in ELF dynamic libraries 
- ruby binding
- either, dynload, test/nm 
  getSymbolCount and friends temporarly removed
- website update
  - wiki-based
    - trac?
    - redmine

TODO LOW-PRIORITY
- dynload iterate symbols feature for ELF and Macho
- make x86 port cleaner (backend can be even smaller)
- motte freebsd port 

QUESTIONS
- 

ROADMAP
0.1 Friday, 2007/11/28
- port linux:
  on Linux GCC/ELF (since Linux 1.2), the C symbols are NOT underscored.
  we currently handle this fact in the assembly source 
- gmake: 
  - build directory
  - linux port
  - motte freebsd port 
  - create depends files and include in Makefiles
- restructuring

- support for all C types (DClong will be DClonglong)
  
  dcShort
  dcLongLong

- rename dcu -> libdyncallutil
- x64,x86_x64,x64
- documentation
- dyncall build tools package
- build documentation
- language: R, python, ruby
- stdcall and ccall merge on x86?!

TODO
- hg repo: transform repo to unix-source 
  -------- introduce encode/decode for hg on win32 hg clients
- linux platform
- check usage of static/dynamic linkage
- source code style
- common direct call interface
	suggestion:

	struct calldata_ppc32;
	struct calldata_x86;

	void dcCall(void* target, void* argdata);
- win32 portable assembly framework for backends nasm/as/vc
- support for all C types such as 8bit char, 16bit short
- rename dcPushLong to dcPushLongLong ?

DONE
- regression test suite
- test/suite/mkcase.py should only run at make distclean

