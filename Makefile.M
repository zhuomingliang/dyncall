#include "buildsys/dynmake/Makefile.base.M"

.PHONY: all
all:
        cd dyncall     _(SHELL_COMMAND_SEPARATOR) _(MAKE) _(MAKE_FLAG) _(MAKE_DEFAULT_FILE)
        //cd dynload     _(SHELL_COMMAND_SEPARATOR) _(MAKE) _(MAKE_FLAG) _(MAKE_DEFAULT_FILE)
        //cd dyncallback _(SHELL_COMMAND_SEPARATOR) _(MAKE) _(MAKE_FLAG) _(MAKE_DEFAULT_FILE)
