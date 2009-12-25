/****************************************************************/
/****************** 程式名稱 : 2-19.c ***************************/
/****************** 環狀鏈結串列之節點插入與刪除 ****************/

 #include<stdlib.h>
 struct cycle_list                 /* 環狀鏈節串列結構宣告 */
 {
  int data;                        /* 節點資料 */
  struct cycle_list *link;         /* 節點串列指標 */
 };
 typedef struct cycle_list node;   /* 環狀鏈結串列新型態 */
 typedef node *clink;              /* 串列指標新型態 */

 void print_cycle_list(clink head) /* 列印環狀鏈結串列之內容 */
 {
  clink ptr;
  head=head->link;                 /* 串列指標指到第一節點 */
  ptr=head;                        /* ptr指到串列開始 */
  do                               /* 拜訪串列節點迴圈 */
  {
    printf("[%d]",ptr->data);      /* 列印節點資料 */
    ptr=ptr->link;                 /* ptr指到下一個節點 */
  }while (head !=ptr && head != head->link);
  printf("\n");
 }

 clink insert_node(clink head,clink ptr,int value)
 {                                 /* 環狀鏈結串列之節點插入 */
   clink new_node;                 /* 新節點指標 */
   new_node=(clink)malloc(sizeof(node)); /* 建立新的節點並配置memory空間 */
   if (!new_node)                  /* 檢查記憶體 */
      return NULL;
   new_node->data=value;           /* 設定節點的內容 */
   new_node->link=NULL;            /* 設定指標的初值 */
   if (head==NULL)                 /* 若串列是空的 */
   {
     new_node->link=new_node;      /* link指標指到本身節點 */
     return new_node;              /* 傳回新節點指標 */
   }
   if (ptr==NULL)
   {                               /* 將新的節點插在第一個節點之前 */
     new_node->link=head->link;    /* 新節點指向下一節點 */
     head->link->link=new_node;    /* 前一節點指向新的節點 */
   }
   else
   {                               /* 將新的節點插在某節點之後 */
     new_node->link=ptr->link;     /* 新節點指向下一節點 */
     ptr->link=new_node;           /* 前一節點指向新的節點 */
   }
   if (ptr==head)                   /* 將新的節點插入最後一節點 */
      head=new_node;                /* 改變head指標至串列開始 */
   return head;
 }

 clink delete_node(clink head,clink ptr)
 {                                  /* 環狀鏈結串列之節點刪除 */
  clink front;                      /* 前一節點指標 */
  if (head==NULL)                   /* 若串列是空的 */
     return NULL;
  if (ptr==head->link)
  {                                 /* 刪除第一個節點 */
    head->link=ptr->link;           /* 將link指標指向下一節點 */
  }
  else
  {
   front=head;
   if(head != head->link)           /* 若串列多於一個節點 */
   while (front->link != ptr)       /* 找prt節點的前一節點 */
       front=front->link;           /* 指到下一個節點 */
   front->link = ptr->link;         /* 前節點指向下一節點 */
  }
  if (ptr==head)                    /* 刪除最後節點 */
    head=front;
  free(ptr);                        /* 釋回memory空間 */
  return head;                      /* 傳回串列起始指標 */
 }

 void main()                        /* 主程式 */
 {
  clink head=NULL;                  /* 環狀鏈結串列指標 */
  int list[6]={3,4,5,6,7,8};        /* 陣列內容 */
  int i;
   head=insert_node(head,head,list[0]);  /* 建立第一個節點 */
   printf(" 建立第一節點:");
   print_cycle_list(head);          /* 印出鏈結串列 */
   for (i=2;i<6;i++)                /* 以迴圈建立串列節點 */
   {
    head=insert_node(head,head->link,list[i]); /* 將新節點插在第一個節點前 */
    printf("插入第一個節點之前:");
    print_cycle_list(head);         /* 印出串列 */
   }
   for (i=2;i<6;i++)
   {                                /* 將新節點插在某節點之後 */
    head=insert_node(head,head->link,list[i]);
    printf("插入新節點之後 : ");
    print_cycle_list(head);         /* 印出串列 */
   }

   head=delete_node(head,head->link); /* 刪除第一個節點 */
   printf("刪除第一個節點:");
   print_cycle_list(head);          /* 印出串列 */
   printf("刪除最後一個節點:");
   head=delete_node(head,head);
   print_cycle_list(head);
 }
