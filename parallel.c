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
    }
    else
    {
        // Get the wealth
        MPI_Bcast(A, gX1*gY1, MPI_INT, mainThread, MPI_COMM_WORLD);
    }

    // At this point everyone should have Matrix A

    // Test by having each processor print a number from MatA
    printf("Processor %d: %d\n",gRank, A[gRank]);


    // Free Data
    freeMatrixData();

    // Finalize MPI
    MPI_Finalize();

    return 0;
}// ----------  end of function main  ----------

