( cd dyncall ; CC=gcc make -f Makefile.generic clean all CFLAGS= )
( cd dyncallback ; CC=gcc make -f Makefile.generic clean all CFLAGS=-I../dyncall )
( cd test ; CC=gcc CFLAGS= CXX=g++ make -f Makefile.generic clean all-no-dynload )

