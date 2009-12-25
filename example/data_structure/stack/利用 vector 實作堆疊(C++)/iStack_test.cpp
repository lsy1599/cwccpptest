/* --------------------------------------------------------------------------------
 * �\��G���|��@ 
 *
 * �ɦW�GiStack_test.cpp
 *
 * �����ɮסG
 *   iStack.cpp
 *   iStack.h
 *
 * �sĶ�G
 *   (BCC) bcc32 iStack_test.cpp iStack.cpp
 *   (VC)  cl -GX iStack_test.cpp iStack.cpp
 *   (G++) g++ -o iStack_test.exe iStack_test.cpp iStack.cpp   
 *
 * �}�o���ҡG
 *   1. Windows 2000 Server
 *   2. Notepad.exe
 *   3. Borland C++ 5.5 Compiler / GNU g++ Compiler / Visual C++ 6.0 Compiler
 *
 * �ѦҸ�ơG
 *   1. Stanley B. Lippman & Josee Lajoie ��, �J��Ķ, �uC++ Primer ���媩�v, �֮p 
 *
 * �]�p�̡GChui-Wen Chiu(Arick) 
 *
 * ��s��x�G
 *   2003/08/31 �إ�
 * --------------------------------------------------------------------------------- */
#include <iostream>
#include "iStack.h"
using std::cout;
using std::endl;

void main()
{
  iStack stack(32);
  stack.display();
  
  for(int ix = 1; ix<51; ++ix)
  {
    if (ix % 2 == 0)
       stack.push(ix);

    if (ix % 5 == 0)
       stack.display(); 

    if (ix %10 == 0)
    {
       int dummy;
       stack.peek( dummy );
       stack.pop( dummy );  
       stack.peek( dummy );
       stack.pop( dummy );  
       stack.display(); 
    }
  }
}