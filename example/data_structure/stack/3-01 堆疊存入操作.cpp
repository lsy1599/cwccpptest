 /************************************************************/
 /******************* �{���W�� : 3-1.c ***********************/
 /******************* ���|�s�J�ާ@ ***************************/
  int  push(char  x)         /* x ��push �Jstack����*/
  {                          /* �{�����q */
   if(stack_full(&s))
     return(0);              /* STACK �w�� */
   s.top=s.top + 1;
   s.item[s.top] = x;
   return(1);                /* ���\�NX�s�JSTACK�� */
  }
  int satck_full(stack *S)
  {
   if (s->top = N-1)
     return(1);              /* STACK���F,�Ǧ^1 */
   else
     return(0);              /* STACK����,�Ǧ^0 */
  }

