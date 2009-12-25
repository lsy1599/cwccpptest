 /************************************************************/
 /***************** �{���W�� : 2-18.c ************************/
 /***************** ���V�쵲��C���`�I�R�� *******************/

 #include<stdlib.h>
 struct double_list                    /* ���V�쵲��C���c�ŧi */
 {
 int data;                             /* ��C�`�I��� */
 struct double_list *front;            /* ���V�U�@�`�I���e���� */
 struct double_list *back;             /* ���V�e�@�`�I������� */
 };
 typedef struct double_list dnode;     /* ���V�쵲��C�s�`�I���A */
 typedef dnode *dlink;                 /* ���V�쵲��C�s���Ы��A */

 dlink create_double_list(int *array,int len) /* �إ����V�쵲��C */
 {
   dlink head;                         /* ���V��C���� */
   dlink before;                       /* �e�@�`�I������ */
   dlink new_node;                     /* �s�`�I������ */
   int i;
   head=(dlink)malloc(sizeof(dnode));  /* �إ߲Ĥ@�Ӹ`�I�ðt�mmemory�Ŷ� */
   if(!head)
     return NULL;
   head->data=array[0];                /* �]�w�`�I���e */
   head->front=NULL;                   /* �]�w�e���Ъ�� */
   head->back=NULL;                    /* �]�w����Ъ�� */
   before=head;                        /* ���V�쵲��C�Ĥ@�`�I */
   for(i=1;i<len;i++)                  /* �إߨ䥦�`�I���j�� */
   {
     new_node=(dlink)malloc(sizeof(dnode));
     if(!new_node)
       return NULL;
     new_node->data=array[i];          /* �]�w�`�I���e */
     new_node->front=NULL;             /* �]�w�e���Ъ�� */
     new_node->back=before;            /* �N�s�`�I���V�e�@�`�I */
     before->front=new_node;           /* �N�e���Ы��V�s�`�I */
     before=new_node;                  /* �s�`�I�����e�`�I */
   }
   return head;                        /* �Ǧ^��C�_�l���� */
 }

 void free_double_list(dlink head)     /* �������V�쵲��C��memory�Ŷ� */
 {
   dlink ptr;                          /* �x�s�ثe�`�I���� */
   while(head !=NULL)                  /* ���X��C�䥦�`�I�j�� */
   {
     ptr=head;                         /* �O�d�ثe�`�I���� */
     head=head->front;                 /* ���V�U�@�`�I */
     free(ptr);                        /* ����ثe�`�I��memory�Ŷ� */
   }
 }

 void print_double_list(dlink head,dlink now) /* ���V�쵲��C���C�L */
 {
   while (head != NULL)
   {
     if (head==now)
	printf("#%d#",head->data);            /* �C�L�ثe�`�I��� */
     else
	printf("[%d]",head->data);            /* �C�L�`�I��� */
     head=head->front;                        /* ���V�U�@�`�I */
   }
   printf("\n");
 }

 dlink delete_node(dlink head,dlink ptr) /* ���V�쵲��C���`�I�R�� */
 {
   if (ptr->back==NULL)                  /* �Y�e�`�I��NULL */
   {
     head=head->front;           /* �R���Ĥ@�Ӹ`�I�ñN���Ы���U�@�`�I */
     head->back=NULL;            /* �]�w���V�e�`�I������ */
   }
   else
   {
     if(ptr->front==NULL)        /* �Y�U�@�`�I��NULL */
     {
      ptr->back->front=NULL;     /* �R���̫�`�I�ñN�e�`�I���Ы��VNULL */
     }
     else                        /* �R����C�������`�I */
     {
      ptr->back->front=ptr->front;   /* �N�e�`�I���Ы���U�@�`�I */
      ptr->front->back=ptr->back;    /* �N�U�`�I���Ы��V�e�`�I */
     }
   }
   free(ptr);                    /* ����R���`�I��memory�Ŷ� */
   return head;                  /* �Ǧ^��C�_�l���� */
 }

 void main()                     /* �D�{�� */
 {
   dlink head;                   /* ���V�쵲��C���� */
   dlink now=NULL;               /* �ثe�`�I���� */
   int list[6]={4,5,6,7,8,9};    /* �]�w�}�C���e */
   int choice;
   head=create_double_list(list,6); /* �I�s�إ����V�쵲��C�Ƶ{�� */
   if (head==NULL)
   {
      printf ("�O����t�m����! \n");
      exit(1);
   }
   while(1)                       /* �D�j�� */
   {
    if (now==NULL)
       now=head;                  /* �Nnow���V�Ĥ@�`�I */
    printf("��C���e�O: ");
    print_double_list(head,now);  /* �C�L�쵲��C���e */
    printf("[1]���U���� [2]���^���� [3]�R���`�I [4]���}==>");
    scanf("%d",&choice);
    switch(choice)
    {
     case 1: if (now->front !=NULL)
	       now=now->front;      /* ���V�U�@�`�I */
	     else
	       printf("�R����C�������`�I\n");
	     break;
     case 2: if (now->back !=NULL)
	       now=now->back;       /* ���V�e�@�`�I */
	     else
	       printf("�R����C�}�l���`�I\n");
	     break;
     case 3: if (head !=NULL)       /* �R���ثe�`�I */
	     {
	      head=delete_node(head,now);
	      now=head;             /* �Nnow���V�Ĥ@�Ӹ`�I */
	     }
	     else
	      printf("��C�O�Ū�\n");
	     break;
     case 4: exit(1);               /* �����{�� */
    }
  }
  free_double_list(head);
 }


