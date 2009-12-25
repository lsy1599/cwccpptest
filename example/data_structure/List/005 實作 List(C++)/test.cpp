/* --------------------------------------------------------------------------------
 * �\��GList ��@
 *
 * �ɦW�GiList_test.cpp
 *
 * �����ɮסG
 *   iList.cpp, iList.h
 *   iListItem.cpp, iListItem.h
 *
 * �sĶ�G
 *   (BCC) bcc32 test.cpp iList.cpp iListITem.cpp
 *   (VC)  cl -GX test.cpp iList.cpp iListItem.cpp
 *   (G++) g++ -o test.exe test.cpp iList.cpp iListItem.cpp
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
 *   2003/09/02 �إ�
 * --------------------------------------------------------------------------------- */
#include <iostream>
#include "iList.h"
using std::cout;
using std::endl;

void main()
{
  iList myList;
  for(int ix=0; ix<10; ++ix)
  {
     myList.insert_front(ix);
     myList.insert_end(ix);
  }
  cout<<"ok: after insert_front() and insert_end()"<<endl;
  myList.display();

  iListItem *it = myList.find(8);
  cout<<endl
      <<"Searching for the value 8: found it?"
      <<(it ? "yes!" : " no!")
      <<endl;

  myList.insert(it, 1024);
  cout<<endl
      <<"Inserting element 1024 following the value 8\n";
  myList.display();
}
