#!/bin/sh
make -f `dirname $0`/Makefile lua-5.1.4
case `uname -s` in
  Darwin)
    LPLAF=macosx
    ;;
  *)
    LPLAF=posix
    ;;
esac
(cd lua-5.1.4; make ${LPLAF})


