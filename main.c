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

    extractMatrix(matrixA,A);
    extractMatrix(matrixB,B);

    // Read Files
//    char* A_string = NULL;
//    char* B_string = NULL;

//    int i;
//    for( i = 0; i < x2*y2 ; i++)
//        printf("%d ", B[i]);

    // Get the matrix into a string
//    readFile(matrixA, &A_string);
//    readFile(matrixB, &B_string);

    // Get the string matrix into an actual int array
//    extractMatrix(A_string, A);
//    extractMatrix(B_string, B);

    // Testing the matrix mult. simple algorithm
    int *newMatrix = matrixMult(A, x1, y1, B, x2, y2);
    
    // Write data to file
    writeFile(newMatrix, x1, y2);

    // Clean up
//    free(A_string);
//    free(B_string);
    free(newMatrix);
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
    *output = (char *)malloc(fileSize);

    // Read data into buffer and return the value of stuff read to count
    count = fread(*output, 1, fileSize, fp);

    // Make sure we read the same amount
    if ( count != fileSize)
    {
        fputs("File was not read properly.\n", stderr);
        exit(1);
    }
    // This will write into memory that you don't want 
    // Make it a null terminated string
    output[fileSize] = '\0';

    free(output);

    fclose(fp);
}

void extractMatrix( char *filename, int *C )
{
    FILE *file = fopen(filename, "rb");
    int i;
    int element; 
    for( i = 0; fscanf(file,"%d",&element) != EOF ; i++ )
    {
        C[i] = element;
    }
    // Done
}

void writeFile( int *matrix, int x1, int y1)
{
    FILE *output = fopen("C.txt", "w");
    int x,y;

    // Write out the matrix in the ouput file
    for( x = 0; x < x1; x++ )
    {
        for( y = 0; y < y1-1; y++ )
        {
            fprintf(output,"%d ", matrix[x*y1 + y]);
        }
        // This will prevent the extraspace and instead let's put a newline
        fprintf(output,"%d\n", matrix[x*y1 + y]);
    }

    //Clean up
    fclose(output);
}

int *matrixMult(int *A, int x1, int y1, int *B, int x2, int y2)
{
    // Row-major Order: row*NUMOFCOLS+column
    // Create new matrix
    int *multMatrix = (int *)malloc(sizeof(int)*(x1*y2));
    int k,x,y,result = 0;
    
    for( k = 0; k < y2 ; k++)
    {
        // Move row
        for( x = 0 ; x < x1 ; x++ )
        {
            for ( y = 0; y < y1 ; y++ )
            {
                result += A[x*(y1) + y]*B[y*(y2) + k];
//                printf("%d %d\n",A[x*(y1) + y],B[y*(y2) + k]);
            }
            multMatrix[x*y2+k] = result;
            result = 0;
        }
    }
    return multMatrix;
}

//void extractMatrix( char *matrix, int *C )
//{
//    // This is assuming that there will only be 4 digits
//    char temp[4];
//    char currentChar = '$';
//    int i = 0;
//    int j = 0;
//    int k = 0;
//    do
//    {
//        if( matrix[i] != ' ' && matrix[i] != '\n' )
//        {
//            currentChar = matrix[i];
//            temp[j] = matrix[i];
//            j++;
//            i++;
//        }
//        else
//        {
//            C[k] = atoi(temp);
//            i++;
//            currentChar = matrix[i];
//            j = 0;
//            k++;
//        }
//    }while( currentChar != '\0' );
//}
//
