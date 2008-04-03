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
typedef struct {

  TLogPalette lpal;
  TPaletteEntry dummy[256];
} LogPal;
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    HDC hdc = GetDC(Panel1->Handle);
    ::Rectangle(hdc, 0, 0, 100, 100);
    TCanvas *tempCanvas = new TCanvas;
    tempCanvas->Handle = hdc;

    TImage* img = new TImage(Panel1);
    img->Width = Panel1->Width;
    img->Height = Panel1->Height;

    TRect destRect = Rect(0,0, Panel1->Width,Panel1->Height);
    TRect sourceRect = destRect;
    img->Canvas->CopyRect(destRect, tempCanvas, sourceRect);

    LogPal SysPal;
    SysPal.lpal.palVersion = 0x300;
    SysPal.lpal.palNumEntries = 256;
    GetSystemPaletteEntries(tempCanvas->Handle,0,256,SysPal.lpal.palPalEntry);
    img->Picture->Bitmap->Palette = CreatePalette((const tagLOGPALETTE *)&SysPal.lpal);
    img->Picture->SaveToFile("c:\\a.bmp");

    delete img;
//    TCanvas* canvas = new TCanvas();

//    delete canvas;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
    HDC hdc = GetDC(Panel1->Handle);
    HDC hdcCompatible = CreateCompatibleDC(hdc);
    Graphics::TCanvas *pTempCanvas = new Graphics::TCanvas();
    Graphics::TBitmap *pTempPic = new Graphics::TBitmap();
    pTempCanvas->Handle = hdcCompatible;
    HBITMAP hbmScreen = CreateCompatibleBitmap(hdc, Panel1->Width, Panel1->Height);
    if ( SelectObject(hdcCompatible, hbmScreen) ){
        ::Rectangle(hdcCompatible, 0, 0, 100, 100);
        ::Rectangle(hdcCompatible, 50, 0, 300, 300);

        pTempPic->Width = Panel1->Width;//(pTempCanvas->ClipRect.right - pTempCanvas->ClipRect.left);
        pTempPic->Height = Panel1->Height;//(pTempCanvas->ClipRect.bottom - pTempCanvas->ClipRect.top);
        TRect rect(0, 0, pTempPic->Width, pTempPic->Height);
        pTempPic->Canvas->CopyRect(
            rect,
            pTempCanvas,
            rect
        );

        pTempPic->SaveToFile("c:\\b.bmp");
    }

}
//---------------------------------------------------------------------------
