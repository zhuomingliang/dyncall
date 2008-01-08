# dyncall project GNUmakefile
# Copyright 2007 Daniel Adler

# --- header ------------------------------------------------------------------

TOP   = .

include $(TOP)/build/gmake/prolog.gmake

# --- project directories -----------------------------------------------------

AUTOS = ConfigRules
DIRS  = dyncall dynload 

# --- project dependencies ----------------------------------------------------
.PHONY: test
test: 
	$(MAKE) -C test 
# --- epilog ------------------------------------------------------------------

include $(TOP)/build/gmake/epilog.gmake

.PHONY: distclean-depth

distclean-depth:
	find . -type d -name "out_*" | xargs rm -Rf

distclean: distclean-depth

install: build
	$(MAKE) -C dyncall install
	$(MAKE) -C dynload install

