CC = gcc
CFLAGS = -Wall -O2 

all: mountain

fcyc.o: fcyc.c fcyc.h clock.h
	$(CC) $(CFLAGS) -c fcyc.c

clock.o: clock.c clock.h
	$(CC) $(CFLAGS) -c clock.c


mountain: mountain.c fcyc.h fcyc.o clock.o
	$(CC) $(CFLAGS) -o mountain mountain.c fcyc.o clock.o -lrt

clean:
	rm -f mountain *.o *~


