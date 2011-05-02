all: \
	many.s \
	f16.s f20.s f40.s \
	d16.s d20.s d40.s \
	id40.s
.c.s:
	${CC} ${CFLAGS} -S $< ${TARGET_ARCH}
.PHONY: all clean
clean:
	rm -f *.s *.o


