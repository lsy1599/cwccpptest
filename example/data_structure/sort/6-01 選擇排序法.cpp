 /***************************************************************/
 /********************* �{���W�� : 6-1.c ************************/
 /*********************** ��ܱƧǪk ****************************/
 /***************************************************************/

 # include <stdio.h>
 # define N 6
 int select_sort(int x[],int low,int high);

 main()
 {
   static int data[N]={28,15,7,68,19,24}; /* �]�}�C����6����� */
   int i;

   clrscr();
   printf("�}�C��m");                   /* �L�X���Ƨǫe����� */
   for (i=0 ; i<N; i++)
   printf(" [%2d] ",i);
   printf("\n");
   printf("===========================================\n");
   printf("�Ƨǫe :");
   for (i=0; i<N ; i++)
   printf("  %2d  ",data[i]);
   printf("\n");
   select_sort(data,0,5) ;              /* �I�s��ܱƧǨ�� */
   printf("===========================================\n");
 }


 int select_sort(x,low,high)        /*�i���ܱƧǪk�ʧ@*/
 int x[],low,high;
 {
   int n,i,j,t,k,min,step;
   step=0;
   for (i=low; i < high ;i++)
   {
     min=i;
     for (j=i+1 ; j <= high ;j++)
	if (x[j] >x[min])  min=j;
     t=x[min] ;                       /* �Nx[i]�Px[min]���e�洫 */
     x[min]=x[i];
     x[i]=t ;
     printf("�B�J %d :", ++step);  /*�C�L�X�C���ƧǪ����G*/
     for (k=low;k<=high; k++)
	printf("  %2d  ",x[k]);
     printf("\n");
   }
 }