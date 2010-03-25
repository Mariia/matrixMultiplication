#! /bin/bash


SERIAL = serial
PARALLEL = parallel
PARALLELOMP = parallelOMP
CANNON = cannon

CFLAGS = -Wall -c -g
MATRIX_DIMENSIONS = 4 4 4   
N_PROCS = 4
VALGRIND = --tool=memcheck

serial: serial.o matrixOperations.o
	mpicc serial.o matrixOperations.o -o $(SERIAL)

parallel: parallel.o matrixOperations.o
	mpicc parallel.o matrixOperations.o -o $(PARALLEL)

parallelOMP: parallelOMP.o matrixOperations.o
	mpicc -openmp parallelOMP.o matrixOperations.o -o $(PARALLELOMP)

cannon: cannon.o matrixOperations.o
	mpicc cannon.o matrixOperations.o -o $(CANNON)

# Dependencies
serial.o: serial.c
	mpicc $(CFLAGS) serial.c

parallel.o: parallel.c
	mpicc $(CFLAGS) parallel.c

parallelOMP.o: parallelOMP.c
	mpicc $(CFLAGS) -openmp parallelOMP.c

cannon.o: cannon.c
	mpicc $(CFLAGS) cannon.c

matrixOperations.o: matrixOperations.c
	mpicc $(CFLAGS) matrixOperations.c

# Running and Performance
runSerial:
	mpiexec -n $(N_PROCS) ./$(SERIAL) $(MATRIX_DIMENSIONS)

runParallel:
	mpiexec -n $(N_PROCS) ./$(PARALLEL) $(MATRIX_DIMENSIONS)

runParallelOMP:
	# Export Variables
	export KMP_AFFINITY=norespect,scatter
	mpiexec -n $(N_PROCS) ./$(PARALLELOMP) $(MATRIX_DIMENSIONS)

runCannon:
	mpiexec -n $(N_PROCS) ./$(CANNON) $(MATRIX_DIMENSIONS)

memtestSerial:
	valgrind $(VALGRIND) mpiexec ./$(SERIAL) $(MATRIX_DIMENSIONS)

memtestParallel:
	valgrind $(VALGRIND) mpiexec ./$(PARALLEL) $(MATRIX_DIMENSIONS)

clean:
	rm -f $(SERIAL) $(PARALLEL) $(CANNON) *.o
