# June 24, 2004
#
# Makefile for compiling accompanying software for
# "Discrete-Event Simulation: A First Course" by Park and Leemis
#

CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lm

OBJFILES = ex122 ex126 ex234 ex235 rng.o rngs.o rvgs.o rvms.o 

all: $(OBJFILES)

rng.o: ../c_lib/rng.c ../c_lib/rng.h
	$(CC) -c $<

rngs.o: ../c_lib/rngs.c ../c_lib/rngs.h
	$(CC) -c $<

rvgs.o: ../c_lib/rvgs.c ../c_lib/rvgs.h ../c_lib/rngs.c ../c_lib/rngs.h
	$(CC) -c $<

rvms.o: ../c_lib/rvms.c ../c_lib/rvms.h ../c_lib/rngs.c ../c_lib/rngs.h
	$(CC) -c $<

ex122: ex122.c
	$(CC) $(LDFLAGS) $^ -o $@

ex126: ex126.c
	$(CC) $(LDFLAGS) $^ -o $@

ex234: ex234.c rng.o
	$(CC) $(LDFLAGS) $^ -o $@

ex235: ex235.c rng.o
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	/bin/rm -f $(OBJFILES) core*
