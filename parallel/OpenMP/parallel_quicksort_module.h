/* 
 * File:     parallel_quicksort_module.h
 *
 * Purpose:  Implement parallel quicksort.
 *
 */

#include <omp.h>

void quicksort(int arr[], int first, int last);
void parallel_quicksort(int arr[], int n, int thread_count);
int partition(int arr[], int first, int last);
void swap(int* i, int* j);

/*-------------------------------------------------------------------
 * Function:   parallel_quicksort
 * Purpose:    initiate parallel sort on an array
 * In args:    arr:	the array to be sorted
 *               n:     the size of the array 
 *    thread_count:	number of threads
 */
void parallel_quicksort(
	int arr[], 
	int n,
    int thread_count) {
		#	pragma omp parallel num_threads(thread_count) \
				default(none) shared(arr, n)
				{ // start parallel block
					#	pragma omp single nowait
					{
						quicksort(arr, 0, n - 1);
					}
				} // end of parallel block
}


/*-------------------------------------------------------------------
 * Function:   quicksort
 * Purpose:    Sort the array in parallel
 * In args:    arr:	the array to be sorted
 *             first:	index of the first element
 *             last:	index of the last element
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
			//#	pragma omp taskwait
		}
}

/*-------------------------------------------------------------------
 * Function:   partition
 * Purpose:    Partition the array/subarray into two subarrays/subproblems
 * In args:    arr:	the array to be sorted
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
 * In args:    i:	The pointer of an element in the array
 *             j:	The pointer of another element in the array
 */
void swap (
	int* i	/* in  */,
	int* j	/* in  */) {
		int temp = *i;
		*i = *j;
		*j = temp;
}
