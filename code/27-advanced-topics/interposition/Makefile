###########################################################################
# Edit the following line to indicate where libdl.so is found on your system
###########################################################################
LIBDL = /usr/lib64/libdl.so  # 64-bit systems
#LIBDL = /usr/lib/libdl.so   # 32-bit systems

# No need to change anything below here
CC = gcc
CFLAGS = -O2 -Wall

all: hellor hellol helloc

#############################
# Load/Run-time interposition
#############################
hellor: hello.c
	$(CC) $(CFLAGS) -DRUNTIME -shared -fPIC -o mymalloc.so mymalloc.c
	$(CC) $(CFLAGS) -ldl -o hellor hello.c

# Note: different shells may have different ways to initialize
# the LD_PRELOAD environment variable. 
runr:
#	(LD_PRELOAD="$(LIBDL) ./mymalloc.so" ./hellor)	
	(LD_PRELOAD="./mymalloc.so" ./hellor)	

#########################
# Link-time interposition
#########################
hellol: hello.c mymalloc.c
	$(CC) $(CFLAGS) -DLINKTIME -c mymalloc.c
	$(CC) $(CFLAGS) -Wl,--wrap,malloc -Wl,--wrap,free \
	-o hellol hello.c mymalloc.o

runl:
	./hellol

############################
# Compile-time interposition
############################
helloc: hello.c mymalloc.c
	$(CC) $(CFLAGS) -DCOMPILETIME -c mymalloc.c
	$(CC) $(CFLAGS) -I. -o helloc hello.c mymalloc.o

runc:
	./helloc



clean:
	rm -f *~ hellor hellol helloc *.so *.o


