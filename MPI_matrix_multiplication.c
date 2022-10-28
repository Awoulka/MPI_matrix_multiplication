#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"
#include <time.h>
#include <sys/time.h>

/*
  In here 'process o' which distribute the workload to other processes is considered 
  as Root (Master) process and other processes which do the computation is considered 
  as Slave task processes. 
*/

// Number of rows and columnns in a matrix
#define N 100

MPI_Status status;

// Matrix holders are created
//double matrix_a[N][2],matrix_b[2][3],matrix_c[N][N];
//double matrix_a[3][3] = {{1,2,3},{2,5,6},{2,3,7}}, matrix_b[3][3]= {{-1,6,7},{8,9,-7},{-6,5,2}},matrix_c[N][N];
int m=3,n=3,p=3,q=3;
double matrix_a[N][N] = {{1,2,3},{2,5,6},{2,3,7}}, matrix_b[N][N]= {{-1,6,7},{8,9,-7},{-6,5,2}},matrix_c[N];
//double a[]= {1,1}, b[2][4]= {{0,1,-1,-2},{-3,-2,0,1}},c[4];
double data[N];

int main(int argc, char **argv)
{
struct timeval start, end;
  int processCount, processId, slaveTaskCount, source, dest, rows, offset,n=0;

  //struct timeval start, stop;

// MPI environment is initialized
  MPI_Init(&argc, &argv);
// Each process gets unique ID (rank)
  MPI_Comm_rank(MPI_COMM_WORLD, &processId);
// Number of processes in communicator will be assigned to variable -> processCount
  MPI_Comm_size(MPI_COMM_WORLD, &processCount);

// Number of slave tasks will be assigned to variable -> slaveTaskCount
  slaveTaskCount = processCount - 1;

// Root (Master) process


 if (processId == 0) {
 
 
 gettimeofday(&start, NULL);
 for (int i = 0; i<q; i++) {

	for (int j = 0; j<q; j++) {
		      
		data[n]=matrix_a[i][processId]*matrix_b[processId][j];
		
		n++;
	}
	
	/*printf("\npreocess %d:\n",processId);

	      for (int j = 0; j<q; j++)
		printf("%.0f\t", data[j]);
	    
	    printf ("\n");*/
     		
 }
 
 MPI_Reduce(&data, &matrix_c, p*q, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

gettimeofday(&end, NULL);

 	int l=0;
 	printf("\nResult Matrix C = Matrix A * Matrix B:\n\n");
 	
	    for (int i = 0; i<m*q; i++) {
	      //for (int j = 0; j<q; j++)
		printf("%.0f\t", matrix_c[i]);
	      if( l==q-1){
	     	 
	     	printf ("\n");
	     	l=-1;
	      }
	      l++;
	    }
	    printf ("\n");
	long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
    printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);

      
  }
  
  	


 	
// Slave Processes 
  if (processId > 0) {
  
 
 for (int i = 0; i<q; i++) {

	for (int j = 0; j<q; j++) {
		      
		data[n]=matrix_a[i][processId]*matrix_b[processId][j];
		
		n++;
	}
	
	/*printf("\npreocess %d:\n",processId);

	      for (int j = 0; j<q; j++)
		printf("%.0f\t", data[j]);
	    
	    printf ("\n");*/
     		
 }
 
 MPI_Reduce(&data, &matrix_c, p*q, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);


  }

  MPI_Finalize();
}
