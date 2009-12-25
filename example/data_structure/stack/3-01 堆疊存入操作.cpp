 /************************************************************/
 /******************* 程式名稱 : 3-1.c ***********************/
 /******************* 堆疊存入操作 ***************************/
  int  push(char  x)         /* x 為push 入stack元素*/
  {                          /* 程式片段 */
   if(stack_full(&s))
     return(0);              /* STACK 已滿 */
   s.top=s.top + 1;
   s.item[s.top] = x;
   return(1);                /* 成功將X存入STACK中 */
  }
  int satck_full(stack *S)
  {
   if (s->top = N-1)
     return(1);              /* STACK滿了,傳回1 */
   else
     return(0);              /* STACK未滿,傳回0 */
  }

