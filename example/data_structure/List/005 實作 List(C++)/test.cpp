/* --------------------------------------------------------------------------------
 * 功能：List 實作
 *
 * 檔名：iList_test.cpp
 *
 * 相關檔案：
 *   iList.cpp, iList.h
 *   iListItem.cpp, iListItem.h
 *
 * 編譯：
 *   (BCC) bcc32 test.cpp iList.cpp iListITem.cpp
 *   (VC)  cl -GX test.cpp iList.cpp iListItem.cpp
 *   (G++) g++ -o test.exe test.cpp iList.cpp iListItem.cpp
 *
 * 開發環境：
 *   1. Windows 2000 Server
 *   2. Notepad.exe
 *   3. Borland C++ 5.5 Compiler / GNU g++ Compiler / Visual C++ 6.0 Compiler
 *
 * 參考資料：
 *   1. Stanley B. Lippman & Josee Lajoie 著, 侯捷譯, 「C++ Primer 中文版」, 碁峰 
 *
 * 設計者：Chui-Wen Chiu(Arick) 
 *
 * 更新日誌：
 *   2003/09/02 建立
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
