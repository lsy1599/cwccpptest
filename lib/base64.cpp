// base64.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <stdio.h>
#include <memory.h>
#include <vector>
#include <string>
#include <iostream>
#include <windows.h>
#include <list>
const int MAX_MIME_LINE_LEN	= 76;
std::string XBase64Encode(TCHAR* filename) {
	static const char* s_Base64Table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	bool m_bAddLineBreak = false;
//, const char* pbInput, int nInputSize/*, unsigned char* pbOutput, int nMaxSize*/
	std::list<unsigned char> tmp;

	HANDLE hFile = CreateFile(filename, 
                     GENERIC_READ,
                     FILE_SHARE_READ, 
                     NULL,
                     OPEN_EXISTING, 
                     FILE_ATTRIBUTE_NORMAL, 
                     NULL);
	DWORD nInputSize = GetFileSize(hFile, NULL);
	DWORD readed;
	char* pbInput = new char[nInputSize];
	ReadFile(hFile, pbInput, nInputSize, &readed, NULL);
	//__dbg_printf(_T("File Length: %d"), size);
	//__dbg_printf(_T("Read: %d"), readed);  
	CloseHandle(hFile);	

	//unsigned char* pbOutStart = pbOutput;
	//unsigned char* pbOutEnd = pbOutput + nMaxSize;
	int nFrom, nLineLen = 0;
	unsigned char chHigh4bits = 0;

	for (nFrom=0; nFrom<nInputSize; nFrom++)
	{
		//if (pbOutput >= pbOutEnd)
		//	break;

		unsigned char ch = pbInput[nFrom];
		switch (nFrom % 3)
		{
		case 0:
			tmp.push_back( s_Base64Table[ch >> 2] );
			//*pbOutput++ = s_Base64Table[ch >> 2];
			chHigh4bits = (ch << 4) & 0x30;
			break;

		case 1:
			tmp.push_back( s_Base64Table[chHigh4bits | (ch >> 4)] );
			//*pbOutput++ = s_Base64Table[chHigh4bits | (ch >> 4)];
			chHigh4bits = (ch << 2) & 0x3c;
			break;

		default:
			tmp.push_back(s_Base64Table[chHigh4bits | (ch >> 6)]);
			//*pbOutput++ = s_Base64Table[chHigh4bits | (ch >> 6)];
			//if (pbOutput < pbOutEnd)
			//{
				tmp.push_back(s_Base64Table[ch & 0x3f]);
				//*pbOutput++ = s_Base64Table[ch & 0x3f];
				nLineLen++;
			//}
		}

		nLineLen++;
		//if (m_bAddLineBreak && nLineLen >= MAX_MIME_LINE_LEN && pbOutput+2 <= pbOutEnd)
		//{
		//	*pbOutput++ = '\r';
		//	*pbOutput++ = '\n';
		//	nLineLen = 0;
		//}
	}

	if (nFrom % 3 != 0 )	// 76 = 19 * 4, so the padding wouldn't exceed 76
	{
		tmp.push_back(s_Base64Table[chHigh4bits]);
		//*pbOutput++ = s_Base64Table[chHigh4bits];
		int nPad = 4 - (nFrom % 3) - 1;
		//if (pbOutput+nPad <= pbOutEnd)
		//{
			//::memset(pbOutput, '=', nPad);
			//pbOutput += nPad;
			for(int i =0; i <nPad; ++i){
				tmp.push_back('=');
			}
		//}		
	}
	//if (m_bAddLineBreak && nLineLen != 0 && pbOutput+2 <= pbOutEnd)	// add CRLF
	//{
	//	*pbOutput++ = '\r';
	//	*pbOutput++ = '\n';
	//}
	//return (int)(pbOutput - pbOutStart);

	return std::string(tmp.begin(), tmp.end());
}

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace std;
/*
	char* src = "This is an encoded string";
	unsigned char dst[255];

	std::string s( XBase64Encode(src, strlen(src)) );
*/

	
	//fread(buf, sizeof(char), stream);
	//fclose(stream);
	//std::string s( XBase64Encode(src, strlen(src)) );
	std::string s( XBase64Encode(TEXT("c:\\my.zip")));
	MessageBoxA(0, s.c_str(),0, 0); 
//	cout << s << endl;

	return 0;
}

