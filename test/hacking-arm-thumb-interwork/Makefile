TARGETS		= test
TARGET_ARCH	= -march=armv4t
CFLAGS		= -mthumb-interwork
CFLAGS_THUMB	= -mthumb $(CFLAGS)
LOADLIBES	= thumb.o arm.o
all: $(LOADLIBES) test

thumb.o: thumb.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS_THUMB) $(TARGET_ARCH) $< -o $@
arm.o: arm.c

clean:
	$(RM) $(TARGETS) *.o
