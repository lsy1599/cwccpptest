
 /**************************/
 /*      程式 ch4_1.cpp      */
 /*      陣列環狀佇列      */
 /**************************/

 #include <stdio.h>
 #define N 100
 int queue[N];
 int front=-1, rear=-1;


 /*加入資料於環狀佇列內*/
 void add(int d)
 {
   if(front == (rear+1)%N) {
      printf("環狀佇列滿了\n");
      exit(1);
   }
   rear=(rear+1)%N;
   queue[rear]=d;
 }


 /*傳回並刪除環狀佇列的前端元素*/
 int delete()
 {
   if(front == rear){
      printf("環狀佇列已空\n");
      exit(1);
   }
   front=(front+1)%N;
   return(queue[front]);
 }


 void main()
 {
   int d, loop=1;                   /*loop表迴圈控制變數*/
   char input[7];

   clrscr();                        /*清除螢幕畫面*/
   printf("*** 陣列環狀佇列 ***\n");
   printf("可執行下列指令 : add, delete, +, -, exit\n\n");
   do {
      printf("==>");
      scanf("%s",input);
      if(strcmp(input,"add")==0){  /*字串比較若相等則傳回0之值*/
	 printf("輸入數值:");
	 scanf("%d",&d);
	 add(d);
      }
      else if(strcmp(input,"delete")==0)
	 printf("%d\n",delete());
      else if(strcmp(input,"+")==0)
	 add(delete()+delete());
      else if(strcmp(input,"-")==0)
	 add(delete()-delete());
      else if(strcmp(input,"exit")==0)
	 loop=0;
      else
	 printf("輸入錯誤!\n");
   } while(loop);
   printf("Bye-Bye !\n");
 }