
package quiksortthreads;
import java.io.Console;
import java.util.Random;

public class QuikSortThreads implements Runnable{
        int[] array;
        int My_start,My_end;
     QuikSortThreads(int[] data,int start,int end) {
            this.array=data;
            this.My_start=start;
            this.My_end=end;
        }
        public void run(){
            quickSort(this.array, this.My_start, this.My_end);
        }
        static void swap(int[] arr, int i, int j){
            int tmp=arr[i];
            arr[i]=arr[j];
            arr[j]=tmp;
        }
        static int partition(int[] arr, int start, int end) {
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
        static void quickSort(int[] arr, int start, int end) {
            if (end <= start)
                return;
            int s = partition (arr,start,end);
            quickSort(arr,start,s-1);
            quickSort(arr,s+1,end);
        }
        static int[] randomList(int n,int k) {
            Random random=new Random();
            int[] RandomArray=new int[n];
            for(int i=0;i<RandomArray.length;i++)
                RandomArray[i]=random.nextInt(k);
            return RandomArray;
        }

     public static void main(String[] args) {
             
            int[] Array={10,1,25,2,20,6};
            quickSort(Array,0,Array.length-1);
                     
            for(int i:Array)
            System.out.println(i);

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
System.out.println("\n"); 
System.out.println("Number of threads is " + 2 ); 
System.out.println("Time with " + (endTime - startTime) + " milliseconds");
        }
    }