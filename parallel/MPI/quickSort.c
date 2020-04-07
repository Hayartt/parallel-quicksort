//INCOMPLETE - ELAAF


#include "quickSort.h"
void parallelQuicksort(int* a, int n, int first, int last);

int main(int argc, char* argv[])
{
	int n = strtol(argv[1], NULL, 10);
	int a[n];
	int rank, size;

	
	rand_arr_gen(a, n);
	print_arr(a, n);

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	parallelQuicksort(a, 0, n, (n - 1));


	MPI_Finalize();

	print_arr(a, n);
}


void parallelQuicksort(int* a, int n, int first, int last)
{
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	printf("hi\n");
	int partition_index;
		if (first < last) {

			partition_index = partition(a, first, last);

			if (rank%2==0) 
			{
				MPI_Send(a, partition_index - 1, MPI_INT, rank, partition_index, MPI_COMM_WORLD);
				parallelQuicksort(a, n, first, partition_index - 1);
				MPI_Recv(a, partition_index - 1, MPI_INT, rank, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}
			else
			{
				MPI_Send((a + partition_index + 1), n - partition_index - 1, MPI_INT, rank, partition_index + 1, MPI_COMM_WORLD);
				parallelQuicksort(a, n, partition_index + 1, last);
				MPI_Recv((a + partition_index + 1), n - partition_index - 1, MPI_INT, rank, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}
		}

}