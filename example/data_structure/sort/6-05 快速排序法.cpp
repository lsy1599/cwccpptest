 /**************************************************************/
 /*********************** �{���W�� : 6-5.c *********************/
 /************************** �ֳt�ƧǪk ************************/
 /**************************************************************/

 # include <stdio.h>
 # define N 10
 # define TRUE l

 int step = 0 ;                               /* �ܼƫŧi���� */
 int quick_sort(int x[],int low,int high) ;
 int div_and_con(int x[],int low,int high) ;
 void swap(int *x, int *y) ;

 main()
 {
   static int data[N] = {26,59,41,15,33,68,72,11,83,5};
					  /* ��l���}�C��Ʀ@�Q��*/
   int i ;
   clrscr() ;
   printf("�}�C��m ") ;
   for (i = 0 ; i < N ; i++)
       printf("[%2d] ",i) ;
   printf("\n") ;
   printf("=========================================================\n");
					   /*�C�L���ƦC���e���}�C���*/
   printf("�Ƨǫe : ") ;
   for (i = 0 ; i < N ; i++)
       printf(" %2d  ",data[i]) ;
   printf("\n") ;
   quick_sort(data,0,N-1) ;                /* �I�s�ֳt�ƧǨ�� */
   printf("=========================================================\n") ;
 }


 int quick_sort(x,low,high)                /* �i��ֳt�Ƨǰʧ@ */
 int x[],low,high ;
 {
    int i,divide_point ;
    if (low < high) {          /* ��low < high�ɶi����ȱƧǻP���Ϊ��ʧ@ */
       divide_point = div_and_con(x,low,high) ;
       printf("�B�J %d : ",++step) ;
       for (i = 0; i < N ; i++)
	  printf(" %2d  ",x[i]) ;
       printf("\n") ;
       quick_sort(x,low,divide_point-1) ;
       quick_sort(x,divide_point+1,high) ;
   }
 }


 int div_and_con(x,low,high)
	 /* ��X�����I�A�A�H�����I�N��Ƥ������k�ⳡ���A���O�i��ֳt�Ƨ� */
 int x[],low,high ;
 {
   int i,j,l,key;
   key = x[low];
   i = low ;
   j = high + 1 ;
   while (TRUE)
   {
     while(x[++i] < key) ;
     while(x[--j] > key) ;
     if (i < j)
       swap(&x[i],&x[j]) ;     /* i < j ��,����ƥ洫 */
     else
       break ;
   }
   swap(&x[low],&x[j]) ;
   return(j) ;
 }


 void swap(int *x, int *y)     /* ��ƥ洫��� */
 {
   int temp ;
   temp = *x ;
   *x = *y ;
   *y = temp ;
 }



