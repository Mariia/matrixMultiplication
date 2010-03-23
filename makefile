#! /bin/bash


SERIAL = serial
PARALLEL = parallel
CANNON = cannon

CFLAGS = -Wall -c
MATRIX_DIMENSIONS = 4 4 4   
N_PROCS = 4
VALGRIND = --tool=memcheck

serial: serial.o matrixOperations.o
	mpicc serial.o matrixOperations.o -o $(SERIAL)

parallel: parallel.o matrixOperations.o
	mpicc parallel.o matrixOperations.o -o $(PARALLEL)

cannon: cannon.o matrixOperations.o
	mpicc cannon.o matrixOperations.o -o $(CANNON)

# Dependencies
serial.o: serial.c
	mpicc $(CFLAGS) serial.c

parallel.o: parallel.c
	mpicc $(CFLAGS) parallel.c

cannon.o: cannon.c
	mpicc $(CFLAGS) cannon.c

matrixOperations.o: matrixOperations.c
	mpicc $(CFLAGS) matrixOperations.c

# Running and Performance
runSerial:
	mpiexec -n $(N_PROCS) ./$(SERIAL) $(MATRIX_DIMENSIONS)

runParallel:
	mpiexec -n $(N_PROCS) ./$(PARALLEL) $(MATRIX_DIMENSIONS)

runCannon:
	mpiexec -n $(N_PROCS) ./$(CANNON) $(MATRIX_DIMENSIONS)

memtestSerial:
	valgrind $(VALGRIND) mpiexec ./$(SERIAL) $(MATRIX_DIMENSIONS)

memtestParallel:
	valgrind $(VALGRIND) mpiexec ./$(PARALLEL) $(MATRIX_DIMENSIONS)

clean:
	rm -f $(SERIAL) $(PARALLEL) $(CANNON) *.o
