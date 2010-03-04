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


// ===  FUNCTION  =============================================================
//         Name:  extractMatrix(char*,int*)
//  Description:  Get the matrix from the string and put it into an actual int 
//                matrix.
// ============================================================================
void extractMatrix( char *matrix, int *C );
