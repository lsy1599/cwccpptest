 /***************************************************************/
 /********************* �{���W�� : 6-2.c ************************/
 /*********************** ���J�ƧǪk ****************************/
 /***************************************************************/

 # include <stdio.h>
 # define N 6
 int insert_sort(int x[],int low,int high);

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
   insert_sort(data,0,5) ;              /* �I�s���J�ƧǨ�� */
   printf("===========================================\n");
 }


 int insert_sort(x,low,high)            /* �i�洡�J�Ƨǰʧ@ */
 int x[],low,high;
 {
   int i,j,temp,k,min,step;
   step=0;
   for (i=low+1; i <= high ;i++)
   {
     temp=x[i];
     for (j=i-1 ; j >= low ;j--)
     {
	if (x[j] > temp)                /* ���x[i]�Px[j]���j�p */
	   x[j+1]=x[j];
	else
	   break;
     }
     x[j+1]=temp ;
     printf("�B�J %d :", ++step);  /*�C�L�X�C���ƧǪ����G*/
     for (k=low;k<=high; k++)
	printf("  %2d  ",x[k]);
     printf("\n");
   }
 }