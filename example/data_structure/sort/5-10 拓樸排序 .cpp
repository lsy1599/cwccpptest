 /******************************************************************/
 /******************* 程式名稱 : 5-10.c ****************************/
 /******************* 拓樸排序 *************************************/
 /******************************************************************/

 # include <stdio.h>
 # define n 50
 # define TRUE 1
 # define selected 1
 # define unselected 0
 int vertices,adj_matrix[n][n],mark[n];   /* 宣告變數 */
 void in_edge(void);
 void print_matrix(void);
 void topology_sort(void);

 main()                            /* 主程式:拓樸排序 */
 {
   int i,j;
   clrscr();
   printf("請輸入頂點總數:");      /* 輸入有向圖形的總節點數 */
   scanf("%d",&vertices);
   in_edge();
   print_matrix();
   printf("\n\n拓樸排序為 :");
   topology_sort();
 }


 void in_edge(void)         /* 用來輸入有向圖形,並儲存至相鄰陣列 */
 {
   int i,j;
   for(i=0;i < vertices;i++)
      for (j=0;j<vertices;j++)
	 adj_matrix[i][j]=0;
   printf("請輸入有向圖的邊.....\n");
   while (TRUE)
   {
      printf("邊是連接頂點(-1:結束):");
      scanf("%d",&i);
      if (i ==-1) break;
      printf("               到頂點:");
      scanf("%d",&j);
      adj_matrix[i][j]=1; /* 若有向圖形中,任何兩點有邊相鄰,則adj_Matrix[i][j]=1 */
   }
 }


 void print_matrix(void)    /* 列印出相鄰陣列的內容 */
 {
   int i,j;
   printf("\n有向圖鄰接矩陣為 :\n");
   for (i=0 ;i<vertices;i++)
      printf("  v%d",i);
   printf("\n");
   for (i=0;i<vertices;i++)
   {
      printf("v%d    ",i);
      for (j=0;j<vertices;j++)
	 printf("%d",adj_matrix[i][j]);
      printf("\n");
   }
 }


 void topology_sort(void)          /* 用以輸出拓樸排序 */
 {
   int i,j,k,m;
   for(i=0;i < vertices;i++)
      mark[i]=unselected;   /* Mark陣列用來儲存沒有先行者的頂點
   k=0;                       並在上面做記錄 */
   label:
   while (k < vertices)
   {
     for (i=0 ;i < vertices; i++)
     {
       m=0;
       if (mark[i] == unselected)
       {
	 for (j=0; j < vertices ; j++)
	 {
	     if (mark[i]==unselected && mark[j]==unselected)
	       if (adj_matrix[j][i]==1)
		  m +=1;
	 }
	 if (m == 0)
	 {
	   mark[i]=selected;
	   k +=1;
	   printf("==>v%d ",i);
	   goto label;
	 }
       }
     }
   }
 }

