 /**********************************************************/
 /**************** �{���W�� : 2-17.c ***********************/
 /**************** ���V�쵲��C�����I���J ******************/

 #include<stdlib.h>
 struct double_list                  /* ���V��C���c�ŧi */
 {
  int data;                          /* ��C�`�I��� */
  struct double_list *front;         /* ���V�U�@�`�I���e���� */
  struct double_list *back;          /* ���V�e�@�`�I������� */
 };
 typedef struct double_list dnode;   /* ���V��C�s�`�I���A */
 typedef dnode *dlink;               /* ���V��C�s���Ы��A */

 void print_double_list(dlink head)  /* �C�L���V�쵲��C */
 {
   while (head !=NULL)               /* ���X��C�`�I�j�� */
   {
    printf("[%d]",head->data);       /* �C�L�`�I��� */
    head=head->front;                /* ���V�U�@�`�I */
   }
   printf("\n");
 }

 /* ���V�쵲��C���`�I�t�J */
 dlink insert_node(dlink head,dlink ptr,int value)
 {
  dlink new_node;                        /* �s�`�I������ */
  new_node=(dlink)malloc(sizeof(dnode)); /* �إ߷s�`�I */
  if (!new_node)
     return NULL;
  new_node->data=value;                  /* �إ߸`�I���e */
  new_node->front=NULL;                  /* �]�w�e���Ъ�� */
  new_node->back=NULL;                   /* �]�w����Ъ�� */

  if (head==NULL)                        /* �p�G��C�O�Ū� */
     return new_node;                    /* �Ǧ^�s�`�I���� */
  if (ptr==NULL)
  {
  /***  �N�`�I���b�Ĥ@�Ӹ`�I���e,������C�}�l ***/
    new_node->front=head;                /* �s�`�I���e���Ы��V��C�}�l */
    head->back=new_node;                 /* ��`�I������Ы��V�s�`�I */
    head=new_node;                       /* �s�`�I������C�}�l */
  }
  else
  {
   if (ptr->front==NULL)                 /* �U�@�Ӹ`�I�O�_��NULL */
   {
     /*** �N�`�I���b��C�̫� ***/
     ptr->front=new_node;                /* �̫�`�I�e���Ы��V�s�`�I */
     new_node->back=ptr;                 /* �s�`�I����Ы��V�U�@�`�I */
   }
   else
   {
     /*** �N�`�I���J�쵲��C�����`�I ***/
     ptr->front->back=new_node;          /* �U�@�`�I���V�s�`�I */
     new_node->front=ptr->front;         /* �s�`�I���V�U�@�`�I */
     new_node->back=ptr;                 /* �s�`�I���V���J�`�I */
     ptr->front=new_node;                /* ���J�`�I���V�s�`�I */
   }
  }
  return head;                           /* �Ǧ^��C�_�l���� */
 }

 void main()                             /* �D�{�� */
 {
  dlink head=NULL;                       /* ���V�쵲��C���� */
  dlink tail=NULL;                       /* ��C�̫᪺���� */
  int list[6]={1,2,3,4,5,6};             /* �}�C���e */
  int i;
  head=insert_node(head,head,list[0]);   /* �إ߲Ĥ@�Ӹ`�I */
  print_double_list(head);               /* �L�X�쵲��C�����e */
  tail=head;                             /* �O�d��C�̫���� */

  head=insert_node(head,NULL,list[1]);   /* �N�`�I���b�Ĥ@�Ӹ`�I���e */
  print_double_list(head);               /* �L�X���J�᪺��C */

  head=insert_node(head,tail,list[2]);   /* �N�`�I���J��C�̫� */
  print_double_list(head);               /* �L�X���J�᪺��C */

  for(i=3;i<6;i++)                       /* �إߦ�C�`�I */
  {
    head=insert_node(head,head,list[i]); /* �N�`�I���J�`�I�P��C���� */
    print_double_list(head);             /* �L�X���J�᪺��C */
  }
 }
