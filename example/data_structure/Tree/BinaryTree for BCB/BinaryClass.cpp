
#include<stdlib.h>
#include<time.h>
#include <vcl\vcl.h>
//#pragma link "WThread"
//#include "WThread.hpp"
void Delay(int iMilliSeconds)
{
  int iStart;

  iStart = GetTickCount();
  while (GetTickCount() - iStart <= iMilliSeconds)
    Application->ProcessMessages();
}

TColor setColor;
typedef struct pos{
 int xIndent,yLevel;
 int sequence;
}position;

class CBinaryNode
{
public:
  int data;
  bool selected;

  struct CBinaryNode *left;
  struct CBinaryNode *right;

  TLabel *NodeDataInformationLabel;

private:
  position posInfo;
public:
  //position posInfo;

  CBinaryNode(int d) {

		      data=d;
		      left=right=0;
		      posInfo.xIndent=posInfo.yLevel=posInfo.sequence=0;
              selected = false;

              NodeDataInformationLabel=new TLabel(NULL);


              NodeDataInformationLabel->Caption="<"+IntToStr(data)+">";
              NodeDataInformationLabel->Color=clYellow;
              NodeDataInformationLabel->Visible=false;

              //    將 NodeDataInformationLabel  顯示在BinaryMainForm 上
             NodeDataInformationLabel->Parent=BinaryMainForm;
  }
  ~CBinaryNode(){//NodeDataInformationLabel->Parent=NULL;
                 delete NodeDataInformationLabel;}

  void SetNodeSequence(int seq){
				posInfo.sequence=seq;
  }
  void SetNodeLevel(int level){
		      posInfo.yLevel=level;
  }




  int GetNodeIdent(void) { return posInfo.xIndent; }

  int GetNodeLevel(void) { return posInfo.yLevel; }

  int GetNodeSequence(void) {return posInfo.sequence; }

  void SetNodeShowStatus(bool selectStatus,int x_step,int y_step)
  {
     selected=selectStatus;
     NodeDataInformationLabel->Visible=selectStatus;
     if(selectStatus)
        BinaryMainForm->DrawTreePadImage->Canvas->Brush->Color=clWhite;
     else
        BinaryMainForm->DrawTreePadImage->Canvas->Brush->Color=clRed;

     BinaryMainForm->DrawTreePadImage->Canvas->Pen->Color=clWhite;
     BinaryMainForm->DrawTreePadImage->Canvas->Brush->Style=bsSolid;
     BinaryMainForm->DrawTreePadImage->Canvas->Ellipse(
                                       GetNodeSequence()*x_step,
                                       GetNodeLevel()*y_step,
                                       GetNodeSequence()*x_step+BALLSIZE,
                                       GetNodeLevel()*y_step+BALLSIZE);
     }
   }; //------------

class CBinaryTree{
public:
  CBinaryNode* root;
 // TLabel *NodeFoundLabel;
  //   TWinThread *TreeThread;

public:
    int T;
//    int TreeThreadThreadProc(TCompoent* Sender,TWinThreadParam &ThreadInfo);
//    int TreeThreadThreadProc(void);


    CBinaryTree():root(0) {iSequence=0;
                 //            TreeThread=new TWinThread;
                         //  NodeFoundLabel=new TLabel(NULL);
                        //   NodeFoundLabel->Color=clGreen;
                        //   NodeFoundLabel->Visible=true;

                   //    將 NodeDataInformationLabel  顯示在 BinaryMainForm上

                        //  NodeFoundLabel->Parent=BinaryMainForm;

                         //  NodeFoundLabel->Parent=this;

                           }
    ~CBinaryTree() { Destroy(root);
                //     delete NodeFoundLabel;
                   }
    void Insert(int data);
    void DrawTree(int width,int height){

                                         DrawTreePadWidth=width,
                                         DrawTreePadHeight=height;

                                         DrawTree();
                                        }

    ////test level/////////////////////////////
     CBinaryNode* Search(int data){ Search(root,data);
                                   }
     CBinaryNode* SearchNodePosition(int x, int y){ SearchNodePosition(root,x,y); }
     int getX_Step(void){ return x_step;}
     int getY_Step(void){ return y_step;}
     void setAllNodeLabel_FALSE(void){//NodeFoundLabel->Visible=false;
                                     BinaryMainForm->VisualSearchLabel->Visible=false;
                                     setAllNodeLabelShow_FALSEorTRUE(root,false);}
     void setAllNodeLabel_TRUE(void){ //NodeFoundLabel->Visible=false;
                                     setAllNodeLabelShow_FALSEorTRUE(root,true);}

