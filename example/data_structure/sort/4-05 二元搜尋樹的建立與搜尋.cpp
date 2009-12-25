 /******************************************************************/
 /******************* �{���W�� : 4-5.c *****************************/
 /******************* �G���j�M�𪺫إ߻P�j�M ***********************/

 #include <stdlib.h>
  struct tree                       /* �ŧi�𪬵��c */
 {
 int data;                          /* �G����`�I��� */
 struct tree *left;                 /* ���l�𪺫��� */
 struct tree *right;                /* �k�l�𪺫��� */
 };
 typedef struct tree node;          /* �w�q�G���𪺵��c�s���A */
 typedef node *bintree;             /* �ŧi�G����`�I���Ы��A */


 bintree create(int *data,int post) /* �إߤG���� */
 {
   bintree newnode;                 /* �s�`�I���� */
   if (data[post]== 0 || post >15)  /*�פ����*/
      return NULL;
   else
   {
     newnode= (bintree)malloc(sizeof(node)); /* �t�mmemory�Ŷ� */
     newnode->data = data[post];             /* �إ߸`�I���e */
     newnode->left = create(data,2*post);    /* �H���j�覡�إߥ��l�� */
     newnode->right = create(data,2*post+1); /* �H���j�覡�إߥk�l�� */
     return newnode;
   }
 }


 bintree find(bintree ptr, int value)  /* �G���𪺤G���j�M */
 {
   while (ptr != NULL)
   {
    if (ptr->data == value)            /* ���ҭn�䪺��� */
       return ptr;                     /* �Ǧ^�`�I���� */
    else
       if (ptr->data > value)          /* �Ydata > value */
	   ptr=ptr->left;              /* �j�M���l�� */
       else
	   ptr=ptr->right;            /* �j�M�k�l�� */
   }
   return NULL;                       /* �S�����ҭn����� */
 }


 bintree search(bintree ptr,int value) /* �G���𪺷j�M�l�� */
 {
   bintree pointer1,pointer2;
   if (ptr != NULL)                    /* �פ���� */
   {
     if (ptr->data == value)           /* ���ҭn�䪺��� */
	return ptr;                    /* �Ǧ^�`�I���� */
     else
     {
	pointer1 = search(ptr->left,value);  /* �H���j�覡�j�M���l�� */
	pointer2 = search(ptr->right,value); /* �H���j�覡�j�M�k�l�� */
	if (pointer1 != NULL)
	   return pointer1;                  /* �ҭn�䪺��Ʀb���l�� */
	else
	{
	   if (pointer2 != NULL)
	      return pointer2;                  /* �ҭn�䪺��Ʀb�k�l�� */
	   else
	      return NULL;                      /* �S����� */
	}
     }
   }
   else
     return NULL;                             /* �ҭn�䪺��ƬO���`�I */
 }


 void main()
 {
   bintree root=NULL;                         /* ��ګ��� */
   bintree ptr=NULL;
   int value;
   int data[16]={0,5,4,6,2,0,0,8,1,3,0,0,0,0,7,9};
   root = create(data,1);                     /* �إ߾𪬵��c */
   printf("�п�J��M�`�I���(1-9)==>");
   scanf("%d", &value);                       /* Ū���`�I��� */
   ptr = find(root,value);                    /* �G���j�M */
   if (ptr != NULL)
      printf("�G���j�M:�`�I��ƬO[%d]\n",ptr->data);
   else
      printf("�G���j�M:�`�I�S�����\n");
   ptr = search(root,value);                  /* �G����l�ܷj�M */
   if (ptr!=NULL)
      printf("�l�ܷj�M:�`�I��ƬO[%d]\n",ptr->data);
   else
      printf("�l�ܷj�M:�`�I�S�����\n");
 }

