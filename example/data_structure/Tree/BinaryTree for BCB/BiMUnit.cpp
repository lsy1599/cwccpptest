//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
int BALLSIZE=8;
int SearchNumber=0;
bool COMPEL=false;                           
#include "BiMUnit.h"
#include "BinaryClass.cpp"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TBinaryMainForm *BinaryMainForm;

CBinaryTree MyTree;
CBinaryNode *selectedTreeNode;
CBinaryNode *LastselectedTreeNode;

//int data[14]={23,45,13,78,1,22,2,66,12,76,88,19,34,54};
int FTreeData[7]={100,50,150,180,130,25,75};
int LSkewTreeData[5]={75,85,95,125,150};
int RSkewTreeData[5]={75,60,50,30,15};


int data[11]={23,45,13,78,1,22,2,66,12,76,55};





//---------------------------------------------------------------------------
__fastcall TBinaryMainForm::TBinaryMainForm(TComponent* Owner)
	: TForm(Owner)
{
      BinaryMainForm->Width=560;
      BinaryMainForm->Height=380;

      DrawTreePadImage->Width=BinaryMainForm->Width-24;
      DrawTreePadImage->Height=BinaryMainForm->Height-70;

      Bevel1->Width=DrawTreePadImage->Width+6;
      Bevel1->Height=DrawTreePadImage->Height+6;
      ControlSelectionComboBox->ItemIndex=0;
      SelectANewTreeComboBox->ItemIndex=0;



}
//---------------------------------------------------------------------------
void __fastcall TBinaryMainForm::FormResize(TObject *Sender)
{

   int ButtonWidth=SearchButton->Width+16;

   if(BinaryMainForm->Width<420)
      BinaryMainForm->Width=420;

  // if(BinaryMainForm->Height<380)
      BinaryMainForm->Height=380;

   if(BinaryMainForm->Width>560)
      BinaryMainForm->Width=560;

   //if(BinaryMainForm->Height>420)
  //    BinaryMainForm->Height=420;

    DrawTreePadImage->Width=BinaryMainForm->Width-24;
    DrawTreePadImage->Height=BinaryMainForm->Height-70;

    Bevel1->Width=DrawTreePadImage->Width+8;
    Bevel1->Height=DrawTreePadImage->Height+6;

   InputEdit->Top=ControlSelectionComboBox->Top=SearchButton->Top=SelectANewTreeComboBox->Top=InsertButton->Top=DrawTreePadImage->Height+DrawTreePadImage->Top+6;

   SelectANewTreeComboBox->Left=BinaryMainForm->Width-ButtonWidth;
   SearchButton->Left=BinaryMainForm->Width-ButtonWidth*2;
   InsertButton->Left=BinaryMainForm->Width-ButtonWidth*3;
   ControlSelectionComboBox->Left=BinaryMainForm->Width-ButtonWidth*5;
   InputEdit->Left=12;


   DrawTreePadImage->Canvas->Pen->Color=clWhite;
   DrawTreePadImage->Canvas->Brush->Color = clBlack;
   DrawTreePadImage->Canvas->Rectangle(0,0,DrawTreePadImage->Width,DrawTreePadImage->Height);
        MyTree.DrawTree(DrawTreePadImage->Width,
                        DrawTreePadImage->Height);
}
//---------------------------------------------------------------------------
void __fastcall TBinaryMainForm::FormCreate(TObject *Sender)
{


      for(int i = 0 ;i<11 ;i++)
      {
        MyTree.Insert(data[i]);
      }
}
//---------------------------------------------------------------------------
void __fastcall TBinaryMainForm::DrawTreePadImageMouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(COMPEL){
        DrawTreePadImage->Canvas->Pen->Color=clWhite;
        DrawTreePadImage->Canvas->Brush->Color = clBlack;
        DrawTreePadImage->Canvas->Rectangle(0,0,DrawTreePadImage->Width,DrawTreePadImage->Height);
        MyTree.DrawTree(DrawTreePadImage->Width,
                        DrawTreePadImage->Height);
         MyTree.setAllNodeLabel_FALSE();
      COMPEL=false;
      VisualSearchLabel->Visible=false;
    }

    if(Button==mbLeft)
    {
       selectedTreeNode=MyTree.SearchNodePosition(X,Y);

       if(selectedTreeNode)
       {
          if(LastselectedTreeNode)
                   LastselectedTreeNode->SetNodeShowStatus(false,
                                                    MyTree.getX_Step(),MyTree.getY_Step());

           ///////  將被選的Node改被顏色
           selectedTreeNode->SetNodeShowStatus(true,
                             MyTree.getX_Step(),MyTree.getY_Step());

           LastselectedTreeNode=selectedTreeNode;
       }
      else
      {
         if(LastselectedTreeNode)
             LastselectedTreeNode->SetNodeShowStatus(false,
                                   MyTree.getX_Step(),MyTree.getY_Step());
         LastselectedTreeNode=NULL;

      }
     }//if(Button==mbLeft)
}