    ////  將整棵樹的資料釋放 , 準備重建新資料...
     void Release(void){
                         Destroy(root);
                         root=NULL;
                       }

    ///test//
//    void VisualSearch(int SearchNumber)

    void VisualSearch(int sNumber)
    {
     SearchNumber=sNumber;
   //  TreeThread->SpawnThread(&T);

      char *chMeg;
      String Meg;
      bool Found;
      setAllNodeLabel_FALSE();
      BinaryMainForm->VisualSearchLabel->Visible=true;

      Found=VisualSearch(root,SearchNumber);

      if(Found){
        Meg=" 找到了 "+IntToStr(SearchNumber)+" !!";
      //  BinaryMainForm->VisualSearchLabel->Caption="FOUND!!";
      }
      else{
        Meg=" 抱歉找不到 "+IntToStr(SearchNumber)+" !!";
     //   BinaryMainForm->VisualSearchLabel->Caption=" not FOUND!!";
      }
      chMeg=Meg.c_str();
      BinaryMainForm->VisualSearchLabel->Visible=false;
      Application->MessageBox(chMeg,"搜尋結果!!",MB_OK);



    }

private:
    int DrawTreePadWidth;
    int SearchNumber;
    int DrawTreePadHeight;
    int iSequence;
    int Level;
    int DeepestLevel;
    int amount;
    int x_step;
    int y_step;

    String megString;
    void Insert(CBinaryNode*& rptr,const int data);
    void Destroy(CBinaryNode *p);
    void DrawTree(CBinaryNode *ptr);
    void CaculateNodePosition(void);
    void CaculateNodePosition(CBinaryNode *ptr);
    void DrawTreeNodeConnect(CBinaryNode *ptr);
    void DrawTree(void){
                        // NodeFoundLabel->Visible=true;

                         CaculateNodePosition();
                         DrawTreeNodeConnect(root);
                         DrawTree(root); /*cout<<endl;*/
                          }

    CBinaryNode* Search(CBinaryNode *ptr , int data);
    CBinaryNode* SearchNodePosition(CBinaryNode *ptr , int x ,int y);
    void setAllNodeLabelShow_FALSEorTRUE(CBinaryNode *ptr,bool showStatus);
    bool VisualSearch(CBinaryNode *ptr,int SearchNumber);
    void CurrentVisualSearchNode(CBinaryNode *ptr, bool FOUND);
    void VisualSearchNodeMoveToNextNode(CBinaryNode *src_ptr,CBinaryNode *des_ptr);
    int GetVisualSearchLabelSutiablePosition(int x1,int y1,int x2,int y2,int vX){

                           //   megString="pos="+IntToStr(x1)+","+IntToStr(y1);
                         //     megString+=","+IntToStr(x2)+","+IntToStr(y2)+","+IntToStr(vX);

                             // ShowMessage(megString);

                              //ShowMessage(((int)((float)(y1-y2)/(x1-x2)*(vX-x1)))+y2);

                              return ((int)((float)(y1-y2)/(x1-x2)*(vX-x1))+y1);



                            }

    //test///


public:



};

void CBinaryTree::Insert(int data){

      Insert(root,data);
}

void CBinaryTree::Insert(CBinaryNode*& rptr,const int data)
{
   if(rptr) {
      if(data < rptr->data)
           Insert(rptr->left,data);
      else if(data > rptr->data)
           Insert(rptr->right,data);
   }
   else  rptr=new CBinaryNode(data);
}
void CBinaryTree::Destroy(CBinaryNode *p)
{
  if(p) {
     Destroy(p->left);
     Destroy(p->right);
     delete p;
  }
}
void CBinaryTree::CaculateNodePosition(void)
{
   iSequence=1;
   Level=1;
   DeepestLevel=Level;
   amount=1;
   x_step=0;
   CaculateNodePosition(root);
   x_step=(DrawTreePadWidth-10)/amount;
   y_step=(DrawTreePadHeight-10)/DeepestLevel;

}


void CBinaryTree::CaculateNodePosition(CBinaryNode *ptr)
{
   if(ptr){
      amount++;
      Level++;
      CaculateNodePosition(ptr->left);
      ptr->SetNodeSequence(iSequence++);
      ptr->SetNodeLevel(Level);
      Level++;
      CaculateNodePosition(ptr->right);
   }
   if(Level>DeepestLevel)
      DeepestLevel=Level;

   Level--;
}

