/*---------------------------------------------------------------------------
  Keyboard hook DLL for Borland C++Builder 3.

  �@��: ������ (Michael Tsai, easyman@ms2.seeder.net)
  ���: Feb-16-1999

  DESCRIPTION

    �o����L���ĩҰ����Ʊ��ܳ��, ��L�Q�Ұʮɷ|�e�X�@��r���ثe���o��J�J
    �I������. �A�����ε{���u�ݩI�s InstallHook, �M��b����@�ӵ��������U
    Ctrl+Alt+A �զX��Ұʳo�ӱ��ĵ{��, �p�G�ӵ����ثe����J�J�I�O�i�H�s�誺��
    �, �A�N�|�ݨ����@��r��Q��i��.

    �o�ӽd�ҫ�²��, �u���|�Ө禡:

    - InstallHook       �w�˱���, exported
    - RemoveHook        ��������, exported
    - KeyboardHookProc  ���d�Ҫ��D��, ��L���ĵ{��
    - SendDBCSString    �e�X�r��ܫ��w������

  Notes

  - �b��ڼ��g�A�ۤv�� hook DLL ���ɭ�, �A�����ӧ� DLL �W�٨��� KbdHook, �o��
    �@�ӫܮe���M��L�� DLL �W�٬ۦP.
---------------------------------------------------------------------------*/
#include <SysInit.hpp>
#pragma hdrstop

#include <windows.h>
#include "HookProc.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

HHOOK g_HookHandle=0;

/*-------------------------------------------------
  �e�J�@�q�r�����w������
  �Ҧp: SendDBCSString(Edit1->Handle, '����');
  �Y�Ĥ@�Ӥ޼Ƭ��s, �h�e���ثe�@�Τ�������
  ��:
    Edit1->SetFocus();
    SendDBCSString(0, '����');
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

  // ���� Ctrl+Alt+A
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
  if (!g_HookHandle)  // �קK���Ʀw�� hook
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


