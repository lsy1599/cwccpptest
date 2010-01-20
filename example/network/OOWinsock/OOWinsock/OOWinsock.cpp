// OOWinsock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CWinsockLib.h"
#include <iostream>

using std::cout;
using std::endl;

int _tmain(int argc, _TCHAR* argv[])
{
	//CWParamList l;
	//l.Add(1, 0, NULL); 
	//l.Add(0, 1, NULL); 
	//cout << l.size(); 
	//l.Remove(0, 1, NULL); 
	//cout << l.size(); 
	//l.Remove(0, 1, NULL); 
	//cout << l.size(); 
	CWinsock ws(1,1);
	return 0;
}

