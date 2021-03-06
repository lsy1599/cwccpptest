// 合併排序
#include <iostream.h>

template <class Type>
class merge {
	private:
		Type data1[10];
		Type data2[10];
		Type data3[20];
	public:
		void merge_sort(void);
		void select_sort(Type data[], int size);
		void access(int size1, int size2);
};

template <class Type>
void merge<Type>::merge_sort(void)
{
	int size1 = 0, size2 = 0, i;
	// 要求輸入兩個數列作合併
	cout << "\nPlease enter data 1 to sort ( enter 0 when end ):\n";
	cout << "Number : ";
	do
	{
		cin >> data1[size1];
	}  while(data1[size1++] != 0);
	cout << "Please enter data 2 to sort ( enter 0 when end ):\n";
	cout << "Number : ";
	do
	{
		cin >> data2[size2];
	}  while(data2[size2++] != 0);
	// 先使用選擇排序將兩數列排序，再作合併
	select_sort(data1, --size1);
	select_sort(data2, --size2);
	for(i = 0; i < 60; i++) cout << "-";
	cout << "\nData 1 : ";
	for(i = 0; i < size1; i++)
		cout << data1[i] << "  ";
	cout << "\n";
	cout << "Data 2 : ";
	for(i = 0; i < size2; i++)
		cout << data2[i] << "  ";
	cout << "\n";
	for(i = 0; i < 60; i++) cout << "-";
	cout << "\n";
	access(size1, size2);
	for(i = 0; i < 60; i++) cout << "-";
	cout << "\nSorting: ";
	for(i = 0; i < size1+size2; i++)
		cout << data3[i] << "  ";
}

template <class Type>
void merge<Type>::select_sort(Type data[], int size)
{
	int base, compare, min;
	Type temp;
	for(base = 0; base < size-1; base++)
	{
		min = base;
		for(compare = base+1; compare < size; compare++)
			if(data[compare] < data[min])
				min = compare;
		temp = data[min];
		data[min] = data[base];
		data[base] = temp;
	}
}

template <class Type>
void merge<Type>::access(int size1, int size2)
{
	int arg1, arg2, arg3, i;
	data1[size1] = 32767;
	data2[size2] = 32767;
	arg1 = 0;
	arg2 = 0;
	for(arg3 = 0; arg3 < size1+size2; arg3++)
	{
		if(data1[arg1] < data2[arg2]) // 比較兩數列，資料小的先存於合併後的數列
		{
			data3[arg3] = data1[arg1];
			arg1++;
		}
		else
		{
			data3[arg3] = data2[arg2];
			arg2++;
		}
		cout << "Access : ";
		for(i = 0; i < arg3+1; i++)
			cout << data3[i] << "  ";
		cout << "\n";
	}
}

void main(void)
{
	merge<int> obj;
	obj.merge_sort();
}