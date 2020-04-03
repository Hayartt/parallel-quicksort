
package quiksortthreads;
import java.util.Random;

public class QuikSortThreads implements Runnable{
    
        int[] array;
        int My_start,My_end;
        
     QuikSortThreads(int[] data,int start,int end) {
            this.array=data;
            this.My_start=start;
            this.My_end=end;
        }
     
        @Override
        public void run(){
            quickSort(this.array, this.My_start, this.My_end);
                
           /* To get the current thread id run the following */
           /*  long ThreadID= Thread.currentThread().getId()%2 +1;
             System.out.println("Thread " + ThreadID+ " of "+ 2 );*/
                
        }
/*-------------------------------------------------------------------
 * Function:  swap
 * Purpose:   swaps between two indices in an array	
 * In args:    arr:	The array to get swapped
               i:	First index
               j:	Second index
 *           
 */ 
       private static void swap(int[] arr, int i, int j){
            int tmp=arr[i];
            arr[i]=arr[j];
            arr[j]=tmp;
        }
/*-------------------------------------------------------------------
 * Function:  partition
 * Purpose:   Splits an array and swaps based on the pivot 	
 * In args:    arr: The array to be sorted
               start: First index in the array
               end:   Last index in the array
 *           
 */       
       private static int partition(int[] arr, int start, int end) {
            if(start==end)
                return start;
            int pivot = arr[end];
            int s = start-1;
            for(int i=start;i<end;i++)
                if(arr[i]<=pivot)
                    swap(arr,++s,i);
            swap(arr,++s,end);
            return s;
        }
/*-------------------------------------------------------------------
 * Function:  quickSort
 * Purpose:   Splits an array and call quickSort method for the two parts	
 * In args:    arr: The array to be sorted
               start: First index in the array
               end:   Last index in the array
 *           
 */
       private static void quickSort(int[] arr, int start, int end) {
            if (end <= start)
                return;
            int s = partition (arr,start,end);
            quickSort(arr,start,s-1);
            quickSort(arr,s+1,end);
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
   private   static boolean isSorted(int[] a) {
		for (int i = 0; i < a.length - 1; i++) {
			if (a[i] > a[i + 1]) {
				return false;
			}
		}

		return true;
	}

/*------------------------------------------------------------------*/
      
     public static void main(String[] args) {
             
            int[] Array;
            int n=10000000;
            Array=randomList(n,1000000);
            
            int s = partition(Array,0,n-1);
            
            long startTime = System.currentTimeMillis();

            Thread t1=new Thread(new QuikSortThreads(Array,0,s-1));
            Thread t2=new Thread(new QuikSortThreads(Array,s+1,Array.length-1));
            t1.start();
            t2.start();
            
            try {
                t1.join();
                t2.join();
            }catch(InterruptedException e){
                System.out.println(e);
            }
            
            long endTime = System.currentTimeMillis();
            
           boolean check = isSorted(Array);
           if (check == false){
                System.out.println("Failed");}

          System.out.println("----------------------------------"); 
          System.out.println("Number of threads is " + 2); 
          System.out.println("Time with " + (endTime - startTime) + " milliseconds");
        }
    }
