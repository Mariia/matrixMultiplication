// ============================================================================
// 
//       Filename:  matrixOperations.h
// 
//    Description:  Contains the declarations of the matrix operations, 
//                  including intializing MPI and getting the information from
//                  a file.
// 
//        Created:  03/03/2010 04:53:39 PM
//       Compiler:  mpicc
// 
//         Author:  Jose V. Trigueros (), j.v.trigueros@gmail.com
// 
// ============================================================================
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define gMatrixA "A.txt"
#define gMatrixB "B.txt"

// Global Variables
int gNumProcessors, gRank;     // gRank is the current processor
int gX1,gY1,gX2,gY2;           // size of matrix A and matrix B
double gStartTime, gEndTime;

int * A;
int * B;

// Create constant variables for sizes and create matrices
// ===  FUNCTION  =============================================================
//         Name:  setMatrixData(int,char*)
//  Description:  Will initialize the matrix information like size and the 
//                actual arrays.
// ============================================================================
void setMatrixData(int argc, char argv[]);

// ===  FUNCTION  =============================================================
//         Name:  initializeMPI(int*,char**)
//  Description:  This is just a subroutine running the things necessary to set
//                MPI.
// ============================================================================
void initializeMPI(int * argc, char ** argv);

// ===  FUNCTION  =============================================================
//         Name:  readFile(char*,char*)
//  Description:  Reads a file and puts it in a string that the caller passed 
//                as reference.
// ============================================================================
void readFile( char *filename , char** output);

// ===  FUNCTION  =============================================================
//         Name:  writeFile(int*,int,int)
//  Description:  Simply writes the result of the matrix into a text file
// ============================================================================
void writeFile( int *matrix, int x1, int y1);

// ===  FUNCTION  =============================================================
//         Name:  extractMatrix(char*,int*)
//  Description:  Get the matrix from the string and put it into an actual int 
//                matrix.
// ============================================================================
void extractMatrix( char *filename, int *C );

// ===  FUNCTION  =============================================================
//         Name:  matrixMult(int*,int,int,int*,int,int)
//  Description:  Performs simple cut and dry matrix mult.
// ============================================================================
int *matrixMult(int *A, int x1, int y1, int *B, int x2, int y2);
