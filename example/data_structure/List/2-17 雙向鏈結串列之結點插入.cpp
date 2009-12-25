 /**********************************************************/
 /**************** 程式名稱 : 2-17.c ***********************/
 /**************** 雙向鏈結串列之結點插入 ******************/

 #include<stdlib.h>
 struct double_list                  /* 雙向串列結構宣告 */
 {
  int data;                          /* 串列節點資料 */
  struct double_list *front;         /* 指向下一節點的前指標 */
  struct double_list *back;          /* 指向前一節點的後指標 */
 };
 typedef struct double_list dnode;   /* 雙向串列新節點型態 */
 typedef dnode *dlink;               /* 雙向串列新指標型態 */

 void print_double_list(dlink head)  /* 列印雙向鏈結串列 */
 {
   while (head !=NULL)               /* 拜訪串列節點迴路 */
   {
    printf("[%d]",head->data);       /* 列印節點資料 */
    head=head->front;                /* 指向下一節點 */
   }
   printf("\n");
 }

 /* 雙向鏈結串列之節點差入 */
 dlink insert_node(dlink head,dlink ptr,int value)
 {
  dlink new_node;                        /* 新節點的指標 */
  new_node=(dlink)malloc(sizeof(dnode)); /* 建立新節點 */
  if (!new_node)
     return NULL;
  new_node->data=value;                  /* 建立節點內容 */
  new_node->front=NULL;                  /* 設定前指標初值 */
  new_node->back=NULL;                   /* 設定後指標初值 */

  if (head==NULL)                        /* 如果串列是空的 */
     return new_node;                    /* 傳回新節點指標 */
  if (ptr==NULL)
  {
  /***  將節點插在第一個節點之前,成為串列開始 ***/
    new_node->front=head;                /* 新節點之前指標指向串列開始 */
    head->back=new_node;                 /* 原節點之後指標指向新節點 */
    head=new_node;                       /* 新節點成為串列開始 */
  }
  else
  {
   if (ptr->front==NULL)                 /* 下一個節點是否為NULL */
   {
     /*** 將節點插在串列最後 ***/
     ptr->front=new_node;                /* 最後節點前指標指向新節點 */
     new_node->back=ptr;                 /* 新節點後指標指向下一節點 */
   }
   else
   {
     /*** 將節點插入鏈結串列中間節點 ***/
     ptr->front->back=new_node;          /* 下一節點指向新節點 */
     new_node->front=ptr->front;         /* 新節點指向下一節點 */
     new_node->back=ptr;                 /* 新節點指向插入節點 */
     ptr->front=new_node;                /* 插入節點指向新節點 */
   }
  }
  return head;                           /* 傳回串列起始指標 */
 }

 void main()                             /* 主程式 */
 {
  dlink head=NULL;                       /* 雙向鏈結串列指標 */
  dlink tail=NULL;                       /* 串列最後的指標 */
  int list[6]={1,2,3,4,5,6};             /* 陣列內容 */
  int i;
  head=insert_node(head,head,list[0]);   /* 建立第一個節點 */
  print_double_list(head);               /* 印出鏈結串列之內容 */
  tail=head;                             /* 保留串列最後指標 */

  head=insert_node(head,NULL,list[1]);   /* 將節點插在第一個節點之前 */
  print_double_list(head);               /* 印出插入後的串列 */

  head=insert_node(head,tail,list[2]);   /* 將節點插入串列最後 */
  print_double_list(head);               /* 印出插入後的串列 */

  for(i=3;i<6;i++)                       /* 建立串列節點 */
  {
    head=insert_node(head,head,list[i]); /* 將節點插入節點與串列中間 */
    print_double_list(head);             /* 印出插入後的串列 */
  }
 }
