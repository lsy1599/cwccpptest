//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

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
void __fastcall TForm1::Button1Click(TObject *Sender)
{
   ::MoveWindow(this->Handle,0,0,this->Width,this->Height,CheckBox1->Checked);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
   ::MoveWindow(this->Handle,0,Screen->Height-this->Height,this->Width,this->Height,CheckBox1->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
   ::MoveWindow(this->Handle,(Screen->Width-this->Width)/2,0,this->Width,this->Height,CheckBox1->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
   ::MoveWindow(this->Handle,Screen->Width-this->Width,0,this->Width,this->Height,CheckBox1->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
   ::MoveWindow(this->Handle,0,(Screen->Height-this->Height)/2,this->Width,this->Height,CheckBox1->Checked);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button9Click(TObject *Sender)
{
   ::MoveWindow(this->Handle,Screen->Width-this->Width,(Screen->Height-this->Height)/2,this->Width,this->Height,CheckBox1->Checked);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button8Click(TObject *Sender)
{
   ::MoveWindow(this->Handle,(Screen->Width-this->Width)/2,(Screen->Height-this->Height)/2,this->Width,this->Height,CheckBox1->Checked);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
   ::MoveWindow(this->Handle,(Screen->Width-this->Width)/2,Screen->Height-this->Height,this->Width,this->Height,CheckBox1->Checked);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button6Click(TObject *Sender)
{
   ::MoveWindow(this->Handle,Screen->Width-this->Width,Screen->Height-this->Height,this->Width,this->Height,CheckBox1->Checked);

}
//---------------------------------------------------------------------------
