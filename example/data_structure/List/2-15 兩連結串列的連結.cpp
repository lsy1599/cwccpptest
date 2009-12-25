 /**********************************************************/
 /*************** �{���W�� : 2-15.c ************************/
 /*************** ��s����C���s�� *************************/
 #include <stdlib.h>

 struct list                                /* ��C���c�ŧi */
 {
   int num;                                 /* �U�`�I�s�� */
   struct list *next;                       /* ���V�U�@�Ӹ`�I */
 };
 typedef struct list node;                  /* �w�q�s����C���A */
 typedef node *link;                        /* �w�q�s�����Ы��A */

 void print_list(link ptr)                  /* �s����C���C�L */
 {
    while (ptr != NULL)                     /* ���X��C���U�`�I */
    {
       printf("[%d]",ptr->num);             /* �C�L�`�I������� */
       ptr=ptr->next;                       /* ���V�U�@�`�I */
    }
    printf("\n");
 }

 link create_list(int *array,int len)       /* �إ߳s����C */
 {
      link head;                            /* �����C���}�Y */
      link ptr,ptr1;
      int i;
					    /* �إ߲Ĥ@�Ӹ`�I */
      head=(link) malloc(sizeof(node));     /* �t�mmemory�Ŷ� */
      if (!head)
	 return NULL;
      head->num = array[0];                  /* �]�w�`�I�����e */
      head->next = NULL;
      ptr=head;
      for(i=1;i<len;i++)                     /* �إߨ䥦�`�I */
      {
	ptr1=(link) malloc(sizeof(node));
	if (!ptr1)
	   return NULL;
	ptr1->num=array[i];                  /* �إ߸`�I���e */
	ptr1->next=NULL;
	ptr->next=ptr1;                      /* �s���U�@�Ӹ`�I */
	ptr=ptr->next;
      }
      return head;
 }

 link concate(link ptr1,link ptr2)         /* �s����C���s�� */
 {
     link ptr;
     ptr=ptr1;                             /* ���V�Ĥ@�Ӧ�C���}�l */
     while (ptr->next != NULL)             /* ��X�Ĥ@�Ӧ�C������*/
       ptr=ptr->next;                      /* ���V�U�@�`�I */
     ptr->next=ptr2;                       /* �s���ĤG�Ӧ�C */
     return ptr1;
 }

 void main()              /* �D�{��:�s���Ѩ�Ӱ}�C���e�ҫإߪ���C */
 {
    int list1[6]={1,2,3,4,5,6};            /* �}�C�@�����e */
    int list2[5]={7,8,9,10,11};            /* �}�C�G�����e */
    link ptr,ptr1,ptr2;
    ptr1=create_list(list1,6);             /* �إ߲Ĥ@�Ӧ�C */
    if (ptr1==NULL)
    {
       printf("�O����t�m����!\n");
       exit(1);
    }
    ptr2=create_list(list2,5);             /* �إ߲ĤG�Ӧ�C */
    if (ptr2==NULL)
    {
       printf("�O����t�m����!\n");
       exit(1);
    }
    ptr=concate(ptr1,ptr2);                /* �I�s�s�����C�Ƶ{�� */
    print_list(ptr);                       /* �L�X�s����C */
 }
