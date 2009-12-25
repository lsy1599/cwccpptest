 /*************************************************************/
 /******************** �{���W�� : 6-7.c ***********************/
 /********************** ��n�ƧǪk ***************************/
 /*************************************************************/

 # include <stdio.h>
 # define N 8
 # define TRUE 1

 int heap_sort(int x[],int low,int high) ;   /* �ܼƫŧi */
 void move_up(int y[],int n) ;
 void move_down(int y[],int n);
 void swap(int *x, int *y) ;

 main()
 {
    static int data[N] = {45,37,65,11,28,85,21,1} ; /* ��l�}�C��Ʀ�8�� */
    int i ;
    clrscr() ;
    printf("�}�C��m ") ;
    for (i = 0; i < N; i++)
       printf("[%2d]",i) ;
    printf("\n") ;
    printf("==============================================\n") ;
    printf("�Ƨǫe : ") ;     		     /* �C�L�X���Ƨǫe����� */
    for (i = 0; i< N; i++)
       printf(" %2d ",data[i]) ;
    printf("\n") ;
    heap_sort(data,0,N-1) ;                  /* �I�s��n�ƧǨ�� */
    printf("==============================================\n") ;
 }


 int heap_sort(x,low,high)      	    /* �i���n�Ƨǰʧ@ */
 int x[],low,high ;
 {
    int i,j,n,y[N+1],step ;
    step =0 ;			            /* �إߤ@�G���� */
    n = 0 ;				    /* �s����ƥ[�J�}�Cy���� */
    for (j = low ; j <= high ; j++)
    {
       y[++n] = x[j] ;
       move_up(y,n) ;                       /* �Hmove_up��ƽվ㦨��n�� */
    }
    for (i = high ; i >= low ; i--)
    {                                       /* �v�@��X��ڤ��Ȫ��짹���ƧǬ��� */
       x[i] = output(y,&n) ;
       printf("�B�J %d : ",++step) ;
       for (j = low ; j <= high ; j++)
	  printf(" %2d ",x[j]) ;	    /* �N�C�@�^�X�ƧǤ����G�C�L�X�� */
       printf("��X==>x[%d]=%d\n",i,x[i]) ;
    }

 }


 void move_up(int y[], int n)		    /* �N�G����վ㦨��n�� */
 {
    int x ;
    x = y[n] ;
    while (n / 2 > 0 && x > y[n/2])
    {
      y[n] = y[n/2] ;
      n /= 2 ;
    }
    y[n] = x ;
 }


 int output(int y[],int *n)
/* ��X��ڭȡA�A�N�̫�@�Ӹ�Ʋ����ڡA���۩I�smove_down���,�վ�G���𦨰�n�� */
 {
    int t ;
    t = y[1] ;
    swap(&y[1],&y[*n]) ;
    *n = *n - 1;
    move_down(y,*n) ;
    return(t) ;
 }


 void move_down(int y[],int n)              /* �ΥH�q��ڶ}�l�վ㦨��n�� */
 {
    int x,i,left ;
    x = y[1] ;
    i = 1 ;
    while ( i <= n / 2)
    {
      left = 2 * i ;
      if (left < n && y[left] < y[left + 1])  left ++ ;
      if (x < y[left])
      {
	y[i] = y[left] ;
	i = left ;
      }
      else break ;
    }
    y[i] = x ;
 }


 void swap(int *a, int *b)	            /* �i���ƥ洫 */
 {
    int temp ;
    temp = *a ;
    *a = *b ;
    *b = temp ;
 }
