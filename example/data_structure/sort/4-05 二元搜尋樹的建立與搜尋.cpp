 /******************************************************************/
 /******************* 程式名稱 : 4-5.c *****************************/
 /******************* 二元搜尋樹的建立與搜尋 ***********************/

 #include <stdlib.h>
  struct tree                       /* 宣告樹狀結構 */
 {
 int data;                          /* 二元樹節點資料 */
 struct tree *left;                 /* 左子樹的指標 */
 struct tree *right;                /* 右子樹的指標 */
 };
 typedef struct tree node;          /* 定義二元樹的結構新型態 */
 typedef node *bintree;             /* 宣告二元樹節點指標型態 */


 bintree create(int *data,int post) /* 建立二元樹 */
 {
   bintree newnode;                 /* 新節點指標 */
   if (data[post]== 0 || post >15)  /*終止條件*/
      return NULL;
   else
   {
     newnode= (bintree)malloc(sizeof(node)); /* 配置memory空間 */
     newnode->data = data[post];             /* 建立節點內容 */
     newnode->left = create(data,2*post);    /* 以遞迴方式建立左子樹 */
     newnode->right = create(data,2*post+1); /* 以遞迴方式建立右子樹 */
     return newnode;
   }
 }


 bintree find(bintree ptr, int value)  /* 二元樹的二分搜尋 */
 {
   while (ptr != NULL)
   {
    if (ptr->data == value)            /* 找到所要找的資料 */
       return ptr;                     /* 傳回節點指標 */
    else
       if (ptr->data > value)          /* 若data > value */
	   ptr=ptr->left;              /* 搜尋左子樹 */
       else
	   ptr=ptr->right;            /* 搜尋右子樹 */
   }
   return NULL;                       /* 沒有找到所要的資料 */
 }


 bintree search(bintree ptr,int value) /* 二元樹的搜尋追蹤 */
 {
   bintree pointer1,pointer2;
   if (ptr != NULL)                    /* 終止條件 */
   {
     if (ptr->data == value)           /* 找到所要找的資料 */
	return ptr;                    /* 傳回節點指標 */
     else
     {
	pointer1 = search(ptr->left,value);  /* 以遞迴方式搜尋左子樹 */
	pointer2 = search(ptr->right,value); /* 以遞迴方式搜尋右子樹 */
	if (pointer1 != NULL)
	   return pointer1;                  /* 所要找的資料在左子樹 */
	else
	{
	   if (pointer2 != NULL)
	      return pointer2;                  /* 所要找的資料在右子樹 */
	   else
	      return NULL;                      /* 沒有找到 */
	}
     }
   }
   else
     return NULL;                             /* 所要找的資料是葉節點 */
 }


 void main()
 {
   bintree root=NULL;                         /* 樹根指標 */
   bintree ptr=NULL;
   int value;
   int data[16]={0,5,4,6,2,0,0,8,1,3,0,0,0,0,7,9};
   root = create(data,1);                     /* 建立樹狀結構 */
   printf("請輸入找尋節點資料(1-9)==>");
   scanf("%d", &value);                       /* 讀取節點資料 */
   ptr = find(root,value);                    /* 二分搜尋 */
   if (ptr != NULL)
      printf("二分搜尋:節點資料是[%d]\n",ptr->data);
   else
      printf("二分搜尋:節點沒有找到\n");
   ptr = search(root,value);                  /* 二元樹追蹤搜尋 */
   if (ptr!=NULL)
      printf("追蹤搜尋:節點資料是[%d]\n",ptr->data);
   else
      printf("追蹤搜尋:節點沒有找到\n");
 }

