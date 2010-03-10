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

#include "matrixOperations.h"

int main( int argc, char *argv[] )
{
    initializeMPI(&argc,argv);
    gStartTime = MPI_Wtime();

    // Only the root node should run all this code
    if( gRank == 0 && argc == 4)
    {
        // Reading input from command line arguments
        // Should only have 3 arguments passed
        if ( argc != 4 ) 
        {
            printf("%d argument(s) given." , argc - 1);
            return 1;
        }

        // Get sizes of matrix
        // Create the array of matrices
        setMatrixData(argc,argv);
        extractMatrix(gMatrixA,A);
        extractMatrix(gMatrixB,B);

        // Testing the matrix mult. simple algorithm
        double *newMatrix = matrixMult(A, gX1, gY1, B, gX2, gY2);
        gEndTime = MPI_Wtime();
        
        // Write data to file
        writeFile(newMatrix, gX1, gY2);

        free(newMatrix);
        freeMatrixData();
        // Print the time it took to Matrix Mult.
        printf("%lf\n",gEndTime-gStartTime);
    }

    MPI_Finalize();
    return 0;
}// ----------  end of function main  ----------
