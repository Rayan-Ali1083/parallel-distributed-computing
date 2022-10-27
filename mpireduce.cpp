#include<stdio.h>
#include<mpi.h>

int main(){
	int rank, comm_sz, red_res=0;
	int arr[10] = {1, 4, 7, 5, 7, 8, 4, 9, 1, 56};
	int ele_per_proc;
	MPI_Init(NULL, NULL);
	int local_sum;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	
	ele_per_proc = 10/comm_sz;
	
	for(int i=rank*ele_per_proc;i<ele_per_proc+(rank*ele_per_proc);i++){
		local_sum += arr[i];
	}
	printf("local sum = %d rank = %d\n", local_sum, rank);
	
	MPI_Reduce(&local_sum, &red_res, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if(rank == 0)
	printf("Total Sum = %d, rank number = %d\n", red_res, rank);
	
	MPI_Finalize();
}
