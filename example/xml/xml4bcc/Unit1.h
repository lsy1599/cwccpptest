//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MSXML2_OCX.h"
#include <OleServer.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
   TmsDOMDocument *xDoc;
   TButton *Button1;
   TDOMDocument60 *DOMDocument601;
   TmsDOMDocument30 *msDOMDocument301;
   void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
