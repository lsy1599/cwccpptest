// enumDevice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "dsound.h"
using namespace std;

BOOL DSEnumProc(
  LPGUID lpGuid,
  LPCSTR lpcstrDescription,
  LPCSTR lpcstrModule,
  LPVOID lpContext
){
	cout << lpGuid << "\t"
		 << lpcstrDescription << "\t"
		 << lpcstrModule << endl;
	return FALSE;
}


int _tmain(int argc, _TCHAR* argv[])
{
    DWORD pv;  // Can be any 32-bit type.
     
    HRESULT hr = DirectSoundCaptureEnumerate(
        (LPDSENUMCALLBACK)DSEnumProc, NULL);
	
	
	return 0;
}

