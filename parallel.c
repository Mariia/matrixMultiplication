// ============================================================================
// 
//       Filename:  parallel.c
// 
//    Description:  Will perform matrix multiplication using MPI 
// 
//        Created:  03/08/2010 09:24:50 AM
//       Compiler:  mpicc
// 
//         Author:  Jose V. Trigueros , j.v.trigueros@gmail.com
// 
// ============================================================================

#include "matrixOperations.h"

int main( int argc, char *argv[] )
{
    // Name root being main thread
    int mainThread = 0;

    // Initialize MPI
    initializeMPI(&argc,argv);
     
    // Get sizes of matrix
    // Create the array of matrices
    setMatrixData(argc,argv);

    // Root Processor will do the following
    if( gRank == 0 )
    {
        extractMatrix(gMatrixA,A);
        extractMatrix(gMatrixB,B);

        // Once done spread the wealth
        MPI_Bcast(A, gX1*gY1, MPI_INT, mainThread, MPI_COMM_WORLD);
        MPI_Bcast(B, gX2*gY2, MPI_INT, mainThread, MPI_COMM_WORLD);
    }
    else
    {
        // Get the wealth
        MPI_Bcast(A, gX1*gY1, MPI_INT, mainThread, MPI_COMM_WORLD);
        MPI_Bcast(B, gX2*gY2, MPI_INT, mainThread, MPI_COMM_WORLD);
    }

    // At this point everyone should have Matrix A and B
    // It is time to start distributing 

    // Create temporary matrix
    int * tempC = (int *)malloc(sizeof(int)*(gX1));

    // Check how many threads we have
    printf("%d \n", gNumProcessors);
    if( gNumProcessors >= (gY2+1) )
    {
        // So we have enough processors to cover all columns
        int i, j, tempSum = 0;
        for( i = 0; i < gX1 ; i++ )
        {
            for( j = 0; j < gY1 ; j++ )
            {
                tempSum += A[i*(gY1) + j]*B[j*gY2 + gRank];
            }
            tempC[i] = tempSum;
            tempSum = 0;
        }
    }

    // Everybody should have their data now so let's sync
    MPI_Barrier(MPI_COMM_WORLD);

    // Print vector
    if( tempC != NULL && gRank == 0 )
    {
        int i;
        for( i = 0; i < gX1; i++ )
        {
            printf("My rank is: %d\n" , gRank);
            printf("%d ", tempC[i]);
            puts("");
        }
    }


    // Free Data
    free(tempC);
    freeMatrixData();

    // Finalize MPI
    MPI_Finalize();

    return 0;
}// ----------  end of function main  ----------

