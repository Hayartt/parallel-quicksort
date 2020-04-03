
package Quicksort;

import java.util.Random;
import java.util.Scanner;

public class QuickSort {

/*-------------------------------------------------------------------
 * Function:  partition
 * Purpose:   Splits an array and swaps based on the pivot 	
 * In args:   arr:  The array to be sorted
              low:  First index in the array
              high: Last index in the array
 *           
 */	
private int partition(int arr[], int low, int high) 
	{ 
		int pivot = arr[high]; 
		int i = (low-1); // index of smaller element 
		for (int j=low; j<high; j++) 
		{ 
			// If current element is smaller than the pivot 
			if (arr[j] < pivot) 
			{ 
				i++; 

				// swap arr[i] and arr[j] 
				int temp = arr[i]; 
				arr[i] = arr[j]; 
				arr[j] = temp; 
			} 
		} 

		// swap arr[i+1] and arr[high] (or pivot) 
		int temp = arr[i+1]; 
		arr[i+1] = arr[high]; 
		arr[high] = temp; 

		return i+1; 
	} 

/*-------------------------------------------------------------------
 * Function:  Sort
 * Purpose:   The function that implements QuickSort()	
 * In args:    arr:    The array to be sorted
               low:    First index in the array
               high:   Last index in the array
 */	
	private void sort(int arr[], int low, int high) 
	{ 
		if (low < high) 
		{ 
			/* pi is partitioning index, arr[pi] is 
			now at right place */
			int pi = partition(arr, low, high); 

			// Recursively sort elements before partition and after partition 
			sort(arr, low, pi-1); 
			sort(arr, pi+1, high); 
		} 
	} 

/*-------------------------------------------------------------------
 * Function:   printArray
 * Purpose:    A utility function to print array of size n	
 * In args:    arr: The array to be printed            
 */ 
	private static void printArray(int arr[]) 
	{ 
		int n = arr.length; 
		for (int i=0; i<n; ++i) 
			System.out.print(arr[i]+" "); 
		System.out.println(); 
	} 
/*-------------------------------------------------------------------
 * Function:   randomList
 * Purpose:    Generates n random integer values to fill an array.	
 * In args:    n:	The size of an array
 * 	       k:	The range of random numbers    
 */
    private static int[] randomList(int n,int k) {
            Random random=new Random();
            int[] RandomArray=new int[n];
            for(int i=0;i<RandomArray.length;i++)
                RandomArray[i]=random.nextInt(k);
            return RandomArray;
        }
/*-------------------------------------------------------------------
 * Function:   isSorted
 * Purpose:   Verifies that an array is sorted in ascending order	
 * In args:    n:	The array to be verified
 *           
 */
   private static boolean isSorted(int[] a) {
		for (int i = 0; i < a.length - 1; i++) {
			if (a[i] > a[i + 1]) {
				return false;
			}
		}

		return true;
	}

    public static void main(String[] args) {
	 System.out.println("Enter the size of an array: "); 
	  Scanner in = new Scanner(System.in);
	  int n = in.nextInt();
          int arr[];
           arr=randomList(n,1000000);	
         long startTime = System.currentTimeMillis();
         
		QuickSort ob = new QuickSort(); 
		ob.sort(arr, 0, n-1); 
                
         long endTime = System.currentTimeMillis();
         
         System.out.println("----------------------------------"); 
         System.out.println("Time with " + (endTime - startTime) + " milliseconds");
         
	 boolean check = isSorted(arr);
           if (check == false){
                System.out.println("Failed");}
           
        // to print the array run the following
	//	printArray(arr); 
    }
    
}
