// PrinterUtilTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "PrinterUtil.h"
#include "FileUtils.h"

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{	
		HANDLE hPrinter = NULL;
		OpenPrinter(TEXT("Adobe PDF"), &hPrinter, NULL);
		if (hPrinter != NULL) {
			wcout << GetPrinterName(hPrinter);
			ClosePrinter(hPrinter);
			return TRUE;
		}

	return 0;
}

