#!/bin/sh
#cpp -P Makefile.M | sed "s/^  */	/" > Makefile.dynmake
gcc -E -P -x c Makefile.M | sed "s/^  */	/" > Makefile.dynmake
$2 -f Makefile.dynmake $1
