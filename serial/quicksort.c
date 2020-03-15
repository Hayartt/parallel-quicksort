/* File:     quicksort.c
 *
 * Purpose:  Implement serial quicksort.
 *
 * Compile:  gcc -g -Wall -o quicksort quicksort.c
 * Run:      ./quicksort
 *
 * Input:    Number of elements in the array
 *
 * Errors:   Invalid number of arguments. (Exit: -2)
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void rand_arr_gen(int arr[], int n);
void print_arr(int arr[], int n);
void quicksort(int arr[], int first, int last);
int partition(int arr[], int first, int last);
void swap(int* i, int* j);
int verify(int arr[], int n);

/*------------------------------------------------------------------*/

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Invalid number of arguments\n");
		return -2;
	}
	int n = strtol(argv[1], NULL, 10);
	int a[n];
	for (int i = 0; i < 1000; i++) {
		rand_arr_gen(a, n);
		quicksort(a, 0, (n - 1));
		if (verify(a, n) == 0) {
			printf("failed\n");
			return -1;
		}
	}
	return 0;
}

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
		arr[i] = (rand() % n) + 1; 
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
 * Purpose:    Sort the array	(Conquer)
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
			quicksort(arr, first, partition_index - 1);
			quicksort(arr, partition_index + 1, last);
		}
}

/*-------------------------------------------------------------------
 * Function:   partition
 * Purpose:    Partition the array into two subarrays/subproblems	(Divide)
 * In args:    arr:		the array to be sorted
 *             first:	
 *             last:	
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