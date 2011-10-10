#!/bin/sh
cpp -P Makefile.M | sed "s/^  */	/" > Makefile.dynmake
make -f Makefile.dynmake $1
