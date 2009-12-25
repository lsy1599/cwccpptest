 /********************************************************************/
 /*********************** 程式名稱 : 7-4.c ***************************/
 /*********************** 程式功能 : 插補搜尋法 **********************/
 /********************************************************************/

 # include <stdio.h>
 # define N 12
 # define TRUE 1

 int intp_search(int key,int x[],int low,int high,int index[]) ;

 main()
 {
    static int data[N] = {11,23,33,46,54,62,78,89,124,235,341,456} ;
    int i,key,count,index[N] ;
    clrscr();
    while (TRUE)
    {     			       /* 將原始資料列印出來 */
    for (i = 0; i< N ; i++)
    {
      printf("data[%2d]=%3d  ",i,data[i]) ;
      if ((i+1) %4 == 0)  printf("\n") ;
    }
    printf("\n請輸入搜尋資料(^Break : 結束) : "); /* 輸入欲搜尋的資料 */
    scanf("%d",&key) ;
    count=intp_search(key,data,0,N-1,index) ;     /* 呼叫插補搜尋函數 */
    printf("=====================================\n") ;
    if (count > 0)
       for(i =0 ; i< count ; i++)
       printf("資料 %3d 找到了 ! 是在data[%d] 位置\n",key,index[i]) ;
    else
       printf("資料 %3d 找不到 ! \n",key) ;
       printf("==================================\n") ;  /*找不到鍵值*/
       printf("再 試 試 !!! \n");
    }
 }


 int intp_search(key,x,low,high,index)       /* 進行插補搜尋的動作 */
 int key,x[],low,high,index[] ;
 {
    int i,mid,count;
    count = -1 ;
    mid= -100 ;
    while (low <= high)
    {
      mid=low + (key-x[low]) * (high-low) / (x[high]-x[low]);/* 設定及計算修正量 */
      if (key < x[mid])
      { 		        /* 當key<x[mid]，改變high指標到mid-1 位置 */
	if (high != mid -1)
	   high = mid-1;
	else  return(-1) ;
      }
      else if (key > x[mid])
      {
	if (low != mid +1)     /* 當key>x[mid]，改變low指標到mid+1的位置 */
	   low = mid +1 ;
	else  return(-1) ;
      }
      else
      {
	index[++count] = mid ;
	/* 當key=x[mid]，代表找到鍵值，並以index陣列指示鍵值的位置*/
	i = mid -1 ;
	while (key == x[i])
	     index[++count] = i -- ;
	i = mid + 1 ;
	while (key ==x[i])
	     index[++count] = i ++ ;
	return(count + 1) ;
      }
    }
    return(-1) ;
 }


