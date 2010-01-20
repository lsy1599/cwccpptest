/*---------------------------------------------------------------------------
  Keyboard hook DLL for Borland C++Builder 3.

  作者: 蔡煥麟 (Michael Tsai, easyman@ms2.seeder.net)
  日期: Feb-16-1999

  DESCRIPTION

    這個鍵盤掛勾所做的事情很單純, 當他被啟動時會送出一串字串到目前取得輸入焦
    點的視窗. 你的應用程式只需呼叫 InstallHook, 然後在任何一個視窗中按下
    Ctrl+Alt+A 組合鍵啟動這個掛勾程序, 如果該視窗目前的輸入焦點是可以編輯的控
    制項, 你就會看見有一串字串被丟進來.

    這個範例很簡單, 只有四個函式:

    - InstallHook       安裝掛勾, exported
    - RemoveHook        移除掛勾, exported
    - KeyboardHookProc  此範例的主角, 鍵盤掛勾程序
    - SendDBCSString    送出字串至指定的視窗

  Notes

  - 在實際撰寫你自己的 hook DLL 的時候, 你不應該把 DLL 名稱取為 KbdHook, 這樣
    一來很容易和其他的 DLL 名稱相同.
---------------------------------------------------------------------------*/
#include <SysInit.hpp>
#pragma hdrstop

#include <windows.h>
#include "HookProc.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

HHOOK g_HookHandle=0;

/*-------------------------------------------------
  送入一段字串到指定的視窗
  例如: SendDBCSString(Edit1->Handle, '測試');
  若第一個引數為零, 則送往目前作用中的視窗
  例:
    Edit1->SetFocus();
    SendDBCSString(0, '測試');
-------------------------------------------------*/
void SendDBCSString(HWND hWnd, LPCSTR str)
{
  int i;
  byte ch;

  if (hWnd == 0)
    hWnd = GetFocus();
  if (hWnd == 0)
    return;

  for (i = 0; i < (int)strlen(str); i++)
  {
    ch = byte(str[i]);
    if (IsDBCSLeadByte(ch))
    {
      i++;
      SendMessage(hWnd, WM_IME_CHAR, MAKEWORD(byte(str[i]), ch), 0);
    }
    else
      SendMessage(hWnd, WM_IME_CHAR, WORD(ch), 0);
   }
}

// Hook procedure
LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
  const DWORD KEY_MASK = 0x80000000;

  if (nCode < 0)
    return CallNextHookEx(g_HookHandle, nCode, wParam, lParam);

  // 偵測 Ctrl+Alt+A
  if (((lParam & KEY_MASK) == 0) &&
      (GetKeyState(VK_CONTROL) < 0) && (GetKeyState(VK_MENU) < 0) &&
      (wParam == 0x41))
  {
    SendDBCSString(0, "Hello from a keyboard hook written by Michael Tsai");
    return true;
  }
  return false;
}

bool __stdcall InstallHook()
{
  if (!g_HookHandle)  // 避免重複安裝 hook
  {
    g_HookHandle = SetWindowsHookEx(
      WH_KEYBOARD,
      (HOOKPROC)KeyboardHookProc,
      HInstance,
      0);
  }
  return (g_HookHandle != NULL);
}

bool __stdcall RemoveHook()
{
  bool Result=false;

  if (g_HookHandle)
  {
    UnhookWindowsHookEx(g_HookHandle);
    g_HookHandle = NULL;
    Result = true;
  }
  return Result;
}


