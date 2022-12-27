#include<stdio.h>
#include<mpi.h>
#include<unistd.h>

int main(){
	int rank;
	int arr[] = {1, 8, 5, 7};				// data to distribute
	int rec[2];						// array to store gathered data. Every process will have it's own rec[2];
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	MPI_Scatter(arr, 2, MPI_INT, rec, 2, MPI_INT, 0, MPI_COMM_WORLD);	// scatter arr with sizes of 2. Rec will recieve it 								  		whose size is 2. The process which scatters has id = 0;
	
	for(int i=0;i<2;i++){							// all ranks shown with the data they have
		printf("Rank: %d recieved %d\n", rank, rec[i]);
	}
	
	for(int i=0;i<2;i++){							// random operation on every process
		rec[i]*= 100;
	}
	
	MPI_Gather(rec, 2, MPI_INT, arr, 2, MPI_INT, 0, MPI_COMM_WORLD);	// gathers data and synchronizes all process
	
	if(rank == 0){								// rank 0 shows all data
		printf("Rank 0 recieved data:\n");
		for(int i=0;i<4;i++){
			printf("%d\n", arr[i]);
		}
	}
	
	MPI_Finalize();
}
