#! /bin/bash

BINARY = main
CFLAGS = -g -Wall 
MATRIX_DIMENSIONS = 2 3 1

$(BINARY): main.h main.c
	gcc $(CFLAGS) main.c -o $(BINARY)

run:
	./main $(MATRIX_DIMENSIONS)

clean:
	rm $(BINARY)
