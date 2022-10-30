#include<stdio.h>
#include<mpi.h>

#define N 4

int main(){
	int rank, comm_size,rec[N];
	int arr[N][N];
	int e_ans, o_ans;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			arr[i][j] = rand()%10;
		}
	}
	
	MPI_Init(NULL, NULL);
	int even, odd;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	
	if(rank == 0){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				printf("%d ",arr[i][j]);
			}
		printf("\n");
	}
	}
	
	MPI_Scatter(&(arr), 4, MPI_INT, &rec, 4, MPI_INT, 0, MPI_COMM_WORLD);
	
	for(int i=0;i<N;i++){
		printf("%d ",rec[i]);
		if(rec[i]%2!=0){
			odd++;
		}else{
			even++;
		}
	}
	
	MPI_Reduce(&odd, &o_ans,1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&even, &e_ans,1, MPI_INT, MPI_SUM, 1, MPI_COMM_WORLD);
	printf("\n");
	MPI_Barrier(MPI_COMM_WORLD);
	if(rank == 0 ){
		printf("ODD= %d\n", o_ans);
	}else if(rank == 1){
		printf("EVEN= %d\n", e_ans);
	}
	MPI_Finalize();
	
}
