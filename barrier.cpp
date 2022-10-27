#include<stdio.h>
#include<mpi.h>
#include<unistd.h>
int main(){
	int rank;
	MPI_Init(NULL, NULL);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if(rank == 0){
		printf("MASTER SLEEPS TONIGHT\n");
		sleep(5);
	}else{
		printf("FUCKING SLAVES WORKING THEIR ASS OFF\n");
	}
	
	if(rank != 0){
		printf("CANT FUCKING MOVE WITHOUT MASTER.\nFUCKING WAKEUP!!!\n");
	}
	MPI_Barrier(MPI_COMM_WORLD);
	printf("MASTER IS AWAKE. THANKS FOR WAITING XD\n"); // all threads will wait for master and then execute this line
	MPI_Finalize();
}
