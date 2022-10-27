#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]){
	int rank, comm_size;
	int rows=4, cols=4;		// Assuming that arr size is [4x4] and is sending data row wise to another array of length = 4
	int arr[rows][cols];
	int MAT_MUL[4][1] = {
				{2},
				{3},
				{4},
				{5}
				};
	int ANS[4][1];
	int rec_data[4][1];
	int FINAL_RECV[4][1];
	for(int i=0;i<4;i++){		// fill array randomly
		for(int j=0;j<4;j++){
			arr[i][j] = rand()%10;
		}
	}
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	
	
	if(rank == 0){
		printf("MATRIX ARR:\n");			// array print. We will be sending this matrix
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++){
				printf("%d ", arr[i][j]);
			}
			printf("\n");
		}
		printf("MATRIX TO MULTIPLY WITH MATRIX ARR:\n");
		for(int i=0;i<4;i++){
			printf("%d\n", MAT_MUL[i][0]);
		}
		int row_of_arr = 0;				// tells which whole row is being sent
		
		for(int rank_num=0;rank_num<comm_size;rank_num++){
			MPI_Send(&(arr[row_of_arr]), 4, MPI_INT, rank_num, 100, MPI_COMM_WORLD);
			row_of_arr++;
		}
		
		
		
	}
	MPI_Barrier(MPI_COMM_WORLD);// barrier so that, in output screen arr is the first output.(Makes sure rank 0 gets executed completely first)
	
	MPI_Recv(rec_data, 4, MPI_INT, 0, 100, MPI_COMM_WORLD, NULL); // recieve from every rank and print row along with rank number
	
	
	for(int a_index=0;a_index<rows;a_index++){			// row wise calculated and and answer is now in ANS matrix
		for(int i=0;i<rows;i++){
			 ANS[a_index][0] += MAT_MUL[i][0] * rec_data[i][0];
		}
	}
	// time to send ANS matrix to rank 0 where it will be printed
	
	MPI_Send(&(ANS[rank]), 1, MPI_INT, 0, 100, MPI_COMM_WORLD);
	printf("SENDING %d to RANK %d\n", *(ANS[rank]), rank);
	
	MPI_Barrier(MPI_COMM_WORLD);					// using barrier for aligned output
	if(rank == 0){
		for(int i=0;i<comm_size;i++){
			MPI_Recv(FINAL_RECV[i], 1, MPI_INT, i, 100, MPI_COMM_WORLD, NULL);
		}
		printf("FINAL ANSWER:\n");
		for(int i=0;i<comm_size;i++){
			printf("%d\n", FINAL_RECV[i][0]);
		}
	}
	
	MPI_Finalize();

}
