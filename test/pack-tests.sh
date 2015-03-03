#!/bin/sh
# script to package some tests for quick deployment (useful for embedded stuff)

TESTS="callf call_suite ellipsis malloc_wx plain plain_c++ suite suite2 suite3 suite_floats callback_plain callback_suite"
# addition test:
#
# callback_plain callback_suite callf
# ellipsis
# malloc_wx thunk
# nm
# plain suite suite2 suite3
# suite2_x86win32fast suite2_x86win32std suite_x86win32fast suite_x86win32std

DATE=`date +%s`
NAME="dyncall-tests-${DATE}"

mkdir -p _work/${NAME}
for I in $TESTS ; do
cp $I/$I _work/${NAME}
done
mkdir -p _packed
tar -cvzf _packed/${NAME}.tar.gz -C _work ${NAME}
