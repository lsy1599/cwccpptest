 /*************************************************************/
 /******************** 程式名稱 : 6-7.c ***********************/
 /********************** 堆積排序法 ***************************/
 /*************************************************************/

 # include <stdio.h>
 # define N 8
 # define TRUE 1

 int heap_sort(int x[],int low,int high) ;   /* 變數宣告 */
 void move_up(int y[],int n) ;
 void move_down(int y[],int n);
 void swap(int *x, int *y) ;

 main()
 {
    static int data[N] = {45,37,65,11,28,85,21,1} ; /* 原始陣列資料有8筆 */
    int i ;
    clrscr() ;
    printf("陣列位置 ") ;
    for (i = 0; i < N; i++)
       printf("[%2d]",i) ;
    printf("\n") ;
    printf("==============================================\n") ;
    printf("排序前 : ") ;     		     /* 列印出未排序前的資料 */
    for (i = 0; i< N; i++)
       printf(" %2d ",data[i]) ;
    printf("\n") ;
    heap_sort(data,0,N-1) ;                  /* 呼叫堆積排序函數 */
    printf("==============================================\n") ;
 }


 int heap_sort(x,low,high)      	    /* 進行堆積排序動作 */
 int x[],low,high ;
 {
    int i,j,n,y[N+1],step ;
    step =0 ;			            /* 建立一二元樹 */
    n = 0 ;				    /* 新的資料加入陣列y之後 */
    for (j = low ; j <= high ; j++)
    {
       y[++n] = x[j] ;
       move_up(y,n) ;                       /* 以move_up函數調整成堆積樹 */
    }
    for (i = high ; i >= low ; i--)
    {                                       /* 逐一輸出樹根之值直到完成排序為止 */
       x[i] = output(y,&n) ;
       printf("步驟 %d : ",++step) ;
       for (j = low ; j <= high ; j++)
	  printf(" %2d ",x[j]) ;	    /* 將每一回合排序之結果列印出來 */
       printf("輸出==>x[%d]=%d\n",i,x[i]) ;
    }

 }


 void move_up(int y[], int n)		    /* 將二元樹調整成堆積樹 */
 {
    int x ;
    x = y[n] ;
    while (n / 2 > 0 && x > y[n/2])
    {
      y[n] = y[n/2] ;
      n /= 2 ;
    }
    y[n] = x ;
 }


 int output(int y[],int *n)
/* 輸出樹根值，再將最後一個資料移到樹根，接著呼叫move_down函數,調整二元樹成堆積樹 */
 {
    int t ;
    t = y[1] ;
    swap(&y[1],&y[*n]) ;
    *n = *n - 1;
    move_down(y,*n) ;
    return(t) ;
 }


 void move_down(int y[],int n)              /* 用以從樹根開始調整成堆積樹 */
 {
    int x,i,left ;
    x = y[1] ;
    i = 1 ;
    while ( i <= n / 2)
    {
      left = 2 * i ;
      if (left < n && y[left] < y[left + 1])  left ++ ;
      if (x < y[left])
      {
	y[i] = y[left] ;
	i = left ;
      }
      else break ;
    }
    y[i] = x ;
 }


 void swap(int *a, int *b)	            /* 進行資料交換 */
 {
    int temp ;
    temp = *a ;
    *a = *b ;
    *b = temp ;
 }
