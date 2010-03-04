// ============================================================================
// 
//       Filename:  main.c
// 
//    Description:  Simple Matrix Multiplication
// 
//        Created:  03/03/2010 01:23:46 PM
// 
//         Author:  Jose V. Trigueros , j.v.trigueros@gmail.com
// 
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

#define matrixA "A.txt"
#define matrixB "B.txt"

int main( int argc, char *argv[] )
{
    // Reading input from command line arguments
    // Should only have 3 arguments passed
    if ( argc != 4 ) 
    {
        printf("%d argument(s) given." , argc - 1);
        return 1;
    }

    // Get sizes of matrix
    int x1 = atoi(argv[1]);
    int y1 = atoi(argv[2]);
    int x2 = atoi(argv[2]);
    int y2 = atoi(argv[3]);

    int const A_SIZE = x1*y1;
    int const B_SIZE = x2*y2;

    // Create the array of matrices
    int A[A_SIZE];
    int B[B_SIZE];

    // Read Files
    char* A_string = NULL;
    char* B_string = NULL;

    readFile(matrixA, &A_string);
    readFile(matrixB, &B_string);

    extractMatrix(A_string, A);
    extractMatrix(B_string, B);

    printf("%d %d %d %d\n%s\n%s", x1, y1, x2, y2, A_string, B_string);     

    int i = 0;
    for( i = 0; i < A_SIZE ; i++)
        printf("%d ", A[i]);
    puts("");

    for( i = 0; i < B_SIZE ; i++)
        printf("%d ", B[i]);
    puts("");
    return 0;
}// ----------  end of function main  ----------

void readFile( char *filename , char** output)
{
    FILE *fp = fopen(filename,"rb");
    long fileSize;
    int count;

    // Test to see if the file was read properly
    if ( fp == NULL ) 
    {
        fputs("File was not read properly.\n", stderr);
        exit(1);
    }

    // Get file size
    fseek(fp, 0,SEEK_END);
    fileSize = ftell(fp);
    rewind(fp);

    // Allocate memory for buffer
    *output = (char *)malloc(fileSize + 1);

    // Read data into buffer and return the value of stuff read to count
    count = fread(*output, 1, fileSize, fp);

    // Make sure we read the same amount
    if ( count != fileSize)
    {
        fputs("File was not read properly.\n", stderr);
        exit(1);
    }
    // Make it a null terminated string
    output[count] = '\0';

//    printf("%s", *output);
    // Clean up
    fclose(fp);
}

void extractMatrix( char *matrix, int *C )
{
    // This is assuming that there will only be 4 digits
    char temp[4];
    char currentChar = '$';
    int i = 0;
    int j = 0;
    int k = 0;
    do
    {
        if( matrix[i] != ' ' && matrix[i] != '\n' )
        {
            temp[j] = matrix[i];
            j++;
            i++;
        }
        else
        {
            C[k] = atoi(temp);
            i++;
            j = 0;
            k++;
        }
    }while( currentChar != '\0' );
}
