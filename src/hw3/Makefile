# June 24, 2004
#
# Makefile for compiling accompanying software for
# "Discrete-Event Simulation: A First Course" by Park and Leemis
#

CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lm

OBJFILES = ex311 ex334 ex315 rng.o rngs.o rvgs.o rvms.o 

all: $(OBJFILES)

rng.o: ../c_lib/rng.c ../c_lib/rng.h
	$(CC) -c $<

rngs.o: ../c_lib/rngs.c ../c_lib/rngs.h
	$(CC) -c $<

rvgs.o: ../c_lib/rvgs.c ../c_lib/rvgs.h ../c_lib/rngs.c ../c_lib/rngs.h
	$(CC) -c $<

rvms.o: ../c_lib/rvms.c ../c_lib/rvms.h ../c_lib/rngs.c ../c_lib/rngs.h
	$(CC) -c $<

ex311: ex311.c rng.o
	$(CC) $(LDFLAGS) $^ -o $@

ex334a: ex334a.c rngs.o rvgs.o
	$(CC) $(LDFLAGS) $^ -o $@

ex334b: ex334b.c rngs.o rvgs.o
	$(CC) $(LDFLAGS) $^ -o $@

ex315: ex315.c rngs.o rvgs.o
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	/bin/rm -f $(OBJFILES) core*
