/*---------------------------------------------------------------------------
  功能：二元樹走訪(中序、後序、前序)-遞迴版 & 迴圈版

  設計者：Chui-Wen Chiu(Arick), sisimi@pchome.com.tw

  相關檔案：無

  測試環境：
    1. Windows 2000 Professional
    2. Borland C++ Builder 5.0

  參考資料：
    1. Ellis Horowitz, Sartaj Sahni, Susan Anderson Freed, 蘇維雅譯
       「資料結構-使用C語言」，松崗電腦圖書資料股份有限公司
       ，2001/4，ISBN:957-22-1713-5

  更新日誌：
   2002/12/16  程式建立
-----------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#include <stdio.h>
#include <conio.h>
#include <alloc.h>
#include <stdlib.h>
#pragma hdrstop
#define MAX 100
//---------------------------------------------------------------------------
// 樹狀節點結構
struct nodetype {
    int info;                /* info(p)   -> p->info   */
    struct nodetype *left;   /* left(p)   -> p->left   */
    struct nodetype *right;  /* right(p)  -> p->right  */
};
typedef struct nodetype *NODEPTR;
// 堆疊結構
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
功能：加入已搜尋的陣列中
輸入：NODEPTR ptr   欲加入之節點
---------------------------------------------------------------------------*/
void addFind(NODEPTR ptr){
  findok[++findpos]=ptr;
}
/*---------------------------------------------------------------------------
功能：判斷Node是否已被搜尋
輸入：NODEPTR ptr   欲半段節點
回傳：bool          是否搜尋過
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
//                             堆疊結構運算
/*---------------------------------------------------------------------------
功能：堆疊初始化
輸入：stack *ps   欲初始化之堆疊指標
---------------------------------------------------------------------------*/
void stack_init(stack *ps)
{
   ps->top = -1;	/* (*ps).top = -1; */

   return;
}
/*---------------------------------------------------------------------------
功能：判斷堆疊是否為空
輸入：stack *ps   欲判斷之堆疊指標
---------------------------------------------------------------------------*/
bool empty(stack	*ps)
{
   if (ps->top == -1)  /* if ((*ps).top == -1) */
      return(true);
   else
      return(false);
}
/*---------------------------------------------------------------------------
功能：從堆疊取出元素並刪除
輸入：stack *ps   欲使用之堆疊指標
---------------------------------------------------------------------------*/
NODEPTR pop(stack	*ps)
{
   /* step 1: 判斷是否為空堆疊 */
   if (empty(ps))
   {
//      printf("Stack underflow\n");
      return NULL;
   }
   /* step 2: 傳回堆疊頂端的值並修改 top */
   return(ps->items[ps->top --]);
}
/*---------------------------------------------------------------------------
功能：將元素推入堆疊
輸入：stack   *ps   欲使用之堆疊指標
      NODEPTR ptr   欲推入堆疊之節點
---------------------------------------------------------------------------*/
void push(stack	*ps, NODEPTR	x)
{
   /* step 1: 判斷堆疊是否已滿 */
   if (ps->top == STACKSIZE - 1)
   {
      printf("Stack overflow\n");
      return;
   }
   /* step 2: 修改 top，並將 x 存入*/
   ps->items[++ ps->top] = x;
   return;
}
/*---------------------------------------------------------------------------
功能：取得堆疊頂端元素
輸入：stack *ps   欲使用之堆疊指標
---------------------------------------------------------------------------*/
NODEPTR stacktop(stack	*ps)
{
   /* step 1: 判斷是否為空堆疊 */
   if (empty(ps))
   {
//      printf("Stack underflow\n");
      return NULL;
   }
   /* step 2: 傳回堆疊頂端的值 */
   return(ps->items[ps->top]);
}
// ==========================================================================
//                             樹狀結構運算
/*---------------------------------------------------------------------------
功能：取得一個配置記憶體的節點

---------------------------------------------------------------------------*/
NODEPTR getnode(){
   NODEPTR p;
   p = (NODEPTR) malloc(sizeof(struct nodetype));
   return(p);
}
/*---------------------------------------------------------------------------
功能：釋放一個節點

---------------------------------------------------------------------------*/
void freenode(NODEPTR p)
{
    free(p);
}
/*---------------------------------------------------------------------------
功能：建立樹

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
功能：設定左子樹

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
功能：設定右子樹

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
功能：後序走訪遞迴版

---------------------------------------------------------------------------*/
void postorder(NODEPTR ptr){
  if(ptr){
    postorder(ptr->left);
    postorder(ptr->right);
    printf("%3d",ptr->info);
  }
}
/*---------------------------------------------------------------------------
功能：前序走訪遞迴版

---------------------------------------------------------------------------*/
void preorder(NODEPTR ptr){
  if(ptr){
    printf("%3d",ptr->info);
    preorder(ptr->left);
    preorder(ptr->right);
  }
}
/*---------------------------------------------------------------------------
功能：中序走訪遞迴版

---------------------------------------------------------------------------*/
void inorder(NODEPTR ptr){
  if(ptr){
    inorder(ptr->left);
    printf("%3d",ptr->info);
    inorder(ptr->right);
  }
}
/*---------------------------------------------------------------------------
功能：後序走訪迴圈版

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
功能：前序走訪迴圈版

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
功能：中序走訪迴圈版

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
功能：程式進入點

---------------------------------------------------------------------------*/
int main(int argc, char* argv[])
{
  stack_init(&s);

  NODEPTR ptree;
  // example 0:單一節點
  ptree = maketree(0);

  randomize();
  int n=rand()%10;
  switch(n){
    case 1:
      // example 1:左邊單一節點
      setleft(ptree,1);
      break;
    case 2:
      // example 2:右邊單一節點
      setright(ptree,1);
      break;
    case 3:
      // example 3:左右各一個子節點
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
  // 堆疊測試
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