//---------------------------------------------------------------------------
void __fastcall TBinaryMainForm::InsertButtonClick(TObject *Sender)
{
    MyTree.Insert(random(150));

    MyTree.setAllNodeLabel_FALSE();
    DrawTreePadImage->Canvas->Pen->Color=clWhite;
    DrawTreePadImage->Canvas->Brush->Color = clBlack;
    DrawTreePadImage->Canvas->Rectangle(0,0,DrawTreePadImage->Width,DrawTreePadImage->Height);
    MyTree.DrawTree(DrawTreePadImage->Width,
                    DrawTreePadImage->Height);




}
//---------------------------------------------------------------------------
void __fastcall TBinaryMainForm::ControlSelectionComboBoxChange(TObject *Sender)
{
   DrawTreePadImage->Canvas->Pen->Color=clWhite;
   DrawTreePadImage->Canvas->Brush->Color = clBlack;
   switch(ControlSelectionComboBox->ItemIndex)
   {
      case 1:
           BALLSIZE=8;
           DrawTreePadImage->Canvas->Rectangle(0,0,DrawTreePadImage->Width,DrawTreePadImage->Height);
           MyTree.DrawTree(DrawTreePadImage->Width,
                    DrawTreePadImage->Height);
            BallSizeisBig1->Checked=true;
            BallSizeisSmall1->Checked=false;
            Noball1->Checked=false;
      break;
      case 2:
           BALLSIZE=6;
           DrawTreePadImage->Canvas->Rectangle(0,0,DrawTreePadImage->Width,DrawTreePadImage->Height);
           MyTree.DrawTree(DrawTreePadImage->Width,
                    DrawTreePadImage->Height);
            BallSizeisBig1->Checked=false;
            BallSizeisSmall1->Checked=true;
            Noball1->Checked=false;

      break;
      case 3:
           BALLSIZE=2;
           DrawTreePadImage->Canvas->Rectangle(0,0,DrawTreePadImage->Width,DrawTreePadImage->Height);
           MyTree.DrawTree(DrawTreePadImage->Width,
                    DrawTreePadImage->Height);
            BallSizeisBig1->Checked=false;
            BallSizeisSmall1->Checked=false;
            Noball1->Checked=true;

      break;
      case 4:
           MyTree.setAllNodeLabel_TRUE();
           COMPEL=1;
      break;
      case 5:
           MyTree.setAllNodeLabel_FALSE();
      break;
   }

   ControlSelectionComboBox->ItemIndex=0;



}
//---------------------------------------------------------------------------
void __fastcall TBinaryMainForm::SearchButtonClick(TObject *Sender)
{
   InputEdit->Visible=true;
   SearchButton->Enabled=false;
   SelectANewTreeComboBox->Enabled=false;
   InsertButton->Enabled=false;
   ControlSelectionComboBox->Enabled=false;

   InputEdit->Left=12;
   VisualSearchLabel->Visible=false;

}

