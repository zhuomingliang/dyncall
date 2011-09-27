TARGET	  = sharedlib.so
OBJS	  = sharedlib.o
CPPFLAGS += -I../../dynload
LDFLAGS   = -shared

sharedlib.so: ${OBJS}
	${CC} $? ${LDFLAGS} -o $@
all: ${TARGET}
clean:
	rm -f ${TARGET}

