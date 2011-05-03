CFLAGS += -I../../dyncall
LDFLAGS += -L../../dyncall -ldyncall_s
OBJS = globals.o invoke.o cases.o main.o
TARGETS = call_suite ${OBJS} 
.PHONY: all clean autogen
all: ${TARGETS}
autogen: 
	lua mk-config.lua >config.h
	lua rand-sig.lua >cases.txt
	lua mk-cases.lua <cases.txt >cases.h
cases.o: cases.h 
call_suite: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LDFLAGS} -o $@
clean:
	rm -f ${TARGETS}

cases.txt:
	lua rand-sig.lua >cases.txt
cases.h: cases.txt
	lua mk-cases.lua <cases.txt >cases.h
cases.o: cases.h
