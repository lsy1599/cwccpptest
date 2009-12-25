 /**************************/
 /*      程式 ch2_3.c      */
 /*     計算後序運算式的值 */
 /**************************/


# include <stdio.h>
# include <math.h>
# include <ctype.h>
# include <stdlib.h>

/*  陣列堆疊宣告 */

 #define N 100
 double stack[N];
 int top=-1;


/****************************************************************
*	push函式部分    ( stack〔〕　宣告為全域變數 )
*****************************************************************/

void push(double d, int *top )   /*此處之top為一指標型區域變數*/

{   
      if (*top == N-1)
	  {
      printf("堆疊滿了\n");			/* 注意堆疊大小 */
        exit(1);				/* 加入失敗，執行結束 */
       }   /* end if */
     else
      {
        (*top)++;          		        /*指標指向頂端，增量增加1*/
        stack[*top]=d;				/*儲存資料d 於堆疊頂端　*/
       }   /* end else */

}     /* end of push 函數 */

 
/**********************************************************************
*	pop函式部分    ( stack〔〕　宣告為全域變數 )
**********************************************************************/

double pop(int *top)          

 {                                     
  if (*top == -1)                               /* 注意空堆疊情形*/
     { printf("堆疊空了\n");
       exit(1);					/*刪除失敗，執行結束 */
      }
  else
	 return(stack[(*top)--]);
 }


/***************************************************************************
*  oper函數  ( 檢查有效二元運算子，並計算該運算運用在其後兩參數之結果)
***************************************************************************/

double oper(int symb, double op1, double op2)   
{
   switch (symb) {
case '+' :  return (op1+op2);	/* 相加運算 */
case '-' :  return (op1-op2);	/* 相減運算 */
case '*' :  return (op1*op2);	/* 相乘運算 */
case '/' :  return (op1/op2);	/* 相除運算 */
case '$' :  return (pow(op1,op2));	/*次方運算, pow定義在math.h中*/
default  : printf("%s", "illegal operation"); 
            exit(1);				
     }   /* end switch*/
}     /* end oper函數 */


/*****************************************************************
*                  eva_postfix函數  (計算後序運算式值)
*****************************************************************/
 double eval_postfix(char expr[])
{
    char	c;
	int position;        
    double opnd1, opnd2, value;

    top = -1;                 /* initialize stack*/

  for  (position = 0; (c = expr[position]) != '\0'; position++)
   
  {	/*  將儲存後序運算式從頭到尾依序讀出　*/
	/*  字串之 '\0'　為字串終止控制指令　*/ 
  
   if (isdigit(c))                       /* 將自十進位數值字元轉換為可計算之double */
                                     /*　 isdigit(c)　函數定義在　ctype.h 中 */
	push( (double)(c-'0'),&top);     /* 再將其放入stack中 */
   
   else                    	         /*  此時讀進之字元為　operator  */
      {
	opnd2 = pop(&top);
	opnd1 = pop(&top);              /* 取出堆疊最頂端的兩個運算元　*/
        value = oper(c, opnd1, opnd2);  /* 並執行運算子所對應之計算 */
	push(value, &top);		/*	將計算結果放入堆疊中 */
	
      }   /* end else */
  }  
     return (pop(&top));                /* 傳回堆疊內唯一值　*/
}   /* end eval_postfix */



/*****************************************************************
*                   主程式部分  
*****************************************************************/

void main()
 {
   char expr[N];
   int position = 0;
  
   printf("\n  please enter a postfix expression ==>");
   
   while ((expr[position++] = getchar()) != '\n' );
                                        /*　 getchar()　函數定義在　ctype.h 中 */

   expr[--position] = '\0';
   printf("\n");
   printf ("\n %s %s ", " the original exp is ", expr);
   printf("\n");
		                         /* 列印原始後序運算式　*/
 
   printf("\n");
   printf("\n  eval_postfix = %6.2f", eval_postfix(expr));
   printf("\n");
   printf("\n");					 /*　列印計算後之計算值　*/

} /* end main*/
