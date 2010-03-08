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

        setMatrixData(argc,&argv);

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

        // We only count the time it takes for this matrix to multiply
        gStartTime = MPI_Wtime();
        // Testing the matrix mult. simple algorithm
        int *newMatrix = matrixMult(A, x1, y1, B, x2, y2);
        gEndTime = MPI_Wtime();
        
        // Write data to file
        writeFile(newMatrix, x1, y2);

        // Clean up
    //    free(A_string);
    //    free(B_string);
        free(newMatrix);
        
        // Print the time it took to Matrix Mult.
        printf("%lf\n",gEndTime-gStartTime);
    }

    MPI_Finalize();
    return 0;
}// ----------  end of function main  ----------
