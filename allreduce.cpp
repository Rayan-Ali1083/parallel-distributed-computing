#include<stdio.h>
#include<mpi.h>

int main(){
	int rank, comm_sz, all_red_res;
	int arr[] = {5, 8, 5, 7, 6, 7, 1, 2, 3, 5};
	int ele_per_proc;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	ele_per_proc = 	10/comm_sz;
	int local_sum;
	
	for(int i=rank*ele_per_proc;i<ele_per_proc+(rank*ele_per_proc);i++){
		local_sum += arr[i];
	}
	
	printf("RANK = %d LOCAL SUM= %d\n", rank, local_sum);
	
	MPI_Allreduce(&local_sum, &all_red_res, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	
	printf("RANK = %d SUM= %d\n", rank, all_red_res);
	
	MPI_Finalize();
}
