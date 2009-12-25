//---------------------------------------------------------------------------
#ifndef BiMUnitH
#define BiMUnitH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Menus.hpp>

//---------------------------------------------------------------------------
class TBinaryMainForm : public TForm
{
__published:	// IDE-managed Components
	TButton *InsertButton;
	TButton *SearchButton;
	TImage *DrawTreePadImage;
	TBevel *Bevel1;
	TComboBox *ControlSelectionComboBox;
	TEdit *InputEdit;
	TComboBox *SelectANewTreeComboBox;
	TPopupMenu *PopupMenu1;
	TMenuItem *BallSizeisBig1;
	TMenuItem *BallSizeisSmall1;
	TMenuItem *ShowAllNodeInfo1;
	TMenuItem *N1;
	TMenuItem *Noball1;
	TLabel *VisualSearchLabel;
	void __fastcall FormResize(TObject *Sender);
	
	
	
	
	
	void __fastcall FormCreate(TObject *Sender);
	
	void __fastcall DrawTreePadImageMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);


	
	
	
	void __fastcall InsertButtonClick(TObject *Sender);
	
	
	void __fastcall ControlSelectionComboBoxChange(TObject *Sender);
	
	
	void __fastcall SearchButtonClick(TObject *Sender);
	
	
	void __fastcall InputEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall InputEditEnter(TObject *Sender);
	void __fastcall SelectANewTreeComboBoxChange(TObject *Sender);
	void __fastcall BallSizeisBig1Click(TObject *Sender);
	void __fastcall BallSizeisSmall1Click(TObject *Sender);
	void __fastcall ShowAllNodeInfo1Click(TObject *Sender);

	void __fastcall Noball1Click(TObject *Sender);
private:	// User declarations


public:		// User declarations
	__fastcall TBinaryMainForm(TComponent* Owner);
};
//---------Initial By Myself-------------------------------------------------
/*typedef struct POSITION_INFORMATION{
    int x;
    int y;
    int data;
    bool selected;
}posNode;
  */

//---------------------------------------------------------------------------
extern TBinaryMainForm *BinaryMainForm;
//---------------------------------------------------------------------------
#endif
