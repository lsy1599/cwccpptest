/*******************************************
 * 功能：堆疊結構
 *
 * 檔案：CStack.h
 *
 * 開發環境：
 *   1. Windows 2000 Professional
 *	 2. Visual C++ 6.0 Professional
 *
 * 參考資料：
 *   [1] 蘇維雅，資料結構使用C語言，松崗圖書
 *
 * 設計者：Chui-Wen Chiu(Arick)
 *
 * 開發日誌：
 *	2004/11/13	建立
 *******************************************/
#include "stdafx.h"

class EStackFull{};
class EStackEmpty{};

template<typename ItemType = int>
class CStack
{
public:
	// Member Method
	CStack(int max_stack_size);	// Create an empty stack whose maximum size is max_stack_size
	~CStack();	
	bool IsFull();						// 
	bool IsEmpty();
	void Add(ItemType item);
	ItemType Delete();

private:
	// Member Data
	int m_max_stack_size;	// 堆疊尺寸
	int m_length;
	ItemType* m_data;
};

template<typename ItemType = int>
CStack<ItemType>::CStack(int max_stack_size)
{
	m_length = 0;
	m_max_stack_size = max_stack_size;
	m_data = new ItemType[m_max_stack_size];
}

template<typename ItemType = int>
CStack<ItemType>::~CStack()
{
	if (m_data != NULL)
	{
		delete[] m_data; 
	}
}
	

template<typename ItemType = int>
bool CStack<ItemType>::IsFull()
{
	if(m_length == m_max_stack_size)
		return true;

	return false;
}

template<typename ItemType = int>
bool CStack<ItemType>::IsEmpty()
{
	int const MIN_STACK_SIZE = 0;
	if(m_length == MIN_STACK_SIZE)
		return true;

	return false;
}

template<typename ItemType = int>
void CStack<ItemType>::Add(ItemType item)
{
	if (IsFull())
		throw EStackFull();

	m_data[m_length++] = item;
}

template<typename ItemType = int>
ItemType CStack<ItemType>::Delete()
{
	if (IsEmpty())
		throw EStackEmpty();

	return m_data[--m_length];
}
