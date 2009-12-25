 /**********************************/
 /*      µ{¦¡ ch2_4.cpp            */
 /*     ¤¤§Ç¦¡Âà´««á§Ç¹Bºâ¦¡ªºµ{¦¡ */
 /**********************************/


# include <stdio.h>
# include <math.h>
# include <ctype.h>
# include <stdlib.h>



/*  °}¦C°ïÅ|«Å§i */

#define N 100      /* N¬°¥þ°ìÅÜ¼Æ */
 
 int top=-1;

 typedef enum{left_paren,right_paren, plus, minus,
	     times, divide, mode, expon, operand} precedence;  /* ©w¸q Àu¥ý¶¶§Ç¤§¸ê®Æ«¬ºA */

 precedence stack[N];


 int ISP[]= {1,5,2,2,3,3,3,4,0};
 int ICP[]= {6,5,2,2,3,3,3,4,0};

/****************************************************************
*	empty¨ç¦¡³¡¤À    ( §PÂ_°ïÅ|¬O§_¤wªÅ )
*****************************************************************/


 int empty(int *top)

 {
    if (*top == -1)
       return (1);         /* true = 1 */
    else
       return (0);       /* false = 0 */
 }  /* end empty */



/****************************************************************
*	push¨ç¦¡³¡¤À    ( stack¡e¡f¡@«Å§i¬°¥þ°ìÅÜ¼Æ )
********************************************************************/

void push(precedence d, int *top )   /*¦¹³B¤§top¬°¤@«ü¼Ð«¬°Ï°ìÅÜ¼Æ*/

{
      if (*top == N-1)
      {
	printf("°ïÅ|º¡¤F\n");			/* ª`·N°ïÅ|¤j¤p */
        exit(1);				/* ¥[¤J¥¢±Ñ¡A°õ¦æµ²§ô */
       }   /* end if */
     else
      {
        (*top)++;          		        /*«ü¼Ð«ü¦V³»ºÝ¡A¼W¶q¼W¥[1*/
        stack[*top]=d;				/*Àx¦s¸ê®Æd ©ó°ïÅ|³»ºÝ¡@*/
       }   /* end else */

}     /* end of push ¨ç¼Æ */

 
/**********************************************************************
*	pop¨ç¦¡³¡¤À    ( stack¡e¡f¡@«Å§i¬°¥þ°ìÅÜ¼Æ )
**********************************************************************/

precedence pop(int *top)          

 {                                     
  if (empty(top))                              /* ª`·NªÅ°ïÅ|±¡§Î*/
     { printf("°ïÅ|ªÅ¤F\n");
       exit(1);					/*§R°£¥¢±Ñ¡A°õ¦æµ²§ô */
      }
  else
	 return(stack[(*top)--]);
 }

/***************************************************************************
*  print_token ¨ç¼Æ
***************************************************************************/

void print_symbol (precedence num)
{
 
   switch (num)
    {             /* ±N¦L¥X¹ïÀ³¤§¹Bºâ¤l²Å¸¹þ */

	case plus  : printf("%c", '+'); break;
	case minus : printf("%c", '-'); break;
	case times : printf("%c", '*'); break; 
	case divide : printf("%c", '/'); break; 
	case mode  : printf("%c", '%'); break;
        case expon: printf("%c", '$'); break;

    }   /* end switch*/

}     /* end  print_symbol */


/***************************************************************************
*  get_token ¨ç¼Æ  (Åª¨ú¦r¤¸Token¡A¨Ã«ö·Ó¨äÀu¥ý¶¶§Ç¤ÀÃþ)
***************************************************************************/

precedence get_token  (char token)
{

   switch (token) {             /* ±NÅª¶i¤§Token ¶q¤Æ¨Ã¤ÀÃþ */
	case '(' :  return left_paren;	/* ¦¹®É '(' µ¥©ó left_paren = 0  */
	case ')' :  return right_paren;	/* ¦¹®É ')' µ¥©ó right_paren = 1  */
	case '+' :  return plus;	/* ¨Ì¦¹Ãþ±À */
	case '-' :  return minus;
	case '*' :  return times;
	case '/' :  return divide;
	case '%' :  return mode;
	case '$' :  return expon;
	default  :  return operand;
     }   /* end switch*/
}     /* end get_token ¨ç¼Æ */


/*********************************************************************
*                  infix_to_postfix¨ç¼Æ  (±N¤¤§Ç¦¡Âà´«¬°­p«á§Ç¹Bºâ¦¡)
*********************************************************************/
 void infix_to_postfix(char expr[])
{
    int	 position=0;           /* ¥Ø«eÅª¨ú¦ì¤¸¤§¦ì¸m */
    char c;                    /* Åª¨ú¤@­Ó¦r¤¸ */
    precedence token;                /* ¤ÀÃþ«á¤§token */

    top = -1;                 /* initialize stack*/
    
  for  (position = 0; (c = expr[position]) != '\0'; position++)
   
             /*  ±NÀx¦s¤¤§Ç¹Bºâ¦¡±qÀY¨ì§À¨Ì§ÇÅª¥X¡@*/
	     /*  ¦r¦ê¤§ '\0'¡@¬°¦r¦ê²×¤î±±¨î«ü¥O¡@*/
    {
       token = get_token(c);             /* Åª¨ú¤@­Ó¦r¤¸ */


       switch (token)
       {
                 
	case operand :             	/* ¦¹®É token ¬°¹Bºâ¤¸  */
	     printf("%c", c);
	     break;
	      
	case right_paren :

	    {
	      while(stack[top] != left_paren) /* ¦Û°ïÅ|³»ºÝ³v¤@¨ú¥X¨Ã¿é¥X¡Aª½¨ì¨ú¥X '(' ¬°¤î */
	     {
	       print_symbol(stack[top]);
	       pop(&top);          /* ²¾°£°ïÅ|³»ºÝ¤§'(', ¤£¶·¦L¥X */
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
*                   ¥Dµ{¦¡³¡¤À  
*****************************************************************/

void main()
 {
   char expr[N];
   int position;


  
       printf("½Ð¿é¤J¤@¤¤§Ç¹Bºâ¦¡\n");
       position = 0;

       while ((expr[position++] = getchar()) != '\n' );
					/*¡@ getchar()¡@¨ç¼Æ©w¸q¦b¡@ctype.h ¤¤ */

       expr[--position] = '\0';                        
       printf ("\n%s %s ", "­ì©l¤¤§Ç¹Bºâ¦¡=        ", expr);
					 /* ¦C¦L­ì©l¤¤§Ç¹Bºâ¦¡¡@*/
  
       printf ("\n«á§Ç¹Bºâ¦¡= ");
       infix_to_postfix(expr);
    
	  printf(" \n");

    
  
} /* end main*/
