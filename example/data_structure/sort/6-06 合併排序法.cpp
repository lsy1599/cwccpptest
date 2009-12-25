 /*************************************************************/
 /********************* �{���W�� : 6-6.c **********************/
 /**********************�X�ֱƧǪk ****************************/
 /*************************************************************/

 # include <stdio.h>
 # define N 7
 # define TRUE 1

 int exp(int i,int j) ;                /* �ܼƫŧi���� */
 void merge_sort(int x[],int low,int high) ;
 void merge(int y[],int high,int n,int *j) ;


 main()
 {
   static int data[N] = {12,64,28,32,9,57,89} ; /* ��l�}�C��Ʀ@�C�� */
   int i ;
   clrscr() ;
   printf("�}�C��m ") ;
   for (i = 0 ; i < N ; i++)
       printf(" [%2d] ",i) ;
   printf("\n") ;
   printf("===================================================\n") ;
					  /* �C�L�X���ƧǤ��e����� */
   printf("�Ƨǫe: ") ;
   for (i = 0 ; i < N ; i++)
       printf("  %2d  ",data[i]) ;
   printf("\n") ;
   merge_sort(data,0,N-1) ;               /* �I�s�X�ֱƧǨ�� */
   printf("===================================================\n") ;
 }


 void merge_sort(x,low,high)              /* �i��X�ֱƧǪ��ʧ@ */
 int x[],low,high ;
 {
   int c,i,j,k,n,step ;
   c = 0 ;
   step = 0 ;
   n = high - low +1 ;
   while ((k=exp(2,c)) < n)  c ++ ;  /* �ܼ�c�ΨӨM�w�X�ֱƧǦ@�ݦh�֦^ */
   for (i = 1 ; i <= c ; i++)        /* �ܼ�k�ΨӨM�C�@�^�X�ֻݦh�ָ�� */
   {
       j = low ;	             /* �HMerge��ư��X�֡A�C���X��k�Ӹ�� */
       while (j <= high)             /* �C�L�ƧǤ��᪺���G */
       {
	  merge(x,high,k=exp(2,i-1),&j) ;
       }
       printf("�B�J %d: ",++step) ;
       for (k = low ; k <= high ; k++)
	   printf("  %2d  ",x[k]);
       printf("\n") ;
   }
 }


 int exp(i,j)			       /* �ΨӲ���K���� */
 int i,j ;			       /* exp(i,j)��ƶǦ^i,j���� */
 {
   if (j == 0) return(1) ;
   while (j > 1)
   {
     i *= i ;
     j -- ;
   }
   return(i) ;
 }


 void merge(int x[],int high,int i,int *j)
 /* �qx[*j]�}�l�N��ƨCi�Ӥ@�ե[�H�X�֡A�öǦ^�U�@�ӫݦX�֤�x[*j]����m */
 {
    int y[N+1],z[N+1] ;
    int temp,m,b,c,d ;
    temp = *j ;
    m = 0 ;
    while (m <i && temp <=high)
    {
      y[++m] = x[temp++] ;
    }
    b = 0 ;
    while (b < i & temp <= high)
    {
       z[++b] = x[temp++] ;
    }
    temp = *j ;
    c = 1 ;
    d = 1 ;
    while (c <= m || d <= b)
    {
      if (c <= m && d <= b)
	 x[temp++] = (y[c] < z[d]) ? y[c++] : z[d++] ;
		/* ��y[c]<z[d]��,x[t++]=y[c++],�_�hy[t++]=z[d++] */
      if (c > m)
      {
	while (d <= b)
	     x[temp++] =z[d++] ;
	break ;
      }
      if (d > b)
      {
	while (c <= m)
	   x[temp++]=y[c++];
	break;
      }
    }
    *j = temp ;
 }

