#! /bin/bash


SERIAL = serial
PARALLEL = parallel
CANNON = cannon

CFLAGS = -g -Wall -c
MATRIX_DIMENSIONS = 4 2 3
VALGRIND = --tool=memcheck

serial: serial.o matrixOperations.o
	mpicc serial.o matrixOperations.o -o $(SERIAL)

# Dependencies
serial.o: serial.c
	mpicc $(CFLAGS) serial.c

matrixOperations.o: matrixOperations.c
	mpicc $(CFLAGS) matrixOperations.c

# Running and Performance
runSerial:
	mpiexec ./$(SERIAL) $(MATRIX_DIMENSIONS)

memtestSerial:
	valgrind $(VALGRIND) mpiexec ./$(SERIAL) $(MATRIX_DIMENSIONS)

clean:
	rm -f $(SERIAL) $(PARALLEL) $(CANNON) *.o
