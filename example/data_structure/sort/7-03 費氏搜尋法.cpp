 /*******************************************************************/
 /******************* 程式名稱 : 7-3.c ******************************/
 /******************* 程式功能 : 費氏搜尋法 *************************/
 /*******************************************************************/

 # include <stdio.h>
 # define N 12
 # define TRUE 1

 int fib_search(int key,int x[],int low,int high,int index[]) ;
 int fibonacci(int k) ;

 main()				       /* 主程式 : 費氏搜尋法 */
 {
   static int data[N] = {25,13,625,131,65,33,27,87,71,22,138,241} ;
   int i,key,count,index[N] ;
   clrscr() ;		               /* 將原始陣列內容列印出來 */
   while (TRUE)
   {
     for (i = 0 ; i < N ; i++)
     {
       printf("data[%2d]=%3d  ",i,data[i]) ;
       if ((i+1) % 4 == 0)
	  printf("\n");
     }
     printf("\n請輸入搜尋資料(^Break : 結束) : ") ;
     scanf("%d",&key) ;
     count=fib_search(key,data,0,N-1,index) ;    /* 呼叫費氏搜尋函數 */
     printf("===================================\n") ;
     if (count > 0)
	for(i = 0 ;i < count ; i++)
	printf("資料%3d 找到了 ! 是在data[%d] 位置\n",key,index[i]) ;
     else
	printf("資料%3d 找不到!\n",key) ;
	printf("===================================\n");    /*找不到鍵值*/
     printf("再 試 試 !!!\n");
    }
 }


 int fib_search(key,x,low,high,index)	     /* 執行費氏搜尋動作 */
 int key,x[],low,high,index[] ;
 {
    int i,j,n1,n2,n3,m,n,mid,count;
    count = -1 ;
    n = high-low+1;
    for (i = 0; fibonacci(i) < n +1 ; i++) ; /* 以費氏級數來當做迴圈執行的判斷條件 */
    i -- ;;
    m = n + 1 - fibonacci(i) ;
    n1 = fibonacci(i-1);
    n2 = fibonacci(i-2);
    n3 = fibonacci(i-3);
    if (key > x[n1])
       n1 =n1 + m ;
    while (n1 >= low)
    {
      if (key < x[n1])
      {			       /* 若key < x[n1]，則鍵值在左半段 */
	if (n3 == 0)
	   n1 = 0 ;
	else
	{
	  n1 = n1 - n3 ;
	  j =n2 ;
	  n2 = n3 ;
	  n3 = j- n3 ;
	}
      }
      else if (key > x[n1])
      { 		       /* 若key>x[n1]，則鍵值在右半段 */
	if (n2 == 1)
	   n1 = 0 ;
	else
	{
	  n1 = n1 + n3 ;
	  n2 = n2 - n3 ;
	  n3 = n3 - n2 ;
	}
      }
      else
      {	     /* 若以key=x[n1],代表找到鍵值,並以index 陣列來儲存此鍵值的位置 */
	index[++count] = n1  ;
	mid = n1 ;
	n1 = mid - 1 ;
	while (key == x[n1])
	     index[++count] = n1 -- ;
	n1 = mid + 1 ;
	while (key == x[n1])
	     index[++count] = n1 ++ ;
	return(count + 1) ;
      }
    }
    return(-1) ;
 }


 int fibonacci(k)	       /* 建立費氏級數 */
 int k ;
 {
    if (k == 0)  return(0) ;
    else if (k == 1) return(1) ;
    else return(fibonacci (k-1) + fibonacci (k-2)) ;
 }
