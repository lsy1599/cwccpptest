 /***************************************************************/
 /********************* 程式名稱 : 6-3.c ************************/
 /*********************** 氣泡排序法 ****************************/
 /***************************************************************/

 # include <stdio.h>
 # define N 6
 int bubble_sort(int x[],int low,int high);
 main()
 {
   static int data[N]={28,15,7,68,19,24}; /* 設陣列中有6筆資料 */
   int i;

   clrscr();
   printf("陣列位置");              /* 印出未排序前之資料 */
   for (i=0 ; i<N; i++)
   printf(" [%2d] ",i);
   printf("\n");
   printf("===========================================\n");
   printf("排序前 :");
   for (i=0; i<N ; i++)
   printf("  %2d  ",data[i]);
   printf("\n");
   bubble_sort(data,0,5) ;          /* 呼叫氣泡排序函數 */
   printf("===========================================\n");
 }

 int bubble_sort(x,low,high)        /* 進行氣泡排序動作 */
 int x[],low,high;
 {
   int n,i,j,t,k,step;
   char change ;
   step=0;
   change = 'y';
   n=high-low+1;
   for (i=low; i<n && change=='y' ;i++)
   {
     change='n' ;
     for (j=low ; j<n ;j++)
     {
       if (x[j] >x[j+1] )
       {
	 t=x[j] ;                   /* 若x[j]>x[j+1],則進行交換動作 */
	 x[j]=x[j+1];
	 x[j+1]=t ;
	 change='y';
       }
     }
     printf("步驟 %d :", ++step);   /* 列印出每次排序的結果 */
     for (k=low;k<=high; k++)
	printf("  %2d  ",x[k]);
     printf("\n");
   }
 }