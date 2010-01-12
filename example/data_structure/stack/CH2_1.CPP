 /**************************/
 /*      �{�� ch2_1.c      */
 /*        �}�C���|        */
 /**************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include <conio.h>
 #include <string.h>


 #define N 100
 int stack[N];
 int top=-1;


 /*�[�J��Ʃ���|��*/
 void push(int d)
 {
   if(top == N-1) {
      printf("���|���F\n");
      exit(1);
   }
   stack[++top]=d;
 }


 /*�R�����|�����ݸ��*/
 int pop()
 {
   if(top == -1){
      printf("���|�ŤF\n");
      exit(1);
   }
   return(stack[top--]);
 }


 void main()
 {
   int d, loop=1;                   /*loop���j�鱱���ܼ�*/
   char input[5];

 /*  clrscr();        */                /*�M���ù��e��*/
   printf("*** �}�C���| ***\n");
   printf("�i����U�C���O : push, pop, +, -, exit\n\n");
   do {
      printf("==>");
      scanf("%s",input);
      if(strcmp(input,"push")==0){  /*�r�����Y�۵��h�Ǧ^0����*/
	 printf("��J�ƭ�:");
	 scanf("%d",&d);
	 push(d);
      }
      else if(strcmp(input,"pop")==0)
	 if(top == -1)
	    printf("���|�ŤF\n");
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
	 printf("��J���~!\n");
   } while(loop);
   printf("Bye-Bye !\n");
 }