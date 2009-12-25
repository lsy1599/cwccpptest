/* --------------------------------------------------------------------------------
 * 功能：堆疊實作 
 *
 * 檔名：iStack_test.cpp
 *
 * 相關檔案：
 *   iStack.cpp
 *   iStack.h
 *
 * 編譯：
 *   (BCC) bcc32 iStack_test.cpp iStack.cpp
 *   (VC)  cl -GX iStack_test.cpp iStack.cpp
 *   (G++) g++ -o iStack_test.exe iStack_test.cpp iStack.cpp   
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
 *   2003/08/31 建立
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