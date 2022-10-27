#include<stdio.h>
#include<mpi.h>
#include<math.h>

int main(int argc, char** argv){
	int number = 10, rank, n_ranks, numbers_per_rank;
	int first = 0, last;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);
	numbers_per_rank = floor(number/n_ranks);
	
	
	if( number%n_ranks > 0 ){
		numbers_per_rank += 1;
 	}
	
	first = rank * numbers_per_rank;
	last  = first + numbers_per_rank;
	
	
	for(int i=first;i<last;i++){
		if(i < number){
			printf("I'm rank %d and I'm printing the number %d.\n", rank, i);
		}
	}
	
	return 	MPI_Finalize();
	
	
}
