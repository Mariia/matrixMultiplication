// ============================================================================
// 
//       Filename:  main.h
// 
//    Description:  Contain matrix operations
// 
//        Created:  03/03/2010 04:53:39 PM
//       Compiler:  g**
// 
//         Author:  Jose V. Trigueros (), j.v.trigueros@gmail.com
// 
// ============================================================================
   
   
#include <stdio.h>
#include <stdlib.h>


// ===  FUNCTION  =============================================================
//         Name:  readFile(char*,char*)
//  Description:  Reads a file and puts it in a string that the caller passed 
//                as reference.
// ============================================================================
void readFile( char *filename , char** output);

void writeFile( int *matrix, int x1, int y1);

// ===  FUNCTION  =============================================================
//         Name:  extractMatrix(char*,int*)
//  Description:  Get the matrix from the string and put it into an actual int 
//                matrix.
// ============================================================================
void extractMatrix( char *matrix, int *C );

// ===  FUNCTION  =============================================================
//         Name:  matrixMult(int*,int,int,int*,int,int)
//  Description:  Performs simple cut and dry matrix mult.
// ============================================================================
int *matrixMult(int *A, int x1, int y1, int *B, int x2, int y2);
