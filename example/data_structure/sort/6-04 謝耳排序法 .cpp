/***************************************************************/
/******************* 程式名稱 : 6-4.c **************************/
/******************** 謝耳排序法 *******************************/
/***************************************************************/

 # include <stdio.h>
 # define N 6
 int shell_sort(int x[],int low,int high) ;

 main()
 {
   static int data[N] = {45,27,18,20,55,32,} ;/* 原資料陣列中有六筆資料 */
   int i ;

   clrscr() ;
   printf("陣列位置") ;
   for (i = 0 ; i < N ; i++)
      printf(" [%2d] ",i) ;
   printf("\n") ;
   printf("================================================\n") ;
   printf("排序前 : ") ;                 /* 印出排序前的陣列內容 */
   for (i = 0 ; i < N ; i++)
      printf("  %2d  ",data[i]) ;
   printf("\n") ;
   shell_sort(data,0,5) ;                /* 呼叫謝耳排序 */
   printf("================================================\n") ;
 }


 int shell_sort(x,low,high)              /* 進行謝耳排序動作 */
 int x[],low,high ;
 {
   int i,j,k,m,n,dist,temp,step ;

   step = 0 ;
   n = high - low + 1 ;
   dist=3 ;
   do {                                  /* 根據dist值將x陣列資料加以分組 */
       for (m =0 ;m < dist ; m++)
       {
	for (i = m + low + dist;i <= (n-1)/dist*dist+m && i <= high ; i = i + dist)
	  {
	    temp = x[i] ;
	    for (j = i-dist ; j >= low ; j = j - dist)
	    {
	      if (x[j] > temp )          /* 進行分組的比較動作 */
		   x[j+dist] = x[j] ;
		else
		   break ;
	     }
	     x[j+dist] = temp ;
	  }
	}
	printf("步驟 %d : ",++step) ;       /* 將每次排序的結果列印出來 */
	for (k = low ; k <= high ; k++)
	    printf("  %2d  ",x[k]);
	printf("\n");
	dist = dist - 1 ;                         /* 進行下一回合的排序分組 */
       } while (dist >= 1) ;
 }