#include<stdio.h>
#include<mpi.h>

int main(){
	int rank, n_ranks;
	
	
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);
	
	if(n_ranks < 2){
		printf("WILL ONLY WORK FOR n_ranks > 2") ;
		return MPI_Finalize();
	}
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if(rank == 0){
		printf("Hello from Sender !!!\n");
		printf("Enter data:\n");
		char data[10];
		scanf("%[^\n]s", data);
		MPI_Send(&data, 10, MPI_CHAR, 1, 100, MPI_COMM_WORLD);
	}else{
		char rec_data[10];
		MPI_Status status;
		MPI_Recv(&rec_data, 10, MPI_CHAR, 0, 100, MPI_COMM_WORLD, &status);
		printf("Recieved data: %s\n", rec_data);
		int count;
		MPI_Get_count(&status, MPI_CHAR, &count);
		printf("Number of elements recieved: %d\n", status);
	}
	return MPI_Finalize();

}
