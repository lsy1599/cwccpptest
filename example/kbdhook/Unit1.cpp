// ด๚ธี KbdHook.DLL
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "HookProc.h"
#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnInstallHookClick(TObject *Sender)
{
  if (InstallHook())
    ShowMessage("Keyboard hook installed.\nPress Ctrl+Alt+A do enable hook");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnRemoveHookClick(TObject *Sender)
{
  if (RemoveHook())
    ShowMessage("Keyboard removed.");
}
//---------------------------------------------------------------------------