void CBinaryTree::DrawTree(CBinaryNode *ptr)
{
      if(ptr){
    	  DrawTree(ptr->left);

         BinaryMainForm->DrawTreePadImage->Canvas->Pen->Color=clWhite;

        if(ptr->selected)
           BinaryMainForm->DrawTreePadImage->Canvas->Brush->Color=clWhite;
        else
           BinaryMainForm->DrawTreePadImage->Canvas->Brush->Color=clRed;


        BinaryMainForm->DrawTreePadImage->Canvas->Brush->Style=bsSolid;

        BinaryMainForm->DrawTreePadImage->Canvas->Ellipse((ptr->GetNodeSequence())*x_step,
                                                         (ptr-> GetNodeLevel())*y_step,
                                                         (ptr->GetNodeSequence())*x_step+BALLSIZE,
                                                         (ptr-> GetNodeLevel())*y_step+BALLSIZE);

        ptr->NodeDataInformationLabel->Left=(ptr->GetNodeSequence())*x_step+2*BALLSIZE;
        ptr->NodeDataInformationLabel->Top=(ptr->GetNodeLevel()*y_step);

	    DrawTree(ptr->right);
      }
}
void CBinaryTree::DrawTreeNodeConnect(CBinaryNode *ptr)
{
    if(ptr){
	 if(ptr->left){
	     BinaryMainForm->DrawTreePadImage->Canvas->Pen->Color=clYellow;
         BinaryMainForm->DrawTreePadImage->Canvas->MoveTo(ptr->GetNodeSequence()*x_step+(BALLSIZE/2),ptr-> GetNodeLevel()*y_step+(BALLSIZE/2));
         BinaryMainForm->DrawTreePadImage->Canvas->LineTo(ptr->left->GetNodeSequence()*x_step+(BALLSIZE/2),ptr->left-> GetNodeLevel()*y_step+(BALLSIZE/2));

	    DrawTreeNodeConnect(ptr->left);

	 }
	 if(ptr->right){
	     BinaryMainForm->DrawTreePadImage->Canvas->Pen->Color=clYellow;
         BinaryMainForm->DrawTreePadImage->Canvas->MoveTo((ptr->GetNodeSequence())*x_step+(BALLSIZE/2),(ptr-> GetNodeLevel())*y_step+(BALLSIZE/2));
         BinaryMainForm->DrawTreePadImage->Canvas->LineTo((ptr->right->GetNodeSequence())*x_step+(BALLSIZE/2),(ptr->right-> GetNodeLevel())*y_step+(BALLSIZE/2));
         DrawTreeNodeConnect(ptr->right);
	 }
    }
}
CBinaryNode* CBinaryTree::Search(CBinaryNode *ptr , int data)
{
        if(ptr){
           if(data == ptr->data) return ptr;
           else if( data > ptr->data) return Search(ptr->right , data);
           else if( data < ptr->data) return Search(ptr->left , data);
        }
        return NULL;
}

CBinaryNode* CBinaryTree::SearchNodePosition(CBinaryNode *ptr , int x ,int y)
{
      if(ptr){
            int NodeX=(ptr->GetNodeSequence())*x_step;
            int NodeY=(ptr-> GetNodeLevel())*y_step;
             if( x >= NodeX && y >= NodeY && x <= (NodeX+BALLSIZE) && y <= (NodeY+BALLSIZE) ){
                return ptr;
             }
             if(x > NodeX)
                return SearchNodePosition(ptr->right,x,y);
             else if(x < NodeX)
                return SearchNodePosition(ptr->left,x,y);
      }
      return NULL;

}
void CBinaryTree::setAllNodeLabelShow_FALSEorTRUE(CBinaryNode *ptr,bool showStatus)
{
   if(ptr)
   {
     setAllNodeLabelShow_FALSEorTRUE(ptr->left,showStatus);
     ptr->NodeDataInformationLabel->Visible=showStatus;
     setAllNodeLabelShow_FALSEorTRUE(ptr->right,showStatus);
   }
}

bool CBinaryTree::VisualSearch(CBinaryNode *ptr , int SearchNumber)
{
         if(ptr){
           if(SearchNumber == ptr->data){
               CurrentVisualSearchNode(ptr,true);

               return true;
           }
           else if( SearchNumber > ptr->data ){

                   CurrentVisualSearchNode(ptr,false);
                  // ShowMessage(" out go");
                   BinaryMainForm->VisualSearchLabel->Caption="to Right";
                   VisualSearchNodeMoveToNextNode(ptr,ptr->right);
                   return VisualSearch(ptr->right , SearchNumber);
                  }
           else if( SearchNumber < ptr->data ){
                   CurrentVisualSearchNode(ptr,false);
                  // ShowMessage(" out go");
                   BinaryMainForm->VisualSearchLabel->Caption="to Left";
                   VisualSearchNodeMoveToNextNode(ptr,ptr->left);
                   return VisualSearch(ptr->left , SearchNumber);
                  }
        }

        return false;
}


