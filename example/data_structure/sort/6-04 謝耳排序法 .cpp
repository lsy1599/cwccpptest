/***************************************************************/
/******************* �{���W�� : 6-4.c **************************/
/******************** �¦ձƧǪk *******************************/
/***************************************************************/

 # include <stdio.h>
 # define N 6
 int shell_sort(int x[],int low,int high) ;

 main()
 {
   static int data[N] = {45,27,18,20,55,32,} ;/* ���ư}�C����������� */
   int i ;

   clrscr() ;
   printf("�}�C��m") ;
   for (i = 0 ; i < N ; i++)
      printf(" [%2d] ",i) ;
   printf("\n") ;
   printf("================================================\n") ;
   printf("�Ƨǫe : ") ;                 /* �L�X�Ƨǫe���}�C���e */
   for (i = 0 ; i < N ; i++)
      printf("  %2d  ",data[i]) ;
   printf("\n") ;
   shell_sort(data,0,5) ;                /* �I�s�¦ձƧ� */
   printf("================================================\n") ;
 }


 int shell_sort(x,low,high)              /* �i���¦ձƧǰʧ@ */
 int x[],low,high ;
 {
   int i,j,k,m,n,dist,temp,step ;

   step = 0 ;
   n = high - low + 1 ;
   dist=3 ;
   do {                                  /* �ھ�dist�ȱNx�}�C��ƥ[�H���� */
       for (m =0 ;m < dist ; m++)
       {
	for (i = m + low + dist;i <= (n-1)/dist*dist+m && i <= high ; i = i + dist)
	  {
	    temp = x[i] ;
	    for (j = i-dist ; j >= low ; j = j - dist)
	    {
	      if (x[j] > temp )          /* �i����ժ�����ʧ@ */
		   x[j+dist] = x[j] ;
		else
		   break ;
	     }
	     x[j+dist] = temp ;
	  }
	}
	printf("�B�J %d : ",++step) ;       /* �N�C���ƧǪ����G�C�L�X�� */
	for (k = low ; k <= high ; k++)
	    printf("  %2d  ",x[k]);
	printf("\n");
	dist = dist - 1 ;                         /* �i��U�@�^�X���ƧǤ��� */
       } while (dist >= 1) ;
 }