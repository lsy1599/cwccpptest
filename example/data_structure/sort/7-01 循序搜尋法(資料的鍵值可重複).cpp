 /******************************************************************/
 /********************** 程式名稱 : 7-1.c **************************/
 /**************** 程式功能 : 循序搜尋法(資料的鍵值可重複)**********/
 /******************************************************************/


 # include <stdio.h>
 # define N 12
 # define TRUE 1

 int search(int key,int x[],int low,int high ,int index[]);

 main()                		          /* 主程式 : 循序搜尋法 */
 {
    static int data[N]= {25,117,5,9,11,68,278,53,135,222,371,24} ;
    int i,key,count,index[N] ;
    clrscr() ;
    while (TRUE)
    {
       printf("原陣列資料如下:\n") ;      /* 將資料存入Data陣列中 */
       for (i = 0; i < N ; i++)
       {
	 printf("data[%2d]=%3d  ",i,data[i]) ;
	 if ((i+1) % 4 == 0)
	    printf("\n") ;
       }
       printf("\n請輸入欲搜尋資料(^Break : 結束) : ") ; /* 輸入欲搜尋的資料 */
       scanf("%d",&key) ;
       count=search(key,data,0,N-1,index) ;    /* 呼叫循序搜尋函數 */
       printf("===================================\n") ;
       if (count > 0)
	  for(i = 0 ; i < count ; i++)
	  printf("資料 %3d 找到了 ! 是在 data[%d] 位置\n",key,index[i]) ;
       else
	  printf("資料 %3d 找不到 ! \n",key) ; /* 找不到所要的資料 */
       printf("-----------------------------------\n");
       printf("再試試!!!\n");
    }
 }


 int search(key,x,low,high,index)	       /* 進行循序搜尋動作 */
 int key,x[],low,high;
 int index[] ;
 {
   int i,count ;
   count = -1 ;
   for (i = low ; i <= high ; i++)
   {	          		       /* 將鍵值與陣列中的Data逐一比較 */
     if (key == x[i])
	index[++count] =i ;
   }
   return(count+1) ;
 }

