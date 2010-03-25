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
    double * finalMatrix;

    // Initialize MPI
    initializeMPI(&argc,argv);

    // Start tracking time
    if( gRank == g_mainThread )
        gStartTime = MPI_Wtime();

    // Get sizes of matrix
    // Create the array of matrices
    setMatrixData(argc,argv);

    // Root Processor will do the following
    if( gRank == g_mainThread )
    {
        extractMatrix(gMatrixA,A);
        extractMatrix(gMatrixB,B);

        // Once done spread the wealth
        MPI_Bcast(A, gX1*gY1, MPI_DOUBLE, g_mainThread, MPI_COMM_WORLD);
        MPI_Bcast(B, gX2*gY2, MPI_DOUBLE, g_mainThread, MPI_COMM_WORLD);
    }
    else
    {
        // Get the wealth
        MPI_Bcast(A, gX1*gY1, MPI_DOUBLE, g_mainThread, MPI_COMM_WORLD);
        MPI_Bcast(B, gX2*gY2, MPI_DOUBLE, g_mainThread, MPI_COMM_WORLD);
    }

    // At this point everyone should have Matrix A and B
    // It is time to start distributing 

    // Create temporary matrix
    double * tempC = (double *)malloc(sizeof(double)*(gX1));

    // Check how many threads we have
    if( gNumProcessors >= gY2 )
    {
        // So we have enough processors to cover all columns
        int i, j; 
        double tempSum = 0.0;
        for( i = 0; i < gX1 ; i++ )
        {
            for( j = 0; j < gY1 ; j++ )
            {
                tempSum += A[i*(gY1) + j]*B[j*gY2 + gRank];
            }
//            printf("%lf \n", tempSum);
            tempC[i] = tempSum;
            tempSum = 0;
        }
    }
    else
    {
        puts("I only support square matrices");
        return 1;
    }

    // Everybody should have their data now so let's sync
//    MPI_Barrier(MPI_COMM_WORLD);

    // Only the root node should 
    if( gRank == g_mainThread )
    {
        // Create a new array to collect all the data into
        finalMatrix = (double *)malloc(sizeof(double)*(gX1*gY2));
        MPI_Status status;
        
        // Store g_mainThreads Data in the finalMatrix
        int i;
        for(i = 0; i < gX1; i++)
        {
            finalMatrix[i*gY2+g_mainThread] = tempC[i];
        }

        // Start receiving all the data
        int currentRank;
        for( currentRank = g_mainThread + 1; currentRank < gNumProcessors; currentRank++)
        {
            // Create temp vector 
            double * tempVector = ( double * )malloc(sizeof(double)*gX1);
            MPI_Recv(tempVector,gX1,MPI_DOUBLE,currentRank,currentRank,MPI_COMM_WORLD, &status);
            // Collect all vectors into the matrix
            for(i = 0; i < gX1; i++)
            {
                finalMatrix[i*gY2+currentRank] = tempVector[i];
            }
            free(tempVector);
        }
    }
    else
    {
        // Start sending 
        MPI_Send(tempC, gX1, MPI_DOUBLE, g_mainThread,gRank,MPI_COMM_WORLD);
    }

    //Get the final time now
    if( gRank == g_mainThread )
    {
        gEndTime = MPI_Wtime();
        printf("%lf\n",gEndTime-gStartTime);
    }

    // At this time all data should be on g_mainThread so write it to file
    if( gRank == g_mainThread )
        writeFile(finalMatrix, gX1, gY2);    

    // Free Data
    free(tempC);
    if( gRank == g_mainThread )
        free(finalMatrix);
    freeMatrixData();
    
    // Finalize MPI
    MPI_Finalize();

    return 0;
}// ----------  end of function main  ----------

