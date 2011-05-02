all: many.s \
     f16.s f20.s f40.s \
     d16.s
.c.s:
	${CC} ${CFLAGS} -S $<
.PHONY: all clean
clean:
	rm -f *.s *.o


