/* ----------------------------------------------
   �@�̡GArick
   �\��G�}�C��}�p��(������ƫ��A���j�p)
   �sĶ���GBorland C++ Builder 5.0
   ����G2001/10/29
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
   cout<<"------ �}�C��}�p�� ------\n";
   cout<<"��J�}�C����>>";
   cin>>range;
   if (range<1)
   {
      cout<<"���׿�J���~\n";
      exit(1);
   }
   int *r=new int[range];
   cout<<"��J�U�}�C���פW���\n";
   for (int i=0;i<range;i++)
   {
      cout<<"�}�C�W�� r["<<i<<"]=";
      cin>>r[i];
   }

   int *n=new int[range];
   cout<<"��J���d�߯��ު��}�C��}\n";
   for (int i=0;i<range;i++)
   {
      for(;;)
      {
         cout<<"�}�C���� n["<<i<<"]=";
         cin>>n[i];
         if (n[i]>r[i]||n[i]<0)
            cout<<"���޶W�X���׽d��A�Э��s��J\n";
         else
            break;
      }
   }


   int offset=0;
   for(int j=0;j<range;j++)
      offset=r[j]*offset + n[j];

   cout<<"��} = base address + "<<offset<<endl;

   delete []r;
   delete []n;
//   getch();
   return 0;
}
//---------------------------------------------------------------------------
