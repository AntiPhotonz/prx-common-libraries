release: all
	psp-build-exports -s -v exports.exp
	cp $(TARGET).prx ../release/$(TARGET).prx
	cp $(TARGET).S ../release/$(TARGET).S
	cp cmLibLog.h ../release/cmLibLog.h
	cp $(TARGET).prx ../sampleprx/$(TARGET).prx
	cp $(TARGET).S ../sampleprx/$(TARGET).S
	cp cmLibLog.h ../sampleprx/cmLibLog.h
	rm *.o

TARGET = cmLibLog

OBJS = imports.o _stdlib.o cmLibLog.o


BUILD_PRX = 1
PRX_EXPORTS = exports.exp

USE_KERNEL_LIBS = 1
USE_KERNEL_LIBC = 1

INCDIR		= 
CFLAGS 		= -O2 -G0 -Wall
CXXFLAGS 	= $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS 	= $(CFLAGS)

LIBDIR		= 
LDFLAGS		= -mno-crt0 -nostartfiles
LIBS		= -lpsprtc -lpsplibc -lpspsysmem_user

# -lpspsystemctrl_kernel



PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
