CC = gcc
CFLAGS = -O2 -Wall

all: mm

fcyc.o: fcyc.c fcyc.h clock.h
	$(CC) $(CFLAGS) -c fcyc.c

clock.o: clock.c clock.h
	$(CC) $(CFLAGS) -c clock.c

mm: mm.c mm.h fcyc.h fcyc.o clock.o
	$(CC) $(CFLAGS) -o mm mm.c fcyc.o clock.o -lrt

mm.s: mm.c mm.h
	$(CC) $(CFLAGS) -S mm.c

clean:
	rm -f *.o mm bmm *~ mm.s


