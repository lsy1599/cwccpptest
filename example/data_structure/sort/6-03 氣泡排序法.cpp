 /***************************************************************/
 /********************* �{���W�� : 6-3.c ************************/
 /*********************** ��w�ƧǪk ****************************/
 /***************************************************************/

 # include <stdio.h>
 # define N 6
 int bubble_sort(int x[],int low,int high);
 main()
 {
   static int data[N]={28,15,7,68,19,24}; /* �]�}�C����6����� */
   int i;

   clrscr();
   printf("�}�C��m");              /* �L�X���Ƨǫe����� */
   for (i=0 ; i<N; i++)
   printf(" [%2d] ",i);
   printf("\n");
   printf("===========================================\n");
   printf("�Ƨǫe :");
   for (i=0; i<N ; i++)
   printf("  %2d  ",data[i]);
   printf("\n");
   bubble_sort(data,0,5) ;          /* �I�s��w�ƧǨ�� */
   printf("===========================================\n");
 }

 int bubble_sort(x,low,high)        /* �i���w�Ƨǰʧ@ */
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
	 t=x[j] ;                   /* �Yx[j]>x[j+1],�h�i��洫�ʧ@ */
	 x[j]=x[j+1];
	 x[j+1]=t ;
	 change='y';
       }
     }
     printf("�B�J %d :", ++step);   /* �C�L�X�C���ƧǪ����G */
     for (k=low;k<=high; k++)
	printf("  %2d  ",x[k]);
     printf("\n");
   }
 }