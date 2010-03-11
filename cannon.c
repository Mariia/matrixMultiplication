#include "matrixOperations.h"

int main( int argc, char *argv[] )
{
    initializeMPI(&argc, argv);
    int mainThread = 0;
    
    printf("%d ", gNumProcessors);
     
    setMatrixData(argc,argv); 
    double * C = (double *)malloc( sizeof(double)*(gX1*gY2) );
    CannonAlgorithm(gX1,A,B,C,MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    if( gRank == 0 )
    {
        writeFile(C,gX1,gY1);
    }

    // Free allocated data
    freeMatrixData();
    MPI_Finalize();
    return 0;
}// ----------  end of function main  ----------
