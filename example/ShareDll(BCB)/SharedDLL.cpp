#include <vcl.h>
#include <windows.h>
#pragma hdrstop
#include "SharedDLL.h"
USEUNIT("SharedData.cpp");
USEDEF("Shared.def");
//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
   return 1;
}
//---------------------------------------------------------------------------
extern int data;   
//---------------------------------------------------------------------------
/**
 * �]�w�@���ܼ�
 *
 * @param   x
 */
void DLL_EXPORT SetData(int x)
{
  data = x;
}
//---------------------------------------------------------------------------
/**
 * ���X�@���ܼ�
 *
 * @return
 */
int DLL_EXPORT GetData(void)
{
  return data;
}
