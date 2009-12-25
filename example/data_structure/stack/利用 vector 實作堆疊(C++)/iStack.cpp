#include "iStack.h"

bool iStack::pop(int &value)
{
  if (empty())
  {
    return false;
  } 

  value = _stack[--_top];
  //--_top;
  //value = _stack[_top];
  cout<< "iStack::pop(): "<< value <<endl;
  return true;
}

bool iStack::peek(int &value)
{
  if (empty())
  {
    return false;
  } 

  value = _stack[_top-1];
  cout<< "iStack::peek(): "<< value <<endl;
  return true;
}

bool iStack::push(int &value)
{
  cout<< "iStack::push( "<< value << " )" <<endl;

  if (full())
  {
    return false;
  }

  _stack[_top++]=value;
  //_stack[_top]=value;
  //_top++;

  return true;
}

void iStack::display()
{
  if (!size())
  {
    cout<< "( 0 ) " << endl;
    return;
  } 
  cout<< "( " << size() << " ) ( bot: ";
  for(int ix = 0; ix< _top; ++ix)
    cout<< _stack[ix] << " ";
  cout<< ":top )" <<endl;
}

inline bool iStack::full()
{
  return (_top >= _stack.size()); 
}

inline bool iStack::empty()
{
  return (_top == 0);
}

inline int iStack::size()
{
  return _top;
}