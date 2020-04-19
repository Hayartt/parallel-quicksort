/* File:     parallel_quicksort.c
 *
 * Purpose:  Demonstrate and evaluate parallel quicksort.
 *
 * Compile:  gcc -g -Wall -fopenmp -o parallel_quicksort parallel_quicksort.c
 * 	or:  clang -Xpreprocessor -fopenmp -I/usr/local/include -L/usr/local/lib -lomp  parallel_quicksort.c -o parallel_quicksort
 * Run:      Performance Evaluation:	./parallel_quicksort [initial array size] [initial thread count] 1
 * 	     Normal Execution:		./parallel_quicksort [n] [thread_count] 0
 *
 * Input:    Number of elements in the array. (n)
 *	     Number of processes. (thread_count)
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "parallel_quicksort_module.h"

void rand_arr_gen(int arr[], int n);
void rand_arr_gen_two(int arr1[], int arr2[], int n);
void print_arr(int arr[], int n);
int verify(int arr[], int n);
void Usage(char* prog_name);
void copy_arr(int src[], int dest[], int n);

double start, elapsed;

/*------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
	if (argc < 4) {
		Usage(argv[0]);
		return -2;
	}
	int* a;
	int* b;
	int n = strtol(argv[1], NULL, 10);
	int thread_count = strtol(argv[2], NULL, 10);
	int timed_opt = strtol(argv[3], NULL, 2);
	
	if (timed_opt) {			/*	timed execution	*/ 
		for (int j = n; j <= n * 16; j *= 2) { // array size loop

			a = (int*) (malloc(j * sizeof(int)));
			b = (int*) (malloc(j * sizeof(int)));
			rand_arr_gen_two(a, b, j); // generate random array for tests

			for (int i = thread_count; i <= thread_count * 32; i*=2) { // thread count loop
				if (j <= 100) {
					printf("Array before sorting: ");
					print_arr(b,j);
				}
				start = omp_get_wtime();
				parallel_quicksort(b, j, i);
				elapsed = omp_get_wtime() - start;
				if (j <= 100) {
					printf("Array after sorting: ");
					print_arr(b,j);
				}
				printf("np=%d\t|\tsz=%d:\t\t%f\tseconds\n", i,j, (elapsed));
				printf("\n");

				if (verify(b, j) == 0) {
					printf("failed\n");
				} // non-parallel validation for the result
				copy_arr(a,b,j); // rewrite b to be the same for all parallel tests (values of i)
			}
			printf("----------------------------------------------------------------\n");
			free(a);
			free(b);
		}
	} else {			/*	normal execution	*/ 
		a = (int*) (malloc(n * sizeof(int)));
		//for (int i = 0; i < 1000; i++) { 
			rand_arr_gen(a,n);
			if (n <= 100) {
				printf("Array before sorting: ");
				print_arr(a,n);
			}
			start = omp_get_wtime();
			parallel_quicksort(a, n, thread_count);
			elapsed = omp_get_wtime() - start;
			if (n <= 100) {
				printf("Array after sorting: ");
				print_arr(a,n);
			}
			printf("Finished in %f milliseconds\n", (elapsed * 1000));
			if (verify(a, n) == 0) {
				printf("failed\n");
			} // non-parallel validation for the result
		//}

		free(a);
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
	   prog_name
	   );
}  /* Usage */

/*-------------------------------------------------------------------
 * Function:   rand_arr_gen
 * Purpose:    Generates n random integer values in the range [1,n] to fill an array.	(Auxiliary function)
 * In args:    arr:	array
 *             n:	size of the array
 */
void rand_arr_gen(
	int arr[]	/* out */,
	int n		/* in  */
	) {
		
	// Initialize random number generator
	srand(time(NULL));

	int i;
	for (i = 0; i < n; i++) {
		arr[i] = (rand() % n) + 1; 
	}
}

/*-------------------------------------------------------------------
 * Function:   rand_arr_gen_two
 * Purpose:    Generates n random integer values in the range [1,n] to fill two arraies.	(Auxiliary function)
 * In args:    arr1:	array
 *	       arr1:	array
 *             n:	size of the array
 */
void rand_arr_gen_two(
	int arr1[]	/* out */,
	int arr2[]	/* out */,
	int n		/* in  */
	) {
		
	// Initialize random number generator
	srand(time(NULL));

	int i;
	for (i = 0; i < n; i++) {
		arr1[i] = (rand() % n) + 1; 
		arr2[i] = arr1[i];
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
 * Function:   verify
 * Purpose:    Verifies that an array is sorted in ascending order	(Auxiliary function)
 * In args:    arr:	The array to be verified
 *             n:	The number of elements in that array
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
