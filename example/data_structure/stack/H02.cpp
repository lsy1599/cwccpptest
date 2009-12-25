#include <iostream.h>
#include <conio.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE  100
typedef enum{lparen,rparen,plus,minus,divide,times,mod,eos,operand}precedence;
precedence stack[MAX_STACK_SIZE];
char *op="()+-/*%";
char expr[MAX_EXPR_SIZE];
static int isp[]={0,19,12,12,13,13,13,0};//堆疊內優先權
//                (  ) +   -  /  *  % eos
static int icp[]={20,19,12,12,13,13,13,0};//輸入優先權

int addq(int *top,precedence token)
{
  if (*top>=MAX_STACK_SIZE-1)
  {
    cout<<"Stack Overflow";
    return -1;
  }
  stack[++(*top)]=token;
  return 0;
}

precedence deleteq(int *top)
{
  if (*top==-1)
    return eos;
  return stack[(*top)--];
}

//precedence get_token(char *sym,int *n)
precedence get_token(char sym)
{
//  char t=sym[(*n)++];
  switch (sym)
  {
    case '(': return lparen;
    case ')': return rparen;
    case '+': return plus;
    case '-': return minus;
    case '/': return divide;
    case '*': return times;
    case '%': return mod;
    case '\0': return eos;
    default : return operand;
  }
}

void main()
{
  char *sym="1*2+3*4\0";
//  char *sym="1+2*3\0";
  char c;
  precedence token;
  int n=0,top=0,pos=0;
  stack[0]=eos;
//  for(token=get_token(sym,&n);token!=eos;token=get_token(sym,&n))
  while((c=sym[pos])!='\0')
  {
    token=get_token(c);
    if (token==operand) // 運算元
      cout<<c;
    else if (token== rparen) // 右括號
    {
      while (stack[top]!=lparen)
	cout<<deleteq(&top);
      delete(&top);
    }
    else // 運算子
    {
      while (isp[stack[top]]>=icp[token])
	cout<<deleteq(&top);
      addq(&top,token);
    }
    pos++;
  }
  while ((token=deleteq(&top))!=eos)
    cout<<op[token];
  cout<<endl;

  getch();
}