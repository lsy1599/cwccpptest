 /*****************************************************************/
 /******************* �{���W�� : 3-7.c ****************************/
 /******************* ��J������V��C **************************/

 #define MAXQ 10                  /* �w�q��C���̤j�e�q */
 int queue[MAXQ];                 /* �ŧi��C���}�C */
 int front = -1;                  /* ��C���e�ݫ��� */
 int rear = -1;                   /* ��C����ݫ��� */


 int queue_push(int value)        /* ��C��ƪ��s�J */
 {
   if ( rear + 1 == front || (rear == (MAXQ-1) && front <=0)
				  /* �ˬd��C�O�_���� */
      return -1;                  /* �Y�O�h�L�k�s�J */
   rear++;                        /* ��ݫ��Щ��e�� */
   if ( rear == MAXQ )            /* �O�_�W�L��C�j�p */
      rear = 0;                   /* �Y�O�h�q�Y�}�l */
   queue[rear] = value;           /* �_�h�N��Ʀs�J��C */
 }


 int queue_pop_rear()             /* �q��C����ݨ��X��� */
 {
   int temp;
   if ( front == rear )           /* �ˬd��C�O�_�O�� */
      return -1;                  /* �Y�O,�L�k���X */
   temp = queue[rear];            /* �_�h,�N��ƨ��X,��ݫ��Щ��e�� */
   rear--;
   if ( rear < 0 && front != -1)  /* �O�_�W�X��C�j�p */
      rear = MAXQ =1;             /* �Y�O,�q�Y�}�l */
   return temp;                   /* �_�h,�Ǧ^temp */
 }


 int queue__pop_front()           /* �q��C�e�ݨ��X��� */
 {
   if ( front == rear )           /* �ˬd��C�O�_�O�Ū� */
      return -1;                  /* �Y�O,�L�k���X */
   front++;                       /* �_�h,�e�ݫ��Щ��e�� */
   if ( front == MAXQ )           /* �O�_�W�L��C�j�p */
      front = 0;                  /* �Y�O,�q�Y�}�l */
   return queue[front];           /* �_�h,��C���X */
 }


 void main()                      /* �D�{�� : ���V��C���ާ@ */
 {
   int input_list[6] = {4,5,6,7,8,9};  /* ��J���}�C��� */
   int output_list[6];                 /* �x�s���X����� */
   int choice;
   int i,temp,sp = 0;

   for ( i = 0; i < 6; i++ )           /* �N�}�C�s�b��C */
      queue_push(input_list[i]);
   while ( front != rear )             /* �D�j�� */
   {
     printf("[1]�q��ݨ��X [2]�q�e�ݨ��X==>");
     scanf("%d",&choice);
     switch ( select )
     {
       case 1 : temp = queue_pop_rear();
		output_list[sp++] = temp;
		break;

       case 2 : temp = queue_pop_front();
		output_list[sp++] = temp;
		break;
     }
   }
   printf("��Ӱ}�C�����e:");
   for (i=0; i < 6; i++)
       printf([%]",input_list[i]);
   printf("\n��C���X������:");
   for (i=0 ;i<6;i++)
       printf("[%d]",output_list[i]);
   printf("\n");
 }
