#include<stdio.h>
#include<mpi.h>

int main(){
	int rank;
	int n = 100;	
	
	MPI_Init(NULL, NULL);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(rank == 0){
		printf("I, %d PROCESS WILL TELL EVERYONE THE SECRET CODE!!!\n", rank);
	}
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	if(rank!=0){
		printf("WHY ARE YOU TELLING %d PROCESS YOUR PINCODE : %d?\n", rank, n);
	}
	
	MPI_Finalize();	
}
