// ============================================================================
// 
//       Filename:  parallel.c
// 
//    Description:  Will perform matrix computation using MPI 
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
    // Initialize MPI
    initializeMPI(&argc,argv);
     
     // Only root the root node should do this
//     if ( gRank == 0 )
//     {
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

        extractMatrix(gMatrixA,A);
        extractMatrix(gMatrixB,B);
//     }
    // Test by having each processor print a number from MatA
    printf("Processor %d: %d\n",gRank, A[gRank]);
    // Finalize MPI
    MPI_Finalize();
    return 0;
}// ----------  end of function main  ----------

