/* File:     parallel_quicksort.c
 *
 * Purpose:  Implement parallel quicksort.
 *
 * Compile:  gcc -g -Wall -fopenmp -o parallel_quicksort parallel_quicksort.c
 * 		 or	 clang -Xpreprocessor -fopenmp -I/usr/local/include -L/usr/local/lib -lomp  parallel_quicksort.c -o parallel_quicksort
 * Run:      Performance Evaluation:	./parallel_quicksort [initial array size] [initial thread count] 1
 * 			 Normal Execution:			./parallel_quicksort [n] [thread_count] 0
 *
 * Ithread_countut:    Number of elements in the array. (n)
 *			 Number of processes. (thread_count)
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void rand_arr_gen(int arr[], int n);
void print_arr(int arr[], int n);
void quicksort(int arr[], int first, int last);
int partition(int arr[], int first, int last);
void swap(int* i, int* j);
int verify(int arr[], int n);
void run(int arr[], int n);
void Usage(char* prog_name);
void copy_arr(int src[], int dest[], int n);

double start, elapsed;

/*------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
	if (argc < 4) {
		Usage(argv[0]);
		return -2;
	}
	int n = strtol(argv[1], NULL, 10);
	int thread_count = strtol(argv[2], NULL, 10);
	int timed_opt = strtol(argv[3], NULL, 2);
	if (timed_opt) {			/*	timed execution	*/ 
		for (int j = n; j <= n * 16; j *= 2) {
			int a[j], b[j];
			rand_arr_gen(a,j); // generate random array for tests
			copy_arr(a,b,j); // copy into temp array for in-place sorting by i processes
			for (int i = thread_count; i <= thread_count*16; i*=2) {
				#	pragma omp parallel num_threads(i) \
				default(none) shared(b, j)
				{ // start parallel block
					#	pragma omp single nowait
					{
						start = omp_get_wtime();
						quicksort(b, 0, j - 1);
					}
				} // end of parallel block
				printf("np=%d and sz=%d:\t\t%f\tmilliseconds\n", i,j, (elapsed * 1000));
				if (verify(b, j) == 0) {
					printf("failed\n");
				} // non-parallel validation for the result
				copy_arr(a,b,j); // rewrite b to be the same for all parallel tests (values of i)
			}
		}
	} else {			/*	normal execution	*/ 
		int a[n];
		for (int i = 0; i < 1000; i++) {
			rand_arr_gen(a,n);
			#	pragma omp parallel num_threads(thread_count) \
			default(none) shared(a, n)
			{ // start parallel block
				#	pragma omp single nowait // single process executes this block
				{
					start = omp_get_wtime(); // start the timer
					quicksort(a, 0, n - 1);
				}
			} // end of parallel block
			//printf("Parallel time: %f milliseconds\n", (elapsed * 1000));
			if (verify(a, n) == 0) {
				printf("failed\n");
			} // non-parallel validation for the result
		}
	}
	return 0;
}

/*--------------------------------------------------------------------
 * Function:    copy_arr
 * Purpose:     Copies the contents of an array src to an array dest of the same size
 * In arg:      the source, the destination array, and the size n
 */
void copy_arr(
	int src[],	/* in  */
	int dest[]	/* out */,
	int n		/* in  */) {
		for (int i = 0; i < n; i++) {
			dest[i] = src[i];
		}
}  /* copy_arr */


/*--------------------------------------------------------------------
 * Function:    Usage
 * Purpose:     Print command line for function and terminate
 * In arg:      prog_name
 */
void Usage(char* prog_name) {

   fprintf(
	   stderr, 
	   "usage:\nNormal execution:\t%s <array size> <number of threads> 0\nor\nPerformance comparison\t%s <initial array size> <initial number of threads> 1\n", 
	   prog_name,
	   prog_name);
}  /* Usage */

/*-------------------------------------------------------------------
 * Function:   rand_arr_gen
 * Purpose:    Generates n random integer values in the range [1,n] to fill an array.	(Auxiliary function)
 * In args:    arr:		array
 *             n:		size of the array
 */
void rand_arr_gen(
	int arr[]	/* out */,
	int n		/* in  */
	) {
		
	// Initialize random number generator
	srand(time(NULL));

	int i;
	for (i = 0; i < n; i++) {
		arr[i] = (rand() % 101) + 1; 
	}
}

/*-------------------------------------------------------------------
 * Function:   print_arr
 * Purpose:    Print the contents of an array to stdout.	(Auxiliary function)
 * In args:    arr:    the array to be printed
 *             n:      the number of elements in the array
 */
void print_arr(
	int arr[]	/* in  */, 
	int n		/* in  */) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

/*-------------------------------------------------------------------
 * Function:   quicksort
 * Purpose:    Sort the array	(Conquer task)
 * In args:    arr:		the array to be sorted
 *             first:	
 *             last:		
 */
void quicksort(
	int arr[], 
	int first, 
	int last) {
		int partition_index;
		if (first < last) {
			partition_index = partition(arr, first, last);
			#	pragma omp task default(none) firstprivate(arr, first, partition_index)
			{
				quicksort(arr, first, partition_index - 1);
			}
			#	pragma omp task default(none) firstprivate(arr, partition_index, last)
			{
				quicksort(arr, partition_index + 1, last);
			}
		}
		else {
			elapsed = omp_get_wtime() - start; // finished sorting the subarray ---> should contain to the latest process work time
		}
}

/*-------------------------------------------------------------------
 * Function:   partition
 * Purpose:    Partition the array into two subarrays/subproblems	(Divide task)
 * In args:    arr:		the array to be sorted
 *             first:	index to the first element in the partition
 *             last:	index to the last element in the partition
 */
int partition (
	int arr[], 
	int first, 
	int last) {
		int pivot = arr[last]; // last element is the pivot
		int store_index = first - 1; 
		for (int i = first; i < last; i++) {
			if (arr[i] <= pivot) {
				store_index += 1;
				swap(&arr[store_index], &arr[i]);
			}
		}
		swap(&arr[store_index + 1], &arr[last]);
		return store_index + 1;
}

/*-------------------------------------------------------------------
 * Function:   swap
 * Purpose:    Swaps two elements in an array	(Auxiliary function)
 * In args:    i:		The pointer of an element in the array
 *             j:		The pointer of another element in the array
 */
void swap (
	int* i		/* in  */,
	int* j		/* in  */) {
		int temp = *i;
		*i = *j;
		*j = temp;
}

/*-------------------------------------------------------------------
 * Function:   verify
 * Purpose:    Verifies that an array is sorted in ascending order	(Auxiliary function)
 * In args:    arr:		The array to be verified
 *             n:		The number of elements in that array
 */
int verify (
	int arr[], 
	int n) {
		for (int i = 0; i < n - 1; i++) {
			if (arr[i] > arr[i + 1]) {
				return 0;
			}
		}
		return 1;
}
