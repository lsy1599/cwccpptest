 /**************************/
 /*     �{�� ch2_3.c      */
 /*     �p���ǹB�⦡���� */
 /**************************/


# include <stdio.h>
# include <math.h>
# include <ctype.h>
# include <stdlib.h>

/*  �}�C���|�ŧi */

 #define N 100
 double stack[N];
 int top = -1; 


/****************************************************************
*	push�禡����    ( stack�e�f�@�ŧi�������ܼ� )
*****************************************************************/

void push(double d, int *top )   /*���B��top���@���Ы��ϰ��ܼ�*/

{
      if (*top == N-1)
{
      printf("���|���F\n");			/* �`�N���|�j�p */
        exit(1);				/* �[�J���ѡA���浲�� */
       }   /* end if */
     else
      {
        (*top)++;          		        /*���Ы��V���ݡA�W�q�W�[1*/
        stack[*top]=d;				/*�x�s���d ����|���ݡ@*/
       }   /* end else */

}     /* end of push ��� */

 
/**********************************************************************
*	pop�禡����    ( stack�e�f�@�ŧi�������ܼ� )
**********************************************************************/

double pop(int *top)          

 {                                     
  if (*top == -1)                               /* �`�N�Ű��|����*/
     { printf("���|�ŤF\n");
       exit(1);					/*�R�����ѡA���浲�� */
      }
  else
	 return(stack[(*top)--]);
 }


/***************************************************************************
*  oper���  ( �ˬd���ĤG���B��l�A�íp��ӹB��B�Φb����ѼƤ����G)
***************************************************************************/

double oper(int symb, double op1, double op2)   
{
   switch (symb) {
case '+' :  return (op1+op2);	/* �ۥ[�B�� */
case '-' :  return (op1-op2);	/* �۴�B�� */
case '*' :  return (op1*op2);	/* �ۭ��B�� */
case '/' :  return (op1/op2);	/* �۰��B�� */
case '$' :  return (pow(op1,op2));	/*����B��, pow�w�q�bmath.h��*/
default  : printf("%s", "illegal operation"); 
            exit(1);				
     }   /* end switch*/
}     /* end oper��� */


/*****************************************************************
*                  eva_postfix���  (�p���ǹB�⦡��)
*****************************************************************/
 double eval_postfix(char expr[])
{
    int	 position;   
	char c;
    double opnd1, opnd2, value;

    top = -1;                 /* initialize stack*/

  for  (position = 0; (c = expr[position]) != '\0'; position++)
  { 
	/*  �N�x�s��ǹB�⦡�q�Y����̧�Ū�X�@*/
	/*  �r�ꤧ '\0'�@���r��פ����O�@*/ 
   if (isdigit(c))                       /* �N�ۤQ�i��ƭȦr���ഫ���i�p�⤧double */
   { printf (" come here \n");       /*�@ isdigit(c)�@��Ʃw�q�b�@ctype.h �� */
	push( (double)(c-'0'),&top);     /* �A�N���Jstack�� */
   }
   else                   	         /*  ����Ū�i���r�����@operator  */
      {
    	opnd2 = pop(&top);
    	opnd1 = pop(&top);              /* ���X���|�̳��ݪ���ӹB�⤸�@*/
        value = oper(c, opnd1, opnd2);  /* �ð���B��l�ҹ������p�� */
    	push(value, &top);		/*	�N�p�⵲�G��J���|�� */
      }   /* end else */
  }  
     return (pop(&top));                /* �Ǧ^���|���ߤ@�ȡ@*/
}   /* end eval_postfix */



/*****************************************************************
*                   �D�{������  
*****************************************************************/

void main()
 {
   char expr[N];
   int position = 0;
    
   printf(" �п�J�@��Ǧ� \n");

   while ((expr[position++] = getchar()) != '\n' );
                                        /*�@ getchar()�@��Ʃw�q�b�@ctype.h �� */

   expr[--position] = '\0';
   printf ("\n %s %s ", " the original exp is ", expr);
		                         /* �C�L��l��ǹB�⦡�@*/
 

   printf("\n  eval_postfix = %f\n", eval_postfix(expr));
					 /*�@�C�L�p��ᤧ�p��ȡ@*/
   printf(" \n");

} /* end main*/