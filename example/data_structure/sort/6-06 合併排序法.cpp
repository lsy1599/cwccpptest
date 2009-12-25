 /*************************************************************/
 /********************* 程式名稱 : 6-6.c **********************/
 /**********************合併排序法 ****************************/
 /*************************************************************/

 # include <stdio.h>
 # define N 7
 # define TRUE 1

 int exp(int i,int j) ;                /* 變數宣告部份 */
 void merge_sort(int x[],int low,int high) ;
 void merge(int y[],int high,int n,int *j) ;


 main()
 {
   static int data[N] = {12,64,28,32,9,57,89} ; /* 原始陣列資料共七筆 */
   int i ;
   clrscr() ;
   printf("陣列位置 ") ;
   for (i = 0 ; i < N ; i++)
       printf(" [%2d] ",i) ;
   printf("\n") ;
   printf("===================================================\n") ;
					  /* 列印出未排序之前之資料 */
   printf("排序前: ") ;
   for (i = 0 ; i < N ; i++)
       printf("  %2d  ",data[i]) ;
   printf("\n") ;
   merge_sort(data,0,N-1) ;               /* 呼叫合併排序函數 */
   printf("===================================================\n") ;
 }


 void merge_sort(x,low,high)              /* 進行合併排序的動作 */
 int x[],low,high ;
 {
   int c,i,j,k,n,step ;
   c = 0 ;
   step = 0 ;
   n = high - low +1 ;
   while ((k=exp(2,c)) < n)  c ++ ;  /* 變數c用來決定合併排序共需多少回 */
   for (i = 1 ; i <= c ; i++)        /* 變數k用來決每一回合併需多少資料 */
   {
       j = low ;	             /* 以Merge函數做合併，每次合併k個資料 */
       while (j <= high)             /* 列印排序之後的結果 */
       {
	  merge(x,high,k=exp(2,i-1),&j) ;
       }
       printf("步驟 %d: ",++step) ;
       for (k = low ; k <= high ; k++)
	   printf("  %2d  ",x[k]);
       printf("\n") ;
   }
 }


 int exp(i,j)			       /* 用來產生K之值 */
 int i,j ;			       /* exp(i,j)函數傳回i,j之值 */
 {
   if (j == 0) return(1) ;
   while (j > 1)
   {
     i *= i ;
     j -- ;
   }
   return(i) ;
 }


 void merge(int x[],int high,int i,int *j)
 /* 從x[*j]開始將資料每i個一組加以合併，並傳回下一個待合併之x[*j]之位置 */
 {
    int y[N+1],z[N+1] ;
    int temp,m,b,c,d ;
    temp = *j ;
    m = 0 ;
    while (m <i && temp <=high)
    {
      y[++m] = x[temp++] ;
    }
    b = 0 ;
    while (b < i & temp <= high)
    {
       z[++b] = x[temp++] ;
    }
    temp = *j ;
    c = 1 ;
    d = 1 ;
    while (c <= m || d <= b)
    {
      if (c <= m && d <= b)
	 x[temp++] = (y[c] < z[d]) ? y[c++] : z[d++] ;
		/* 當y[c]<z[d]時,x[t++]=y[c++],否則y[t++]=z[d++] */
      if (c > m)
      {
	while (d <= b)
	     x[temp++] =z[d++] ;
	break ;
      }
      if (d > b)
      {
	while (c <= m)
	   x[temp++]=y[c++];
	break;
      }
    }
    *j = temp ;
 }

