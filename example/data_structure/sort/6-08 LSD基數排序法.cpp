 /*****************************************************************/
 /******************** �{���W�� : 6-8.c ***************************/
 /******************** �{���\�� : LSD��ƱƧǪk *******************/
 /*****************************************************************/


 # include <stdio.h>
 # define N 7
 # define TRUE 1
 # define BUCKET 16
 # define digit 4
 # define dist BUCKET/digit

 unsigned int mask = 0x000f ;			  /* �Ψ��^���C�@�զ줸 */
 int bucket_sort(int x[],int low,int high) ;

 main()						  /* �D�{�� */
 {
    static int data[N] ={123,827,66,485,216,87,158} ;  /* ��l�}�C��7����� */
    int i ;

    clrscr() ;
    printf("�}�C��m") ;
    for (i = 0 ; i < N ; i++)
       printf(" [%3d] ",i) ;
    printf("\n") ;
    printf("=========================================================\n") ;
    printf("�Ƨǫe :") ;
    for (i = 0 ; i < N ; i++)
       printf("  %3d  ",data[i]) ;		  /* �C�L�X�ӱƧǫe����� */
    printf("\n") ;
    radix_sort(data,0,N-1) ;                      /* �I�s��ƱƧǨ�� */
    printf("=========================================================\n") ;
 }


 int radix_sort(x,low,high)			  /* �i���ƱƧǰʧ@ */
 int x[],low,high ;        /* �N���x[low]��x[high]�H��Ȥ�������ǱƧ� */
 {
    int i,j,step ;

    step = 0 ;
    for(i = 1 ; i < dist ; i++)
    {
	 dist_and_join(x,low,high,i) ;		  /* ��4�����t�P�������ʧ@ */
      printf("�B�J%d  :",++step) ;
      for (j = low ; j <= high ; j++)		  /* �C�L�X�C�@���ƧǪ����G */
	 printf("  %3d  ",x[j]) ;
      printf("\n") ;
    }
 }


 int dist_and_join(x,low,high,i)     /* �w���i�զ줸�i����t�M�����ʧ@ */
 int x[],low,high,i;
 {
   unsigned int bucket[N][BUCKET];
   int count[BUCKET] ;
   int j,k,l,pos ;

   for(j = 0 ; j < BUCKET ; count[j++] = -1) ;
   for(j = low ;j <= high ; j++)
   {
     pos = (x[j] >> 4*(i - 1)) & mask ;		  /* �Q�Υk���B��MAND�B���^��x[j]����i�աA�H�i����t */
     count[pos] +=1 ;
     bucket[count[pos]][pos] =x[j] ;
   }
   l = low -1 ;
   for(j = 0 ; j < BUCKET ; j++)
   {
     if (count[j] >=0)
     {
	for(k = 0 ; k <= count[j] ; k++)
	     x[++l] = bucket[k][j] ;
     }
   }
 }
