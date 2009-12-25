 /**************************************************************/
 /*********************** 程式名稱 : 6-5.c *********************/
 /************************** 快速排序法 ************************/
 /**************************************************************/

 # include <stdio.h>
 # define N 10
 # define TRUE l

 int step = 0 ;                               /* 變數宣告部份 */
 int quick_sort(int x[],int low,int high) ;
 int div_and_con(int x[],int low,int high) ;
 void swap(int *x, int *y) ;

 main()
 {
   static int data[N] = {26,59,41,15,33,68,72,11,83,5};
					  /* 原始的陣列資料共十筆*/
   int i ;
   clrscr() ;
   printf("陣列位置 ") ;
   for (i = 0 ; i < N ; i++)
       printf("[%2d] ",i) ;
   printf("\n") ;
   printf("=========================================================\n");
					   /*列印未排列之前的陣列資料*/
   printf("排序前 : ") ;
   for (i = 0 ; i < N ; i++)
       printf(" %2d  ",data[i]) ;
   printf("\n") ;
   quick_sort(data,0,N-1) ;                /* 呼叫快速排序函數 */
   printf("=========================================================\n") ;
 }


 int quick_sort(x,low,high)                /* 進行快速排序動作 */
 int x[],low,high ;
 {
    int i,divide_point ;
    if (low < high) {          /* 當low < high時進行鍵值排序與分割的動作 */
       divide_point = div_and_con(x,low,high) ;
       printf("步驟 %d : ",++step) ;
       for (i = 0; i < N ; i++)
	  printf(" %2d  ",x[i]) ;
       printf("\n") ;
       quick_sort(x,low,divide_point-1) ;
       quick_sort(x,divide_point+1,high) ;
   }
 }


 int div_and_con(x,low,high)
	 /* 找出分割點，再以分割點將資料分成左右兩部份，分別進行快速排序 */
 int x[],low,high ;
 {
   int i,j,l,key;
   key = x[low];
   i = low ;
   j = high + 1 ;
   while (TRUE)
   {
     while(x[++i] < key) ;
     while(x[--j] > key) ;
     if (i < j)
       swap(&x[i],&x[j]) ;     /* i < j 時,做資料交換 */
     else
       break ;
   }
   swap(&x[low],&x[j]) ;
   return(j) ;
 }


 void swap(int *x, int *y)     /* 資料交換函數 */
 {
   int temp ;
   temp = *x ;
   *x = *y ;
   *y = temp ;
 }



