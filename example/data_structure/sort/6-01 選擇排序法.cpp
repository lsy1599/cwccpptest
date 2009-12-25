 /***************************************************************/
 /********************* 程式名稱 : 6-1.c ************************/
 /*********************** 選擇排序法 ****************************/
 /***************************************************************/

 # include <stdio.h>
 # define N 6
 int select_sort(int x[],int low,int high);

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
   select_sort(data,0,5) ;              /* 呼叫選擇排序函數 */
   printf("===========================================\n");
 }


 int select_sort(x,low,high)        /*進行選擇排序法動作*/
 int x[],low,high;
 {
   int n,i,j,t,k,min,step;
   step=0;
   for (i=low; i < high ;i++)
   {
     min=i;
     for (j=i+1 ; j <= high ;j++)
	if (x[j] >x[min])  min=j;
     t=x[min] ;                       /* 將x[i]與x[min]內容交換 */
     x[min]=x[i];
     x[i]=t ;
     printf("步驟 %d :", ++step);  /*列印出每次排序的結果*/
     for (k=low;k<=high; k++)
	printf("  %2d  ",x[k]);
     printf("\n");
   }
 }