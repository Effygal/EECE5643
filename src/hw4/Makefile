

CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lm

OBJFILES = rng.o rngs.o rvgs.o rvms.o librvgs.so cdh.o libcdh.so cdh

all: $(OBJFILES)

rng.o: ../c_lib/rng.c ../c_lib/rng.h
	$(CC) -c $<

rngs.o: ../c_lib/rngs.c ../c_lib/rngs.h
	$(CC) -c $<

rvgs.o: ../c_lib/rvgs.c ../c_lib/rvgs.h ../c_lib/rngs.c ../c_lib/rngs.h
	$(CC) -c $<

rvms.o: ../c_lib/rvms.c ../c_lib/rvms.h ../c_lib/rngs.c ../c_lib/rngs.h
	$(CC) -c $<

librvgs.so: rvgs.o rngs.o
	$(CC) -shared -o librvgs.so rvgs.o rngs.o

cdh: cdh.c
	$(CC) $(LDFLAGS) -g -O0 $^ -o $@

cdh.o: cdh.c 
	$(CC) -c $<

libcdh.so: cdh.o
	$(CC) -shared -o $@ cdh.o

clean:
	/bin/rm -f $(OBJFILES) core*
