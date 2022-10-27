#include<stdio.h>
#include<mpi.h>

int main(){
	int rank;
	int n = 100;	
	
	MPI_Init(NULL, NULL);
	
	// incomplete
	MPI_Finalize();	
}
