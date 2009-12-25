 /************************************************************/
 /***************** 程式名稱 : 2-18.c ************************/
 /***************** 雙向鏈結串列之節點刪除 *******************/

 #include<stdlib.h>
 struct double_list                    /* 雙向鏈結串列結構宣告 */
 {
 int data;                             /* 串列節點資料 */
 struct double_list *front;            /* 指向下一節點的前指標 */
 struct double_list *back;             /* 指向前一節點的後指標 */
 };
 typedef struct double_list dnode;     /* 雙向鏈結串列新節點型態 */
 typedef dnode *dlink;                 /* 雙向鏈結串列新指標型態 */

 dlink create_double_list(int *array,int len) /* 建立雙向鏈結串列 */
 {
   dlink head;                         /* 雙向串列指標 */
   dlink before;                       /* 前一節點的指標 */
   dlink new_node;                     /* 新節點的指標 */
   int i;
   head=(dlink)malloc(sizeof(dnode));  /* 建立第一個節點並配置memory空間 */
   if(!head)
     return NULL;
   head->data=array[0];                /* 設定節點內容 */
   head->front=NULL;                   /* 設定前指標初值 */
   head->back=NULL;                    /* 設定後指標初值 */
   before=head;                        /* 指向鏈結串列第一節點 */
   for(i=1;i<len;i++)                  /* 建立其它節點之迴圈 */
   {
     new_node=(dlink)malloc(sizeof(dnode));
     if(!new_node)
       return NULL;
     new_node->data=array[i];          /* 設定節點內容 */
     new_node->front=NULL;             /* 設定前指標初值 */
     new_node->back=before;            /* 將新節點指向前一節點 */
     before->front=new_node;           /* 將前指標指向新節點 */
     before=new_node;                  /* 新節點成為前節點 */
   }
   return head;                        /* 傳回串列起始指標 */
 }

 void free_double_list(dlink head)     /* 釋放雙向鏈結串列之memory空間 */
 {
   dlink ptr;                          /* 儲存目前節點指標 */
   while(head !=NULL)                  /* 拜訪串列其它節點迴圈 */
   {
     ptr=head;                         /* 保留目前節點指標 */
     head=head->front;                 /* 指向下一節點 */
     free(ptr);                        /* 釋放目前節點之memory空間 */
   }
 }

 void print_double_list(dlink head,dlink now) /* 雙向鏈結串列之列印 */
 {
   while (head != NULL)
   {
     if (head==now)
	printf("#%d#",head->data);            /* 列印目前節點資料 */
     else
	printf("[%d]",head->data);            /* 列印節點資料 */
     head=head->front;                        /* 指向下一節點 */
   }
   printf("\n");
 }

 dlink delete_node(dlink head,dlink ptr) /* 雙向鏈結串列之節點刪除 */
 {
   if (ptr->back==NULL)                  /* 若前節點為NULL */
   {
     head=head->front;           /* 刪除第一個節點並將指標指到下一節點 */
     head->back=NULL;            /* 設定指向前節點之指標 */
   }
   else
   {
     if(ptr->front==NULL)        /* 若下一節點為NULL */
     {
      ptr->back->front=NULL;     /* 刪除最後節點並將前節點指標指向NULL */
     }
     else                        /* 刪除串列之中間節點 */
     {
      ptr->back->front=ptr->front;   /* 將前節點指標指到下一節點 */
      ptr->front->back=ptr->back;    /* 將下節點指標指向前節點 */
     }
   }
   free(ptr);                    /* 釋放刪除節點之memory空間 */
   return head;                  /* 傳回串列起始指標 */
 }

 void main()                     /* 主程式 */
 {
   dlink head;                   /* 雙向鏈結串列指標 */
   dlink now=NULL;               /* 目前節點指標 */
   int list[6]={4,5,6,7,8,9};    /* 設定陣列內容 */
   int choice;
   head=create_double_list(list,6); /* 呼叫建立雙向鏈結串列副程式 */
   if (head==NULL)
   {
      printf ("記憶體配置失敗! \n");
      exit(1);
   }
   while(1)                       /* 主迴圈 */
   {
    if (now==NULL)
       now=head;                  /* 將now指向第一節點 */
    printf("串列內容是: ");
    print_double_list(head,now);  /* 列印鏈結串列內容 */
    printf("[1]往下移動 [2]往回移動 [3]刪除節點 [4]離開==>");
    scanf("%d",&choice);
    switch(choice)
    {
     case 1: if (now->front !=NULL)
	       now=now->front;      /* 指向下一節點 */
	     else
	       printf("刪除串列尾部之節點\n");
	     break;
     case 2: if (now->back !=NULL)
	       now=now->back;       /* 指向前一節點 */
	     else
	       printf("刪除串列開始之節點\n");
	     break;
     case 3: if (head !=NULL)       /* 刪除目前節點 */
	     {
	      head=delete_node(head,now);
	      now=head;             /* 將now指向第一個節點 */
	     }
	     else
	      printf("串列是空的\n");
	     break;
     case 4: exit(1);               /* 結束程式 */
    }
  }
  free_double_list(head);
 }


