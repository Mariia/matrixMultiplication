// ============================================================================
// 
//       Filename:  matrixOperations.c
// 
//    Description:  Contains the implementations of the matrix operations, 
//                  including intializing MPI and getting the information from
//                  a file.
// 
//        Created:  03/08/2010 02:16:50 AM
//       Compiler:  mpicc
// 
//         Author:  Jose V. Trigueros , j.v.trigueros@gmail.com
// 
// ============================================================================

#include "matrixOperations.h"

void initializeMPI(int * argc, char ** argv)
{
    // Initialize MPI
    int mpiStatus = MPI_Init(argc,&argv);
    if( mpiStatus != MPI_SUCCESS )
    {
        // Something went wrong and we must quit
        printf("Something went wrong with MPI and we must quit\n");
        MPI_Abort(MPI_COMM_WORLD, mpiStatus );
    }

    // Returns the number of processors
    MPI_Comm_size(MPI_COMM_WORLD, &gNumProcessors);

    // Returns the current processor ID
    MPI_Comm_rank(MPI_COMM_WORLD, &gRank);
}

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
