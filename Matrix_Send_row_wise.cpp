#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]){
	int rank, comm_size;
	int rows=4, cols=4;		// Assuming that arr size is [4x4] and is sending data row wise to another array of length = 4
	int arr[rows][cols];
	int rec_data[4];
	for(int i=0;i<4;i++){		// fill array randomly
		for(int j=0;j<4;j++){
			arr[i][j] = rand()%10;
		}
	}
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	
	
	if(rank == 0){
		printf("Matrix to send:\n");			// array print
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++){
				printf("%d ", arr[i][j]);
			}
			printf("\n");
		}
		int row_of_arr = 0;				// tells which whole row is being sent
		for(int rank_num=0;rank_num<comm_size;rank_num++){
			MPI_Send(&(arr[row_of_arr]), 4, MPI_INT, rank_num, 100, MPI_COMM_WORLD);
			row_of_arr++;
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);// barrier so that, in output screen arr is the first output.(Makes sure rank 0 gets executed completely first)
	MPI_Recv(rec_data, 4, MPI_INT, 0, 100, MPI_COMM_WORLD, NULL); // recieve from every rank and print row along with rank number
	for(int i=0;i<4;i++){
		printf("RANK: %d, NUMBER: %d\n", rank, rec_data[i]);
	}
	
	MPI_Finalize();

}
