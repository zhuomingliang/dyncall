#!/bin/sh
if [ -z "${DL}" ]; then
  DL=wget
fi
case `uname -s` in
  Darwin)
    LPLAF=macosx
    ;;
  *)
    LPLAF=posix
    ;;
esac
DL="${DL}" make -f `dirname $0`/Makefile lua-5.1.4
(cd lua-5.1.4; make ${LPLAF})


