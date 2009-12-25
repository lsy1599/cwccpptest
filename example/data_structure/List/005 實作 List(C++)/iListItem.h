class iListItem
{
public:
  iListItem(int value, iListItem *item_to_link_to = 0);

  void next(iListItem *link);
  iListItem *next();
  int value();
  
private:
  int _value;
  iListItem *_next;
};

inline
int
iListItem::value()
{
  return _value;
}

inline
iListItem *
iListItem::next()
{
  return _next;
}

inline
void
iListItem::next(iListItem *link)
{
  _next = link;
}

inline
iListItem::iListItem(int value, iListItem *item): _value(value)
{
  if (!item)
    _next = 0; // 安插在最後
  else
  {
    _next = item->_next;
    item->_next = this;
  }
}
