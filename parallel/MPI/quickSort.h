#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
 #include <math.h> 
#include <time.h>

void rand_arr_gen(int arr[], int n);
void print_arr(int arr[], int n);
void quicksort(int arr[], int first, int last);
int parallelPartition(int arr[], int first, int last);
void swap(int* i, int* j);
int verify(int arr[], int n);


/*-------------------------------------------------------------------
 * Function:   partition
 * Purpose:    Partition the array into two subarrays/subproblems	(Divide)
 * In args:    arr:		The array to be sorted
 *             first:	The first index in the array/subarray
 *             last:	The last index in the array/subarray
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
 * Function:   rand_arr_gen
 * Purpose:    Generates n random integer values in the range [1,n] to fill an array.	(Auxiliary function)
 * In args:    arr:		Array
 *             n:		Size of the array
 */
void rand_arr_gen(
	int arr[],
	int n) {
		
	// Initialize random number generator
	//srand(time(NULL));

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
	int arr[], 
	int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

/*-------------------------------------------------------------------
 * Function:   quicksort
 * Purpose:    Sort the array	(Conquer)
 * In args:    arr:		The array to be sorted
 *             first:	The first index in the array/subarray
 *             last:	The last index in the array/subarray
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
 * Function:   swap
 * Purpose:    Swaps two elements in an array	(Auxiliary function)
 * In args:    i:		The pointer of an element in the array
 *             j:		The pointer of another element in the array
 */
void swap (
	int* i,
	int* j) {
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