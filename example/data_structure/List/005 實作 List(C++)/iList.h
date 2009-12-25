#include <iostream>
#include <vector>
#include "iListItem.h"

using std::vector;
using std::ostream;
using std::cout;
using std::endl;

class iList
{
public:
  iList():_at_front(0),
          _at_end(0),
          _size(0) {}

  void insert(iListItem *item, int value);
  void insert_front(int value);
  void insert_end(int value);

  iListItem *find(int value);


  void remove_all();
  void remove_front();
  int remove(int value);

//  reverse();
//  concat();

  void display(ostream &os = cout);

  int size();

private:
  void bump_up_size();
  void bump_down_size();

  iList(const iList &);
  iList& operator = (const iList &);

  int _size;
  iListItem *_at_front;
  iListItem *_at_end;
};

inline
iListItem *
iList::find(int value)
{
  iListItem *ptr = _at_front;
  while(ptr)
  {
    if (ptr->value() == value) // ­È¤ñ¹ï
    {
      break;
    }
    ptr = ptr->next();
  }

  return ptr;
}

inline
void
iList::insert(iListItem *item, int value)
{
  if(!item)
    insert_front(value);
  else if (item == _at_end)
    insert_end(value);
  else
  {
    bump_up_size();
    new iListItem(value, item);
  }
}

inline
void
iList::insert_front(int value)
{
  iListItem *item = new iListItem(value);
  if(!_at_front)
    _at_front = _at_end = new iListItem(value);
  else
  {
    item->next(_at_front);
    _at_front = item;
  }

  bump_up_size();
}

inline        
void
iList::insert_end(int value)
{
  if(!_at_end)
    _at_end = _at_front = new iListItem(value);
  else
    _at_end = new iListItem(value, _at_end);

  bump_up_size();
}


inline
void
iList::bump_up_size()
{
  ++_size;
}

inline
void
iList::bump_down_size()
{
  --_size;
}

inline
int
iList::size()
{
  return _size;
}
