#!/bin/sh
DL=wget make Makefile lua-5.1.4
case `uname -s` in
  darwin)
    LPLAF=macosx
    ;;
  *)
    LPLAF=posix
    ;;
esac
(cd lua-5.1.4; make ${LPLAF})

