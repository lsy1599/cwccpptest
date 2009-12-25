 /**********************************************************/
 /*************** 程式名稱 : 2-15.c ************************/
 /*************** 兩連結串列的連結 *************************/
 #include <stdlib.h>

 struct list                                /* 串列結構宣告 */
 {
   int num;                                 /* 各節點編號 */
   struct list *next;                       /* 指向下一個節點 */
 };
 typedef struct list node;                  /* 定義新的串列型態 */
 typedef node *link;                        /* 定義新的指標型態 */

 void print_list(link ptr)                  /* 連結串列的列印 */
 {
    while (ptr != NULL)                     /* 拜訪串列中各節點 */
    {
       printf("[%d]",ptr->num);             /* 列印節點中的資料 */
       ptr=ptr->next;                       /* 指向下一節點 */
    }
    printf("\n");
 }

 link create_list(int *array,int len)       /* 建立連結串列 */
 {
      link head;                            /* 指到串列的開頭 */
      link ptr,ptr1;
      int i;
					    /* 建立第一個節點 */
      head=(link) malloc(sizeof(node));     /* 配置memory空間 */
      if (!head)
	 return NULL;
      head->num = array[0];                  /* 設定節點的內容 */
      head->next = NULL;
      ptr=head;
      for(i=1;i<len;i++)                     /* 建立其它節點 */
      {
	ptr1=(link) malloc(sizeof(node));
	if (!ptr1)
	   return NULL;
	ptr1->num=array[i];                  /* 建立節點內容 */
	ptr1->next=NULL;
	ptr->next=ptr1;                      /* 連結下一個節點 */
	ptr=ptr->next;
      }
      return head;
 }

 link concate(link ptr1,link ptr2)         /* 連結串列的連結 */
 {
     link ptr;
     ptr=ptr1;                             /* 指向第一個串列的開始 */
     while (ptr->next != NULL)             /* 找出第一個串列的結束*/
       ptr=ptr->next;                      /* 指向下一節點 */
     ptr->next=ptr2;                       /* 連結第二個串列 */
     return ptr1;
 }

 void main()              /* 主程式:連結由兩個陣列內容所建立的串列 */
 {
    int list1[6]={1,2,3,4,5,6};            /* 陣列一的內容 */
    int list2[5]={7,8,9,10,11};            /* 陣列二的內容 */
    link ptr,ptr1,ptr2;
    ptr1=create_list(list1,6);             /* 建立第一個串列 */
    if (ptr1==NULL)
    {
       printf("記憶體配置失敗!\n");
       exit(1);
    }
    ptr2=create_list(list2,5);             /* 建立第二個串列 */
    if (ptr2==NULL)
    {
       printf("記憶體配置失敗!\n");
       exit(1);
    }
    ptr=concate(ptr1,ptr2);                /* 呼叫連結兩串列副程式 */
    print_list(ptr);                       /* 印出連結串列 */
 }
