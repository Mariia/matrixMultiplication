#! /bin/bash

BINARY = main
CFLAGS = -g -Wall 
MATRIX_DIMENSIONS = 2 2 2
VALGRIND = --tool=memcheck

$(BINARY): main.h main.c
	gcc $(CFLAGS) main.c -o $(BINARY)

run:
	./main $(MATRIX_DIMENSIONS)

memtest:
	valgrind $(VALGRIND) ./main $(MATRIX_DIMENSIONS)

clean:
	rm $(BINARY)
