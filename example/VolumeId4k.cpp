// VolumeId4k.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <windows.h>

char _toHex(wchar_t High,wchar_t Low)
{
char rc;
if(High>='A')
rc = High-'A'+10;
else
rc = High-'0';

rc <<= 4;

if(Low>='A')
rc |= Low-'A'+10;
else
rc |= Low-'0';

return rc;
}


int _tmain(int argc, _TCHAR* argv[])
{

if( argc < 3){
wprintf(L"Command : VolumeId4k G: 1111-1111\n");
return 1;
}

// convert Driver letter to driver index
TCHAR DriverLetter=argv[1][0];
if(DriverLetter>'Z')
DriverLetter-='a'-'A';
wprintf(L"Driver : %c\n",DriverLetter);

wchar_t _devicename[] = L"\\\\.\\A:";
_devicename[4] += DriverLetter-'A';


// Creating a handle to disk drive using CreateFile () function ..
HANDLE hDevice ;

hDevice = CreateFile(_devicename,
 GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
 NULL, OPEN_EXISTING, 0, NULL);
if (hDevice == INVALID_HANDLE_VALUE){
wprintf(L"Open Driver %s Failed!\n",argv[1]);
return 1;
}

// Read first sector
char buffer[4096];
DWORD bytesrw;

SetFilePointer (hDevice, 0, NULL, FILE_BEGIN);
if (!ReadFile (hDevice, buffer, 4096, &bytesrw, NULL) ){
wprintf(L"Read 0 sector failed!\n");
goto _exit;
}


// modify the volumeid field - only valid for FAT32
buffer[0x43]=_toHex(argv[2][7],argv[2][8]);
buffer[0x44]=_toHex(argv[2][5],argv[2][6]);
buffer[0x45]=_toHex(argv[2][2],argv[2][3]);
buffer[0x46]=_toHex(argv[2][0],argv[2][1]);


// write back
SetFilePointer (hDevice, 0, NULL, FILE_BEGIN);
if (!WriteFile (hDevice, buffer, 4096, &bytesrw, NULL) ){
wprintf(L"Write Sectpr Faile!\n");
goto _exit;
}


wprintf(L"Success!\n");


_exit:
if(hDevice)
CloseHandle(hDevice);

return 0;
}