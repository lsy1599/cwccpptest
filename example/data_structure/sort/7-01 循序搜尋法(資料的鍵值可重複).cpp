 /******************************************************************/
 /********************** �{���W�� : 7-1.c **************************/
 /**************** �{���\�� : �`�Ƿj�M�k(��ƪ���ȥi����)**********/
 /******************************************************************/


 # include <stdio.h>
 # define N 12
 # define TRUE 1

 int search(int key,int x[],int low,int high ,int index[]);

 main()                		          /* �D�{�� : �`�Ƿj�M�k */
 {
    static int data[N]= {25,117,5,9,11,68,278,53,135,222,371,24} ;
    int i,key,count,index[N] ;
    clrscr() ;
    while (TRUE)
    {
       printf("��}�C��Ʀp�U:\n") ;      /* �N��Ʀs�JData�}�C�� */
       for (i = 0; i < N ; i++)
       {
	 printf("data[%2d]=%3d  ",i,data[i]) ;
	 if ((i+1) % 4 == 0)
	    printf("\n") ;
       }
       printf("\n�п�J���j�M���(^Break : ����) : ") ; /* ��J���j�M����� */
       scanf("%d",&key) ;
       count=search(key,data,0,N-1,index) ;    /* �I�s�`�Ƿj�M��� */
       printf("===================================\n") ;
       if (count > 0)
	  for(i = 0 ; i < count ; i++)
	  printf("��� %3d ���F ! �O�b data[%d] ��m\n",key,index[i]) ;
       else
	  printf("��� %3d �䤣�� ! \n",key) ; /* �䤣��ҭn����� */
       printf("-----------------------------------\n");
       printf("�A�ո�!!!\n");
    }
 }


 int search(key,x,low,high,index)	       /* �i��`�Ƿj�M�ʧ@ */
 int key,x[],low,high;
 int index[] ;
 {
   int i,count ;
   count = -1 ;
   for (i = low ; i <= high ; i++)
   {	          		       /* �N��ȻP�}�C����Data�v�@��� */
     if (key == x[i])
	index[++count] =i ;
   }
   return(count+1) ;
 }

