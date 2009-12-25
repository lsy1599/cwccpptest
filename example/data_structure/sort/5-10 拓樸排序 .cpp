 /******************************************************************/
 /******************* �{���W�� : 5-10.c ****************************/
 /******************* �ݾ�Ƨ� *************************************/
 /******************************************************************/

 # include <stdio.h>
 # define n 50
 # define TRUE 1
 # define selected 1
 # define unselected 0
 int vertices,adj_matrix[n][n],mark[n];   /* �ŧi�ܼ� */
 void in_edge(void);
 void print_matrix(void);
 void topology_sort(void);

 main()                            /* �D�{��:�ݾ�Ƨ� */
 {
   int i,j;
   clrscr();
   printf("�п�J���I�`��:");      /* ��J���V�ϧΪ��`�`�I�� */
   scanf("%d",&vertices);
   in_edge();
   print_matrix();
   printf("\n\n�ݾ�ƧǬ� :");
   topology_sort();
 }


 void in_edge(void)         /* �Ψӿ�J���V�ϧ�,���x�s�ܬ۾F�}�C */
 {
   int i,j;
   for(i=0;i < vertices;i++)
      for (j=0;j<vertices;j++)
	 adj_matrix[i][j]=0;
   printf("�п�J���V�Ϫ���.....\n");
   while (TRUE)
   {
      printf("��O�s�����I(-1:����):");
      scanf("%d",&i);
      if (i ==-1) break;
      printf("               �쳻�I:");
      scanf("%d",&j);
      adj_matrix[i][j]=1; /* �Y���V�ϧΤ�,������I����۾F,�hadj_Matrix[i][j]=1 */
   }
 }


 void print_matrix(void)    /* �C�L�X�۾F�}�C�����e */
 {
   int i,j;
   printf("\n���V�ϾF���x�}�� :\n");
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


 void topology_sort(void)          /* �ΥH��X�ݾ�Ƨ� */
 {
   int i,j,k,m;
   for(i=0;i < vertices;i++)
      mark[i]=unselected;   /* Mark�}�C�Ψ��x�s�S������̪����I
   k=0;                       �æb�W�����O�� */
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

