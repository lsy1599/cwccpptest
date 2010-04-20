// com_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#import "C:\Documents and Settings\Administrator.MYCHAT-1A793BE7\My Documents\Visual Studio 2005\Projects\com_test\com_test\RandomEngine.dll" raw_interfaces_only named_guids
using namespace RandomEngine;

int main(){
	CoInitialize(NULL);
	
	double d= Engine::LCAM();

	 CoUninitialize();
	return 0;
}

