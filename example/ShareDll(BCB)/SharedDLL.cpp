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
 * 設定共享變數
 *
 * @param   x
 */
void DLL_EXPORT SetData(int x)
{
  data = x;
}
//---------------------------------------------------------------------------
/**
 * 取出共享變數
 *
 * @return
 */
int DLL_EXPORT GetData(void)
{
  return data;
}
