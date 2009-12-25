/****************************************************************/
/****************** �{���W�� : 2-19.c ***************************/
/****************** �����쵲��C���`�I���J�P�R�� ****************/

 #include<stdlib.h>
 struct cycle_list                 /* ������`��C���c�ŧi */
 {
  int data;                        /* �`�I��� */
  struct cycle_list *link;         /* �`�I��C���� */
 };
 typedef struct cycle_list node;   /* �����쵲��C�s���A */
 typedef node *clink;              /* ��C���зs���A */

 void print_cycle_list(clink head) /* �C�L�����쵲��C�����e */
 {
  clink ptr;
  head=head->link;                 /* ��C���Ы���Ĥ@�`�I */
  ptr=head;                        /* ptr�����C�}�l */
  do                               /* ���X��C�`�I�j�� */
  {
    printf("[%d]",ptr->data);      /* �C�L�`�I��� */
    ptr=ptr->link;                 /* ptr����U�@�Ӹ`�I */
  }while (head !=ptr && head != head->link);
  printf("\n");
 }

 clink insert_node(clink head,clink ptr,int value)
 {                                 /* �����쵲��C���`�I���J */
   clink new_node;                 /* �s�`�I���� */
   new_node=(clink)malloc(sizeof(node)); /* �إ߷s���`�I�ðt�mmemory�Ŷ� */
   if (!new_node)                  /* �ˬd�O���� */
      return NULL;
   new_node->data=value;           /* �]�w�`�I�����e */
   new_node->link=NULL;            /* �]�w���Ъ���� */
   if (head==NULL)                 /* �Y��C�O�Ū� */
   {
     new_node->link=new_node;      /* link���Ы��쥻���`�I */
     return new_node;              /* �Ǧ^�s�`�I���� */
   }
   if (ptr==NULL)
   {                               /* �N�s���`�I���b�Ĥ@�Ӹ`�I���e */
     new_node->link=head->link;    /* �s�`�I���V�U�@�`�I */
     head->link->link=new_node;    /* �e�@�`�I���V�s���`�I */
   }
   else
   {                               /* �N�s���`�I���b�Y�`�I���� */
     new_node->link=ptr->link;     /* �s�`�I���V�U�@�`�I */
     ptr->link=new_node;           /* �e�@�`�I���V�s���`�I */
   }
   if (ptr==head)                   /* �N�s���`�I���J�̫�@�`�I */
      head=new_node;                /* ����head���Цܦ�C�}�l */
   return head;
 }

 clink delete_node(clink head,clink ptr)
 {                                  /* �����쵲��C���`�I�R�� */
  clink front;                      /* �e�@�`�I���� */
  if (head==NULL)                   /* �Y��C�O�Ū� */
     return NULL;
  if (ptr==head->link)
  {                                 /* �R���Ĥ@�Ӹ`�I */
    head->link=ptr->link;           /* �Nlink���Ы��V�U�@�`�I */
  }
  else
  {
   front=head;
   if(head != head->link)           /* �Y��C�h��@�Ӹ`�I */
   while (front->link != ptr)       /* ��prt�`�I���e�@�`�I */
       front=front->link;           /* ����U�@�Ӹ`�I */
   front->link = ptr->link;         /* �e�`�I���V�U�@�`�I */
  }
  if (ptr==head)                    /* �R���̫�`�I */
    head=front;
  free(ptr);                        /* ���^memory�Ŷ� */
  return head;                      /* �Ǧ^��C�_�l���� */
 }

 void main()                        /* �D�{�� */
 {
  clink head=NULL;                  /* �����쵲��C���� */
  int list[6]={3,4,5,6,7,8};        /* �}�C���e */
  int i;
   head=insert_node(head,head,list[0]);  /* �إ߲Ĥ@�Ӹ`�I */
   printf(" �إ߲Ĥ@�`�I:");
   print_cycle_list(head);          /* �L�X�쵲��C */
   for (i=2;i<6;i++)                /* �H�j��إߦ�C�`�I */
   {
    head=insert_node(head,head->link,list[i]); /* �N�s�`�I���b�Ĥ@�Ӹ`�I�e */
    printf("���J�Ĥ@�Ӹ`�I���e:");
    print_cycle_list(head);         /* �L�X��C */
   }
   for (i=2;i<6;i++)
   {                                /* �N�s�`�I���b�Y�`�I���� */
    head=insert_node(head,head->link,list[i]);
    printf("���J�s�`�I���� : ");
    print_cycle_list(head);         /* �L�X��C */
   }

   head=delete_node(head,head->link); /* �R���Ĥ@�Ӹ`�I */
   printf("�R���Ĥ@�Ӹ`�I:");
   print_cycle_list(head);          /* �L�X��C */
   printf("�R���̫�@�Ӹ`�I:");
   head=delete_node(head,head);
   print_cycle_list(head);
 }
