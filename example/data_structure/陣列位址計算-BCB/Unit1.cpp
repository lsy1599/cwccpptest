/* ----------------------------------------------
   作者：Arick
   功能：陣列位址計算(忽略資料型態的大小)
   編譯器：Borland C++ Builder 5.0
   日期：2001/10/29
---------------------------------------------- */
#include <iostream>
#include <conio>
using namespace std;
#pragma hdrstop
//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
   int range=0;
   cout<<"------ 陣列位址計算 ------\n";
   cout<<"輸入陣列維度>>";
   cin>>range;
   if (range<1)
   {
      cout<<"維度輸入錯誤\n";
      exit(1);
   }
   int *r=new int[range];
   cout<<"輸入各陣列維度上邊界\n";
   for (int i=0;i<range;i++)
   {
      cout<<"陣列上標 r["<<i<<"]=";
      cin>>r[i];
   }

   int *n=new int[range];
   cout<<"輸入欲查詢索引的陣列位址\n";
   for (int i=0;i<range;i++)
   {
      for(;;)
      {
         cout<<"陣列索引 n["<<i<<"]=";
         cin>>n[i];
         if (n[i]>r[i]||n[i]<0)
            cout<<"索引超出維度範圍，請重新輸入\n";
         else
            break;
      }
   }


   int offset=0;
   for(int j=0;j<range;j++)
      offset=r[j]*offset + n[j];

   cout<<"位址 = base address + "<<offset<<endl;

   delete []r;
   delete []n;
//   getch();
   return 0;
}
//---------------------------------------------------------------------------
