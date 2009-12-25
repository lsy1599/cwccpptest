 /**************************/
 /*      程式 ch2_1.c      */
 /*        陣列堆疊        */
 /**************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include <conio.h>
 #include <string.h>


 #define N 100
 int stack[N];
 int top=-1;


 /*加入資料於堆疊內*/
 void push(int d)
 {
   if(top == N-1) {
      printf("堆疊滿了\n");
      exit(1);
   }
   stack[++top]=d;
 }


 /*刪除堆疊的頂端資料*/
 int pop()
 {
   if(top == -1){
      printf("堆疊空了\n");
      exit(1);
   }
   return(stack[top--]);
 }


 void main()
 {
   int d, loop=1;                   /*loop表迴圈控制變數*/
   char input[5];

 /*  clrscr();        */                /*清除螢幕畫面*/
   printf("*** 陣列堆疊 ***\n");
   printf("可執行下列指令 : push, pop, +, -, exit\n\n");
   do {
      printf("==>");
      scanf("%s",input);
      if(strcmp(input,"push")==0){  /*字串比較若相等則傳回0之值*/
	 printf("輸入數值:");
	 scanf("%d",&d);
	 push(d);
      }
      else if(strcmp(input,"pop")==0)
	 if(top == -1)
	    printf("堆疊空了\n");
	 else
	    printf("%d\n",pop());
      else if(strcmp(input,"+")==0)
	  {
	  int a = pop();
          int b = pop();
	      push(a+b);
          }
      else if(strcmp(input,"-")==0)
	 push(pop()-pop());
      else if(strcmp(input,"exit")==0)
	 loop=0;
      else
	 printf("輸入錯誤!\n");
   } while(loop);
   printf("Bye-Bye !\n");
 }