TARGETS		= test
TARGET_ARCH	= -arch armv7 -mthumb-interwork -isysroot /Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS3.0.sdk
# CFLAGS		= -mthumb-interwork
# CFLAGS_THUMB	= -mthumb $(CFLAGS)
LOADLIBES	= thumb.o arm.o
all: $(LOADLIBES) test

thumb.o: thumb.c
	$(CC) -c $(CPPFLAGS) $(TARGET_ARCH) -mthumb $< -o $@
arm.o: arm.c

test.o: test.c

test: test.o thumb.o arm.o
	$(LINK.o) $^ $(OUTPUT_OPTION)

clean:
	$(RM) $(TARGETS) *.o
