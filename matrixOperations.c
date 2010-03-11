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

void setMatrixData(int argc, char ** argv)
{
    // Get data from command line arguments
    gX1 = atoi(argv[1]);
    gY1 = atoi(argv[2]);
    gX2 = atoi(argv[2]);
    gY2 = atoi(argv[3]);

    // Allocate space for Matrices 
    A = (double *)malloc( sizeof(double)*(gX1*gY1) );
    B = (double *)malloc( sizeof(double)*(gX2*gY2) );
}

void freeMatrixData()
{
    free(A);
    free(B);
}

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

// This may not be used anymore
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

void extractMatrix( char *filename, double *C )
{
    FILE *file = fopen(filename, "rb");
    int i;
    double element; 
    for( i = 0; fscanf(file,"%lf",&element) != EOF ; i++ )
    {
        C[i] = element;
    }
    // Done
}

void writeFile( double *matrix, int x1, int y1)
{
    FILE *output = fopen("C.txt", "w");
    int x,y;

    // Write out the matrix in the ouput file
    for( x = 0; x < x1; x++ )
    {
        for( y = 0; y < y1-1; y++ )
        {
//            fprintf(output,"%lf ", matrix[x*y1 + y]);
            fprintf(output,"%d ", (int)rint(matrix[x*y1 + y]));
        }
        // This will prevent the extraspace and instead let's put a newline
//        fprintf(output,"%lf\n",(int)matrix[x*y1 + y]);
        fprintf(output,"%d\n",(int)rint(matrix[x*y1 + y]));
    }

    //Clean up
    fclose(output);
}

double *matrixMult(double *A, int x1, int y1, double *B, int x2, int y2)
{
    // Row-major Order: row*NUMOFCOLS+column
    // Create new matrix
    double *multMatrix = (double *)malloc(sizeof(double)*(x1*y2));
    int k,x,y;
    double result = 0.0;
    
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

void CannonAlgorithm(int n, double *a, double *b, double *c, MPI_Comm comm) 
{ 
      int i; 
      int nlocal; 
      int npes, dims[2], periods[2]; 
      int myrank, my2drank, mycoords[2]; 
      int uprank, downrank, leftrank, rightrank, coords[2]; 
      int shiftsource, shiftdest; 
      MPI_Status status; 
      MPI_Comm comm_2d; 
   
      /* Get the communicator related information */ 
      MPI_Comm_size(comm, &npes); 
      MPI_Comm_rank(comm, &myrank); 
   
      /* Set up the Cartesian topology */ 
      dims[0] = dims[1] = sqrt(npes); 
   
      /* Set the periods for wraparound connections */ 
      periods[0] = periods[1] = 1; 
   
      /* Create the Cartesian topology, with rank reordering */ 
      MPI_Cart_create(comm, 2, dims, periods, 1, &comm_2d); 
   
      /* Get the rank and coordinates with respect to the new topology */ 
      MPI_Comm_rank(comm_2d, &my2drank); 
      MPI_Cart_coords(comm_2d, my2drank, 2, mycoords); 
   
      // There needs to be some switching done here
      /* Compute ranks of the up and left shifts */ 
      MPI_Cart_shift(comm_2d, 0, -1, &rightrank, &leftrank); 
      MPI_Cart_shift(comm_2d, 1, -1, &downrank, &uprank); 
   
      /* Determine the dimension of the local matrix block */ 
      nlocal = n/dims[0]; 
   
      /* Perform the initial matrix alignment. First for A and then for B */ 
      MPI_Cart_shift(comm_2d, 0, -mycoords[0], &shiftsource, &shiftdest); 
      MPI_Sendrecv_replace(a, nlocal*nlocal, MPI_DOUBLE, shiftdest, 
          1, shiftsource, 1, comm_2d, &status); 
   
      MPI_Cart_shift(comm_2d, 1, -mycoords[1], &shiftsource, &shiftdest); 
      MPI_Sendrecv_replace(b, nlocal*nlocal, MPI_DOUBLE, 
          shiftdest, 1, shiftsource, 1, comm_2d, &status); 
   
      /* Get into the main computation loop */ 
      for (i=0; i<dims[0]; i++) { 
        MatrixMultiply(nlocal, a, b, c); /*c=c+a*b*/ 
   
        /* Shift matrix a left by one */ 
        MPI_Sendrecv_replace(a, nlocal*nlocal, MPI_DOUBLE, 
            leftrank, 1, rightrank, 1, comm_2d, &status); 
      printf("Proc1: %d\nProc2: %d Dims:%d\n",my2drank,gRank,i); 
   
        /* Shift matrix b up by one */ 
        MPI_Sendrecv_replace(b, nlocal*nlocal, MPI_DOUBLE, 
            uprank, 1, downrank, 1, comm_2d, &status); 
      } 
   
      /* Restore the original distribution of a and b */ 
      MPI_Cart_shift(comm_2d, 0, +mycoords[0], &shiftsource, &shiftdest); 
      MPI_Sendrecv_replace(a, nlocal*nlocal, MPI_DOUBLE, 
          shiftdest, 1, shiftsource, 1, comm_2d, &status); 
   
      MPI_Cart_shift(comm_2d, 1, +mycoords[1], &shiftsource, &shiftdest); 
      MPI_Sendrecv_replace(b, nlocal*nlocal, MPI_DOUBLE, 
          shiftdest, 1, shiftsource, 1, comm_2d, &status); 
   
      MPI_Comm_free(&comm_2d); /* Free up communicator */ 
}

    /* This function performs a serial matrix-matrix multiplication c = a*b */ 
void MatrixMultiply(int n, double *a, double *b, double *c) 
{ 
    int i, j, k; 

    for (i=0; i<n; i++) 
    for (j=0; j<n; j++) 
    for (k=0; k<n; k++) 
    c[i*n+j] += a[i*n+k]*b[k*n+j]; 
}
