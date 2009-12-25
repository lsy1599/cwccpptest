 /*****************************************************************/
 /******************** 程式名稱 : 6-8.c ***************************/
 /******************** 程式功能 : LSD基數排序法 *******************/
 /*****************************************************************/


 # include <stdio.h>
 # define N 7
 # define TRUE 1
 # define BUCKET 16
 # define digit 4
 # define dist BUCKET/digit

 unsigned int mask = 0x000f ;			  /* 用來擷取每一組位元 */
 int bucket_sort(int x[],int low,int high) ;

 main()						  /* 主程式 */
 {
    static int data[N] ={123,827,66,485,216,87,158} ;  /* 原始陣列有7筆資料 */
    int i ;

    clrscr() ;
    printf("陣列位置") ;
    for (i = 0 ; i < N ; i++)
       printf(" [%3d] ",i) ;
    printf("\n") ;
    printf("=========================================================\n") ;
    printf("排序前 :") ;
    for (i = 0 ; i < N ; i++)
       printf("  %3d  ",data[i]) ;		  /* 列印出來排序前之資料 */
    printf("\n") ;
    radix_sort(data,0,N-1) ;                      /* 呼叫基數排序函數 */
    printf("=========================================================\n") ;
 }


 int radix_sort(x,low,high)			  /* 進行基數排序動作 */
 int x[],low,high ;        /* 將資料x[low]～x[high]以鍵值不遞減之順序排序 */
 {
    int i,j,step ;

    step = 0 ;
    for(i = 1 ; i < dist ; i++)
    {
	 dist_and_join(x,low,high,i) ;		  /* 做4次分配與收集的動作 */
      printf("步驟%d  :",++step) ;
      for (j = low ; j <= high ; j++)		  /* 列印出每一次排序的結果 */
	 printf("  %3d  ",x[j]) ;
      printf("\n") ;
    }
 }


 int dist_and_join(x,low,high,i)     /* 針對第i組位元進行分配和收集動作 */
 int x[],low,high,i;
 {
   unsigned int bucket[N][BUCKET];
   int count[BUCKET] ;
   int j,k,l,pos ;

   for(j = 0 ; j < BUCKET ; count[j++] = -1) ;
   for(j = low ;j <= high ; j++)
   {
     pos = (x[j] >> 4*(i - 1)) & mask ;		  /* 利用右移運算和AND運算擷取x[j]的第i組，以進行分配 */
     count[pos] +=1 ;
     bucket[count[pos]][pos] =x[j] ;
   }
   l = low -1 ;
   for(j = 0 ; j < BUCKET ; j++)
   {
     if (count[j] >=0)
     {
	for(k = 0 ; k <= count[j] ; k++)
	     x[++l] = bucket[k][j] ;
     }
   }
 }
