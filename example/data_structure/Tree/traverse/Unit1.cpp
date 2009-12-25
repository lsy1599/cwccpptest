/*---------------------------------------------------------------------------
  �\��G�G���𨫳X(���ǡB��ǡB�e��)-���j�� & �j�骩

  �]�p�̡GChui-Wen Chiu(Arick), sisimi@pchome.com.tw

  �����ɮסG�L

  �������ҡG
    1. Windows 2000 Professional
    2. Borland C++ Builder 5.0

  �ѦҸ�ơG
    1. Ellis Horowitz, Sartaj Sahni, Susan Anderson Freed, Ĭ����Ķ
       �u��Ƶ��c-�ϥ�C�y���v�A�Q�^�q���ϮѸ�ƪѥ��������q
       �A2001/4�AISBN:957-22-1713-5

  ��s��x�G
   2002/12/16  �{���إ�
-----------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#include <stdio.h>
#include <conio.h>
#include <alloc.h>
#include <stdlib.h>
#pragma hdrstop
#define MAX 100
//---------------------------------------------------------------------------
// �𪬸`�I���c
struct nodetype {
    int info;                /* info(p)   -> p->info   */
    struct nodetype *left;   /* left(p)   -> p->left   */
    struct nodetype *right;  /* right(p)  -> p->right  */
};
typedef struct nodetype *NODEPTR;
// ���|���c
#define STACKSIZE 100
 struct stack {
	int	top;	/* top of stack */
	NODEPTR	items[STACKSIZE];
};
struct stack	s;
int findpos;
NODEPTR findok[MAX];
#pragma argsused
/*---------------------------------------------------------------------------
�\��G�[�J�w�j�M���}�C��
��J�GNODEPTR ptr   ���[�J���`�I
---------------------------------------------------------------------------*/
void addFind(NODEPTR ptr){
  findok[++findpos]=ptr;
}
/*---------------------------------------------------------------------------
�\��G�P�_Node�O�_�w�Q�j�M
��J�GNODEPTR ptr   ���b�q�`�I
�^�ǡGbool          �O�_�j�M�L
---------------------------------------------------------------------------*/
bool isFind(NODEPTR ptr){
  if (findpos==-1)
    return false;

  for(int i=0;i<=findpos;i++){
    if (findok[i]==ptr)
      return true;
  }
  return false;
}
// ==========================================================================
//                             ���|���c�B��
/*---------------------------------------------------------------------------
�\��G���|��l��
��J�Gstack *ps   ����l�Ƥ����|����
---------------------------------------------------------------------------*/
void stack_init(stack *ps)
{
   ps->top = -1;	/* (*ps).top = -1; */

   return;
}
/*---------------------------------------------------------------------------
�\��G�P�_���|�O�_����
��J�Gstack *ps   ���P�_�����|����
---------------------------------------------------------------------------*/
bool empty(stack	*ps)
{
   if (ps->top == -1)  /* if ((*ps).top == -1) */
      return(true);
   else
      return(false);
}
/*---------------------------------------------------------------------------
�\��G�q���|���X�����çR��
��J�Gstack *ps   ���ϥΤ����|����
---------------------------------------------------------------------------*/
NODEPTR pop(stack	*ps)
{
   /* step 1: �P�_�O�_���Ű��| */
   if (empty(ps))
   {
//      printf("Stack underflow\n");
      return NULL;
   }
   /* step 2: �Ǧ^���|���ݪ��Ȩíק� top */
   return(ps->items[ps->top --]);
}
/*---------------------------------------------------------------------------
�\��G�N�������J���|
��J�Gstack   *ps   ���ϥΤ����|����
      NODEPTR ptr   �����J���|���`�I
---------------------------------------------------------------------------*/
void push(stack	*ps, NODEPTR	x)
{
   /* step 1: �P�_���|�O�_�w�� */
   if (ps->top == STACKSIZE - 1)
   {
      printf("Stack overflow\n");
      return;
   }
   /* step 2: �ק� top�A�ñN x �s�J*/
   ps->items[++ ps->top] = x;
   return;
}
/*---------------------------------------------------------------------------
�\��G���o���|���ݤ���
��J�Gstack *ps   ���ϥΤ����|����
---------------------------------------------------------------------------*/
NODEPTR stacktop(stack	*ps)
{
   /* step 1: �P�_�O�_���Ű��| */
   if (empty(ps))
   {
//      printf("Stack underflow\n");
      return NULL;
   }
   /* step 2: �Ǧ^���|���ݪ��� */
   return(ps->items[ps->top]);
}
// ==========================================================================
//                             �𪬵��c�B��
/*---------------------------------------------------------------------------
�\��G���o�@�Ӱt�m�O���骺�`�I

---------------------------------------------------------------------------*/
NODEPTR getnode(){
   NODEPTR p;
   p = (NODEPTR) malloc(sizeof(struct nodetype));
   return(p);
}
/*---------------------------------------------------------------------------
�\��G����@�Ӹ`�I

---------------------------------------------------------------------------*/
void freenode(NODEPTR p)
{
    free(p);
}
/*---------------------------------------------------------------------------
�\��G�إ߾�

---------------------------------------------------------------------------*/
NODEPTR maketree(char x)
{
    NODEPTR p;

    p = getnode();
    p->info = x;
    p->left = NULL;
    p->right = NULL;
    return(p);
}
/*---------------------------------------------------------------------------
�\��G�]�w���l��

---------------------------------------------------------------------------*/
void setleft(NODEPTR p,char x)
{
  if (p == NULL)
     printf("void insertion\n");
  else if (p->left != NULL)
     printf("invalid insertion\n");
  else
     p->left = maketree(x);
}
/*---------------------------------------------------------------------------
�\��G�]�w�k�l��

---------------------------------------------------------------------------*/
void setright(NODEPTR p, char x)
{
    if (p == NULL)
        printf("void insertion\n");
    else if (p->right != NULL)
        printf("invalid insertion\n");
    else
        p->right = maketree(x);
}
/*---------------------------------------------------------------------------
�\��G��Ǩ��X���j��

---------------------------------------------------------------------------*/
void postorder(NODEPTR ptr){
  if(ptr){
    postorder(ptr->left);
    postorder(ptr->right);
    printf("%3d",ptr->info);
  }
}
/*---------------------------------------------------------------------------
�\��G�e�Ǩ��X���j��

---------------------------------------------------------------------------*/
void preorder(NODEPTR ptr){
  if(ptr){
    printf("%3d",ptr->info);
    preorder(ptr->left);
    preorder(ptr->right);
  }
}
/*---------------------------------------------------------------------------
�\��G���Ǩ��X���j��

---------------------------------------------------------------------------*/
void inorder(NODEPTR ptr){
  if(ptr){
    inorder(ptr->left);
    printf("%3d",ptr->info);
    inorder(ptr->right);
  }
}
/*---------------------------------------------------------------------------
�\��G��Ǩ��X�j�骩

---------------------------------------------------------------------------*/
void postorder_loop(NODEPTR ptr){
  NODEPTR rp;

  for(;;){
    for(;ptr;ptr=ptr->left){
      push(&s,ptr);
    }//end for

    ptr=pop(&s);
    if (!ptr){
      return;
    }//end if

    for(;;){
      for(;;){
        rp=ptr->right;
        if (isFind(rp))
        {
          printf("%3d",ptr->info);
          addFind(ptr);
          ptr=pop(&s);
          if (!ptr){
            return;
          }//end if
        }else{
          break;
        }//end if
      }//end for

      if(rp==NULL){
        printf("%3d",ptr->info);
        addFind(ptr);
        ptr=pop(&s);
        if (!ptr){
          return;
        }//end if
      }else{
        push(&s,ptr);
        ptr=rp;
        break;
      }//end if
    }//end for
  }//end for
}
/*---------------------------------------------------------------------------
�\��G�e�Ǩ��X�j�骩

---------------------------------------------------------------------------*/
void preorder_loop(NODEPTR ptr){
  for(;;){

    for(;ptr;ptr=ptr->left){
      printf("%3d",ptr->info);
      push(&s,ptr);
    }//end for

    ptr=pop(&s);
    if (!ptr){
      break;
    }//end if

    ptr=ptr->right;
  }//end for
}
/*---------------------------------------------------------------------------
�\��G���Ǩ��X�j�骩

---------------------------------------------------------------------------*/
void inorder_loop(NODEPTR ptr){
  for(;;){
    for(;ptr;ptr=ptr->left){
      push(&s,ptr);
    }//end for

    ptr=pop(&s);
    if (!ptr){
      break;
    }//end if

    printf("%3d",ptr->info);
    ptr=ptr->right;
  }//end for
}
/*---------------------------------------------------------------------------
�\��G�{���i�J�I

---------------------------------------------------------------------------*/
int main(int argc, char* argv[])
{
  stack_init(&s);

  NODEPTR ptree;
  // example 0:��@�`�I
  ptree = maketree(0);

  randomize();
  int n=rand()%10;
  switch(n){
    case 1:
      // example 1:�����@�`�I
      setleft(ptree,1);
      break;
    case 2:
      // example 2:�k���@�`�I
      setright(ptree,1);
      break;
    case 3:
      // example 3:���k�U�@�Ӥl�`�I
      setleft(ptree,1);
      setright(ptree,2);
      break;
    case 4:
      // example 4:
      setleft(ptree,1);
      setright(ptree,2);
      setleft(ptree->left,3);
      break;
    case 5:
      // example 5:
      setleft(ptree,1);
      setright(ptree,2);
      setright(ptree->left,3);
      break;
    case 6:
      // example 6:
      setleft(ptree,1);
      setleft(ptree->left,2);
      setright(ptree->left,4);
      setleft(ptree->left->left,3);
      break;
    case 7:
      // example 7:
      setright(ptree,1);
      setright(ptree->right,2);
      break;
    case 8:
      // example 8:
      setleft(ptree,1);
      setleft(ptree->left,2);
      setright(ptree->left,3);
      setleft(ptree->left->left,4);
      setright(ptree->left->left,5);
      setright(ptree->left->left->right,7);
      setleft(ptree->left->left->right->right,8);
      setright(ptree->left->right,6);
      break;
    case 9:
      // example 9;
      setleft(ptree,1);
      setright(ptree,2);
      setleft(ptree->right,3);
      setleft(ptree->right->left,4);
      setright(ptree->right->left,5);
      setright(ptree->right->left->left,6);
      break;
    case 10:
      // example 10:
      setleft(ptree,1);
      setleft(ptree->left,2);
      setleft(ptree->left->left,4);
      setright(ptree->left->left,5);
      setright(ptree->left->left->left,8);

      setright(ptree->left,3);
      setleft(ptree->left->right,6);
      setright(ptree->left->right,7);
      setleft(ptree->left->right->right,9);
      setleft(ptree->left->right->right->left,10);
      setright(ptree->left->right->right->left,11);
      setright(ptree->left->right->right->left->right,12);
      break;
    default:
      break;
  }//end switch

/*
  // ���|����
  push(&s,ptree);
  ptree=pop(&s);

  printf("%d\n",ptree->info);
  printf("%d\n",ptree->left->info);
  printf("%d\n",ptree->right->info);
  printf("%d\n",ptree->left->left->info);
*/

  printf("\n=== Preorder ===\n");
  preorder(ptree);
  printf("\n");
  preorder_loop(ptree);

  printf("\n=== inorder ===\n");
  inorder(ptree);
  printf("\n");
  inorder_loop(ptree);

  printf("\n=== Postorder ===\n");
  postorder(ptree);
  printf("\n");
  findpos=-1;
  postorder_loop(ptree);

  printf("\npress any key ...");

  getch();
  return 0;
}
//---------------------------------------------------------------------------
