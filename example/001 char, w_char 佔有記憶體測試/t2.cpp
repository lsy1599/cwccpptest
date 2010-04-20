// t2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
int main(int argc, char* argv[])
{
	// 字元定義
	char c='A';			// 0x41
	printf("char 型別佔據的記憶體大小為 %d Bytes\n", sizeof(c));

	// 字串定義
	char *pr="Hello~";
	static char par[]="Hello~";
	printf("char* 型別佔據的記憶體大小為 %d Bytes\n", sizeof(pr));
	printf("char[] 型別佔據的記憶體大小為 %d Bytes\n", sizeof(par));

	// 寬字元定義
	wchar_t cw='A';		// 0x0041
	wchar_t cw2=L'A';	// 無須如此宣告，編譯器會自動擴充為寬字元
	printf("wchar_t 型別佔據的記憶體大小為 %d Bytes\n", sizeof(cw));
	printf("wchar_t 型別(使用L識別字)佔據的記憶體大小為 %d Bytes\n", sizeof(cw2));

	// 寬字串定義
	wchar_t *psw=L"Hello~";
	static wchar_t paw[]=L"Hello~";
	printf("wchar_t* 型別佔據的記憶體大小為 %d Bytes\n", sizeof(psw));  //  4 Bytes
	printf("wchar_t[] 型別佔據的記憶體大小為 %d Bytes\n", sizeof(paw));	// 14 Bytes

	printf("字元字串長度為 %d\n", strlen(pr));
	printf("寬字元字串長度為 %d\n", wcslen(psw));

	return 0;
}