void __fastcall TBinaryMainForm::InputEditKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift)
{

     if(Key==VK_RETURN){
        if((SearchNumber=atoi(InputEdit->Text.c_str()))!=0){

              MyTree.DrawTree(DrawTreePadImage->Width,
                              DrawTreePadImage->Height);
              InputEdit->Enabled=false;
              MyTree.VisualSearch(SearchNumber);
              InputEdit->Visible=false;
              InputEdit->Text="Input Num...";
              COMPEL=true;
              SearchButton->Enabled=true;
              SelectANewTreeComboBox->Enabled=true;
              InsertButton->Enabled=true;
              InputEdit->Enabled=true;
              ControlSelectionComboBox->Enabled=true;

              // ShowMessage(SearchNumber);
        }
     }




}
//---------------------------------------------------------------------------
void __fastcall TBinaryMainForm::InputEditEnter(TObject *Sender)
{
   InputEdit->Text="";
   SearchNumber=0;
}
//---------------------------------------------------------------------------
void __fastcall TBinaryMainForm::SelectANewTreeComboBoxChange(TObject *Sender)
{

    int i,j;
if(SelectANewTreeComboBox->ItemIndex!=0){
    MyTree.Release();
    DrawTreePadImage->Canvas->Pen->Color=clWhite;
    DrawTreePadImage->Canvas->Brush->Color = clBlack;
    DrawTreePadImage->Canvas->Rectangle(0,0,DrawTreePadImage->Width,DrawTreePadImage->Height);

    LastselectedTreeNode=NULL;

   randomize();
   switch(SelectANewTreeComboBox->ItemIndex)
   {
      case 1:
           MyTree.Insert(random(100)+1);
      break;
      case 2:
         for(i=0;i<5;i++)
              MyTree.Insert(RSkewTreeData[i]);
      break;
      case 3:
         for(i=0;i<5;i++)
              MyTree.Insert(LSkewTreeData[i]);

      break;
      case 4:
         for(i=0;i<7;i++)
              MyTree.Insert(FTreeData[i]);
      break;
      case 5:
         j=random(10)+1;
         for(i=0;i<j;i++)
              MyTree.Insert(random(200)+1);

      break;
   }

   SelectANewTreeComboBox->ItemIndex=0;
      MyTree.DrawTree(DrawTreePadImage->Width,
                    DrawTreePadImage->Height);

  }
}
//---------------------------------------------------------------------------
void __fastcall TBinaryMainForm::BallSizeisBig1Click(TObject *Sender)
{
     BallSizeisBig1->Checked=true;
    DrawTreePadImage->Canvas->Pen->Color=clWhite;
    DrawTreePadImage->Canvas->Brush->Color = clBlack;
    BALLSIZE=8;
    DrawTreePadImage->Canvas->Rectangle(0,0,DrawTreePadImage->Width,DrawTreePadImage->Height);
    MyTree.DrawTree(DrawTreePadImage->Width,
                    DrawTreePadImage->Height);
    BallSizeisSmall1->Checked=false;
    Noball1->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TBinaryMainForm::BallSizeisSmall1Click(TObject *Sender)
{
    BallSizeisSmall1->Checked=true;
    DrawTreePadImage->Canvas->Pen->Color=clWhite;
    DrawTreePadImage->Canvas->Brush->Color = clBlack;
    BALLSIZE=6;
    DrawTreePadImage->Canvas->Rectangle(0,0,DrawTreePadImage->Width,DrawTreePadImage->Height);
    MyTree.DrawTree(DrawTreePadImage->Width,
                    DrawTreePadImage->Height);
     BallSizeisBig1->Checked=false;
     Noball1->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TBinaryMainForm::ShowAllNodeInfo1Click(TObject *Sender)
{
    MyTree.setAllNodeLabel_TRUE();
           COMPEL=true;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TBinaryMainForm::Noball1Click(TObject *Sender)
{
    Noball1->Checked=true;
    DrawTreePadImage->Canvas->Pen->Color=clWhite;
    DrawTreePadImage->Canvas->Brush->Color = clBlack;
    BALLSIZE=2;
    DrawTreePadImage->Canvas->Rectangle(0,0,DrawTreePadImage->Width,DrawTreePadImage->Height);
    MyTree.DrawTree(DrawTreePadImage->Width,
                    DrawTreePadImage->Height);
     BallSizeisBig1->Checked=false;

     BallSizeisSmall1->Checked=false;
}
//---------------------------------------------------------------------------


