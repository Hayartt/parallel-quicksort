/* File:     quicksort.c
 *
 * Purpose:  Implement serial quicksort.
 *
 * Compile:  gcc -g -Wall -o quicksort quicksort.c
 * Run:      ./quicksort
 *
 * Input:    Number of elements in the array
 * Output:   A random array before and after applying the serial quicksort algorithm
 *
 * Errors:   																		????
 * Note:     																		????
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

/*------------------------------------------------------------------*/

int main() {
	int n;
	printf("Enter n: ");
	scanf("%d", &n);
	int a[n];
	rand_arr_gen(a, n);
	printf("Array before sorting:\n");
	print_arr(a, n);
	quicksort(a, 0, (n - 1));
	printf("Array after sorting:\n");
	print_arr(a, n);
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
			quicksort(arr, first, partition_index - 1);
			quicksort(arr, partition_index + 1, last);
		}
}

/*-------------------------------------------------------------------
 * Function:   partition
 * Purpose:    Partition the array into two subarrays/subproblems	(Divide task)
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

/*----------------------------------------------------------:---------
 * Function:   swap
 * Purpose:    Swaps two elements in an array											(Auxiliary function)
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
