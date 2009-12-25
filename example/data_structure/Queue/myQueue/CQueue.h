class EQueueFull{};
class EQueueEmpty{};

template <typename ItemType>
class CQueue
{
public:
	CQueue(int max_queue_size);
	~CQueue();

	bool IsFull();
	bool IsEmpty();

	void Add(ItemType item);
	ItemType Delete();

private:
	ItemType*	m_data;
	int			m_max_queue_size;
	ItemType*	front;
	ItemType*	rear;
};

template <typename ItemType>
CQueue<ItemType>::CQueue(int max_queue_size)
{
	front = -1;
	rear = -1;
	m_max_queue_size = max_queue_size;
	m_data = new ItemType[max_queue_size];
}

template <typename ItemType>
CQueue<ItemType>::~CQueue()
{
	if (m_data != NULL)
		delete[] m_data;
}

template <typename ItemType>
bool CQueue<ItemType>::IsFull()
{
	if (rear == max_queue_size)
		return true;

	return false;
}

template <typename ItemType>
bool CQueue<ItemType>::IsEmpty()
{
	if (front == rear)
		return true;

	return false;
}

template <typename ItemType>
void CQueue<ItemType>::Add(ItemType item)
{
	if (IsFull())
		throw EQueueFull();
	
	m_data[++rear] = item;
}

template <typename ItemType>
ItemType CQueue<ItemType>::Delete()
{
	if (IsEmpty())
		throw EQueueEmpty();
	
	return m_data[++front];
}
