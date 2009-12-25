 /***************************************************************/
 /********************* 程式名稱 : 6-2.c ************************/
 /*********************** 插入排序法 ****************************/
 /***************************************************************/

 # include <stdio.h>
 # define N 6
 int insert_sort(int x[],int low,int high);

 main()
 {
   static int data[N]={28,15,7,68,19,24}; /* 設陣列中有6筆資料 */
   int i;

   clrscr();
   printf("陣列位置");                   /* 印出未排序前之資料 */
   for (i=0 ; i<N; i++)
   printf(" [%2d] ",i);
   printf("\n");
   printf("===========================================\n");
   printf("排序前 :");
   for (i=0; i<N ; i++)
   printf("  %2d  ",data[i]);
   printf("\n");
   insert_sort(data,0,5) ;              /* 呼叫插入排序函數 */
   printf("===========================================\n");
 }


 int insert_sort(x,low,high)            /* 進行插入排序動作 */
 int x[],low,high;
 {
   int i,j,temp,k,min,step;
   step=0;
   for (i=low+1; i <= high ;i++)
   {
     temp=x[i];
     for (j=i-1 ; j >= low ;j--)
     {
	if (x[j] > temp)                /* 比較x[i]與x[j]的大小 */
	   x[j+1]=x[j];
	else
	   break;
     }
     x[j+1]=temp ;
     printf("步驟 %d :", ++step);  /*列印出每次排序的結果*/
     for (k=low;k<=high; k++)
	printf("  %2d  ",x[k]);
     printf("\n");
   }
 }