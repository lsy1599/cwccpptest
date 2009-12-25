#include "iList.h"

void
iList::remove_all()
{
  while(_at_front)
    remove_front();

  _at_front = _at_end = 0;
  _size = 0;
}

void
iList::remove_front()
{
   if(_at_front)
   {
     iListItem *ptr=_at_front;
     _at_front = _at_front->next(); // 將下一個的指標當作第一個項目

     bump_down_size();              // List 長度減 1
     delete ptr;                    // 除記憶體中移除第一個項目
   }
}

int
iList::remove(int value)
{
   iListItem *plist = _at_front;
   int elem_cnt =0;
   // 移除前端元素
   while(plist && plist->value() == value)
   {
     plist = plist->next();
     remove_front();
     ++elem_cnt;
   }

   // 檢驗是否已到尾端
   if(!plist)
     return elem_cnt;

   iListItem *prev = plist;
   plist = plist->next();

   while(plist)
   {
     if(plist->value() == value)
     {
       prev->next(plist->next());
       delete plist;
       ++elem_cnt;
       bump_down_size();
       plist = prev->next();
       if(!plist)
       {
         _at_end = prev;
         return elem_cnt;
       }
     }
     else
     {
       prev = plist;
       plist = plist->next();
     }
   }
   return elem_cnt;
}



void
iList::display(ostream &os)
{
  os<<endl<<"( "<< _size << " )< ";
  iListItem *iter = _at_front;
  while(iter)
  {
    os << iter->value() << " ";
    iter = iter->next();
  }
  os << ")"<<endl;
}
