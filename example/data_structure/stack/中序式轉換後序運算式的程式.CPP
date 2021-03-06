 /**********************************/
 /*      程式 ch2_4.cpp            */
 /*     中序式轉換後序運算式的程式 */
 /**********************************/


# include <stdio.h>
# include <math.h>
# include <ctype.h>
# include <stdlib.h>



/*  陣列堆疊宣告 */

#define N 100      /* N為全域變數 */
 
 int top=-1;

 typedef enum{left_paren,right_paren, plus, minus,
	     times, divide, mode, expon, operand} precedence;  /* 定義 優先順序之資料型態 */

 precedence stack[N];


 int ISP[]= {1,5,2,2,3,3,3,4,0};
 int ICP[]= {6,5,2,2,3,3,3,4,0};

/****************************************************************
*	empty函式部分    ( 判斷堆疊是否已空 )
*****************************************************************/


 int empty(int *top)

 {
    if (*top == -1)
       return (1);         /* true = 1 */
    else
       return (0);       /* false = 0 */
 }  /* end empty */



/****************************************************************
*	push函式部分    ( stack〔〕　宣告為全域變數 )
********************************************************************/

void push(precedence d, int *top )   /*此處之top為一指標型區域變數*/

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

precedence pop(int *top)          

 {                                     
  if (empty(top))                              /* 注意空堆疊情形*/
     { printf("堆疊空了\n");
       exit(1);					/*刪除失敗，執行結束 */
      }
  else
	 return(stack[(*top)--]);
 }

/***************************************************************************
*  print_token 函數
***************************************************************************/

void print_symbol (precedence num)
{
 
   switch (num)
    {             /* 將印出對應之運算子符號� */

	case plus  : printf("%c", '+'); break;
	case minus : printf("%c", '-'); break;
	case times : printf("%c", '*'); break; 
	case divide : printf("%c", '/'); break; 
	case mode  : printf("%c", '%'); break;
        case expon: printf("%c", '$'); break;

    }   /* end switch*/

}     /* end  print_symbol */


/***************************************************************************
*  get_token 函數  (讀取字元Token，並按照其優先順序分類)
***************************************************************************/

precedence get_token  (char token)
{

   switch (token) {             /* 將讀進之Token 量化並分類 */
	case '(' :  return left_paren;	/* 此時 '(' 等於 left_paren = 0  */
	case ')' :  return right_paren;	/* 此時 ')' 等於 right_paren = 1  */
	case '+' :  return plus;	/* 依此類推 */
	case '-' :  return minus;
	case '*' :  return times;
	case '/' :  return divide;
	case '%' :  return mode;
	case '$' :  return expon;
	default  :  return operand;
     }   /* end switch*/
}     /* end get_token 函數 */


/*********************************************************************
*                  infix_to_postfix函數  (將中序式轉換為計後序運算式)
*********************************************************************/
 void infix_to_postfix(char expr[])
{
    int	 position=0;           /* 目前讀取位元之位置 */
    char c;                    /* 讀取一個字元 */
    precedence token;                /* 分類後之token */

    top = -1;                 /* initialize stack*/
    
  for  (position = 0; (c = expr[position]) != '\0'; position++)
   
             /*  將儲存中序運算式從頭到尾依序讀出　*/
	     /*  字串之 '\0'　為字串終止控制指令　*/
    {
       token = get_token(c);             /* 讀取一個字元 */


       switch (token)
       {
                 
	case operand :             	/* 此時 token 為運算元  */
	     printf("%c", c);
	     break;
	      
	case right_paren :

	    {
	      while(stack[top] != left_paren) /* 自堆疊頂端逐一取出並輸出，直到取出 '(' 為止 */
	     {
	       print_symbol(stack[top]);
	       pop(&top);          /* 移除堆疊頂端之'(', 不須印出 */
	     }     /* end while */
	     pop(&top);
	    }
	     break;

	default:

             if (empty(&top))                /* empty stack, push the token directly */ 
		   push(token, &top);
	     else
	       {
                
	        while ((!empty(&top)) && ( ISP[stack[top]] >= ICP[token]))
	          
	          print_symbol(pop(&top));

	       
                                  /* push token to stack */
	       push(token, &top);

	      }      /* end if */

     } /* end switch */

   }   /* end for */

  
       do                
       {                           /* end of string , pop from stack until empty */
	 token = pop(&top);
	 print_symbol(token);

	} while (!empty(&top));      


}   /* end infix_to_postfix */



/*****************************************************************
*                   主程式部分  
*****************************************************************/

void main()
 {
   char expr[N];
   int position;


  
       printf("請輸入一中序運算式\n");
       position = 0;

       while ((expr[position++] = getchar()) != '\n' );
					/*　 getchar()　函數定義在　ctype.h 中 */

       expr[--position] = '\0';                        
       printf ("\n%s %s ", "原始中序運算式=        ", expr);
					 /* 列印原始中序運算式　*/
  
       printf ("\n後序運算式= ");
       infix_to_postfix(expr);
    
	  printf(" \n");

    
  
} /* end main*/
