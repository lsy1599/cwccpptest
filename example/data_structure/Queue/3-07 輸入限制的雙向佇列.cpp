 /*****************************************************************/
 /******************* 程式名稱 : 3-7.c ****************************/
 /******************* 輸入限制的雙向佇列 **************************/

 #define MAXQ 10                  /* 定義佇列的最大容量 */
 int queue[MAXQ];                 /* 宣告佇列的陣列 */
 int front = -1;                  /* 佇列的前端指標 */
 int rear = -1;                   /* 佇列的後端指標 */


 int queue_push(int value)        /* 佇列資料的存入 */
 {
   if ( rear + 1 == front || (rear == (MAXQ-1) && front <=0)
				  /* 檢查佇列是否全滿 */
      return -1;                  /* 若是則無法存入 */
   rear++;                        /* 後端指標往前移 */
   if ( rear == MAXQ )            /* 是否超過佇列大小 */
      rear = 0;                   /* 若是則從頭開始 */
   queue[rear] = value;           /* 否則將資料存入佇列 */
 }


 int queue_pop_rear()             /* 從佇列的後端取出資料 */
 {
   int temp;
   if ( front == rear )           /* 檢查佇列是否是空 */
      return -1;                  /* 若是,無法取出 */
   temp = queue[rear];            /* 否則,將資料取出,後端指標往前移 */
   rear--;
   if ( rear < 0 && front != -1)  /* 是否超出佇列大小 */
      rear = MAXQ =1;             /* 若是,從頭開始 */
   return temp;                   /* 否則,傳回temp */
 }


 int queue__pop_front()           /* 從佇列前端取出資料 */
 {
   if ( front == rear )           /* 檢查佇列是否是空的 */
      return -1;                  /* 若是,無法取出 */
   front++;                       /* 否則,前端指標往前移 */
   if ( front == MAXQ )           /* 是否超過佇列大小 */
      front = 0;                  /* 若是,從頭開始 */
   return queue[front];           /* 否則,佇列取出 */
 }


 void main()                      /* 主程式 : 雙向佇列的操作 */
 {
   int input_list[6] = {4,5,6,7,8,9};  /* 輸入的陣列資料 */
   int output_list[6];                 /* 儲存取出的資料 */
   int choice;
   int i,temp,sp = 0;

   for ( i = 0; i < 6; i++ )           /* 將陣列存在佇列 */
      queue_push(input_list[i]);
   while ( front != rear )             /* 主迴圈 */
   {
     printf("[1]從後端取出 [2]從前端取出==>");
     scanf("%d",&choice);
     switch ( select )
     {
       case 1 : temp = queue_pop_rear();
		output_list[sp++] = temp;
		break;

       case 2 : temp = queue_pop_front();
		output_list[sp++] = temp;
		break;
     }
   }
   printf("原來陣列的內容:");
   for (i=0; i < 6; i++)
       printf([%]",input_list[i]);
   printf("\n佇列取出的順序:");
   for (i=0 ;i<6;i++)
       printf("[%d]",output_list[i]);
   printf("\n");
 }
