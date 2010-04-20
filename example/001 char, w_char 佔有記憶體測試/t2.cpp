// t2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
int main(int argc, char* argv[])
{
	// �r���w�q
	char c='A';			// 0x41
	printf("char ���O���ڪ��O����j�p�� %d Bytes\n", sizeof(c));

	// �r��w�q
	char *pr="Hello~";
	static char par[]="Hello~";
	printf("char* ���O���ڪ��O����j�p�� %d Bytes\n", sizeof(pr));
	printf("char[] ���O���ڪ��O����j�p�� %d Bytes\n", sizeof(par));

	// �e�r���w�q
	wchar_t cw='A';		// 0x0041
	wchar_t cw2=L'A';	// �L���p���ŧi�A�sĶ���|�۰��X�R���e�r��
	printf("wchar_t ���O���ڪ��O����j�p�� %d Bytes\n", sizeof(cw));
	printf("wchar_t ���O(�ϥ�L�ѧO�r)���ڪ��O����j�p�� %d Bytes\n", sizeof(cw2));

	// �e�r��w�q
	wchar_t *psw=L"Hello~";
	static wchar_t paw[]=L"Hello~";
	printf("wchar_t* ���O���ڪ��O����j�p�� %d Bytes\n", sizeof(psw));  //  4 Bytes
	printf("wchar_t[] ���O���ڪ��O����j�p�� %d Bytes\n", sizeof(paw));	// 14 Bytes

	printf("�r���r����׬� %d\n", strlen(pr));
	printf("�e�r���r����׬� %d\n", wcslen(psw));

	return 0;
}