void CBinaryTree::CurrentVisualSearchNode(CBinaryNode *ptr, bool FOUND)
{
       if(FOUND)
           BinaryMainForm->DrawTreePadImage->Canvas->Brush->Color=clYellow;
        else
           BinaryMainForm->DrawTreePadImage->Canvas->Brush->Color=clGreen;


        BinaryMainForm->DrawTreePadImage->Canvas->Brush->Style=bsSolid;

        BinaryMainForm->DrawTreePadImage->Canvas->Ellipse((ptr->GetNodeSequence())*x_step,
                                                          (ptr-> GetNodeLevel())*y_step,
                                                          (ptr->GetNodeSequence())*x_step+BALLSIZE,
                                                          (ptr-> GetNodeLevel())*y_step+BALLSIZE);
        ptr->NodeDataInformationLabel->Visible=true;
        ptr->NodeDataInformationLabel->Left=(ptr->GetNodeSequence())*x_step+2*BALLSIZE;
        ptr->NodeDataInformationLabel->Top=(ptr->GetNodeLevel()*y_step);
}
void CBinaryTree::VisualSearchNodeMoveToNextNode(CBinaryNode *src_ptr,CBinaryNode *des_ptr)
{
   int i,n;//,j;//,a=0;
   BinaryMainForm->DrawTreePadImage->Canvas->Pen->Color=clRed;

//  BinaryMainForm->DrawTreePadImage->Canvas->Pen->Color=clRed;

   if(des_ptr){
   if((src_ptr->GetNodeSequence()*x_step+(BALLSIZE/2))<(des_ptr->GetNodeSequence()*x_step+(BALLSIZE/2)))
     {
         n=des_ptr->GetNodeSequence()*x_step+(BALLSIZE/2);
      // for(j=0;j<20;j++)
         for(i=(src_ptr->GetNodeSequence()*x_step+(BALLSIZE/2)); i < n ;i++)
         {

            BinaryMainForm->VisualSearchLabel->Visible=true;
            BinaryMainForm->VisualSearchLabel->Left=i;
            BinaryMainForm->VisualSearchLabel->Top=GetVisualSearchLabelSutiablePosition(
                                                   src_ptr->GetNodeSequence()*x_step+(BALLSIZE/2),
                                                   src_ptr->GetNodeLevel()*y_step+(BALLSIZE/2),
                                                   des_ptr->GetNodeSequence()*x_step+(BALLSIZE/2),
                                                   des_ptr->GetNodeLevel()*y_step+(BALLSIZE/2),
                                                   i);
          Delay(50);

         }


      }
      else
      {
         n=des_ptr->GetNodeSequence()*x_step+(BALLSIZE/2);
        // for(j=0;j<20;j++)
         for(i=(src_ptr->GetNodeSequence()*x_step+(BALLSIZE/2)); i>n ;i--)
         {
            BinaryMainForm->VisualSearchLabel->Visible=true;
            BinaryMainForm->VisualSearchLabel->Left=i;
            BinaryMainForm->VisualSearchLabel->Top=GetVisualSearchLabelSutiablePosition(
                                                   src_ptr->GetNodeSequence()*x_step+(BALLSIZE/2),
                                                   src_ptr->GetNodeLevel()*y_step+(BALLSIZE/2),
                                                   des_ptr->GetNodeSequence()*x_step+(BALLSIZE/2),
                                                   des_ptr->GetNodeLevel()*y_step+(BALLSIZE/2),
                                                   i);
         Delay(50);
        }
        


      }
      BinaryMainForm->DrawTreePadImage->Canvas->MoveTo(src_ptr->GetNodeSequence()*x_step+(BALLSIZE/2),src_ptr->GetNodeLevel()*y_step+(BALLSIZE/2));
      BinaryMainForm->DrawTreePadImage->Canvas->LineTo(des_ptr->GetNodeSequence()*x_step+(BALLSIZE/2),des_ptr->GetNodeLevel()*y_step+(BALLSIZE/2));

   }

   BinaryMainForm->DrawTreePadImage->Canvas->Pen->Color=clWhite;

}

