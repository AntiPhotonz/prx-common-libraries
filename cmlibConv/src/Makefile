release: all
	psp-build-exports -s exports.exp

TARGET		=	cmlibconv

BUILD_PRX = 1


OBJS	=	exports.o memory.o main.o

PRX_EXPORTS	=	exports.exp
USE_KERNEL_LIBC	=	1
USE_KERNEL_LIBS	=	1

INCDIR	=	
CFLAGS	=	-Os -G 0 -Wall -fno-strict-aliasing
ASFLAGS	=	$(CFLAGS)

LIBDIR 	= 	
LDFLAGS	=	-mno-crt0 -nostartfiles
LIBS	=	-lpspkubridge

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak

