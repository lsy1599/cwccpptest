// MyStack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "CStack.h"

void UnderflowTest()
{
	try
	{
		CStack<int> s1(10);
	
		s1.Add(3);
		s1.Add(5);
		s1.Add(7);

		std::cout<< s1.Delete() << std::endl; // 7
		std::cout<< s1.Delete() << std::endl; // 5
		std::cout<< s1.Delete() << std::endl; // 3
		std::cout<< s1.Delete() << std::endl; // Stack is Empty!!
	}
	catch(EStackEmpty& )
	{
		std::cout << "Stack is Empty!!" << std::endl;
	}
	catch(EStackFull& )
	{
		std::cout << "Stack is Full!!" << std::endl;
	}
}

void OverflowTest()
{
	try
	{
		CStack<int> s1(2);
		std::cout << "Stack size is 2" << std::endl;
		std::cout << "push element #1" << std::endl;
		s1.Add(3);	// Ok
		std::cout << "push element #2" << std::endl;
		s1.Add(5);	// OK
		std::cout << "push element #3" << std::endl;
		s1.Add(7);	// Error
	}
	catch(EStackEmpty& )
	{
		std::cout << "Stack is Empty!!" << std::endl;
	}
	catch(EStackFull& )
	{
		std::cout << "Stack is Full!!" << std::endl;
	}
}
int main(int argc, char* argv[])
{
	OverflowTest();
	UnderflowTest();
	return 0;
}

