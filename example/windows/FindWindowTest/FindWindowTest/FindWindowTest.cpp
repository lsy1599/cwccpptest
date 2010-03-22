// FindWindowTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <shellapi.h>
using namespace std;

HHOOK hookSkyboard;
LRESULT CALLBACK CallWndProc(
	int nCode,
    WPARAM wParam,
    LPARAM lParam
){

	return CallNextHookEx(hookSkyboard, nCode, wParam, lParam);
}

void LockWindow(){
	HWND boardWin = FindWindowEx(NULL, NULL, NULL, L"未命名 - 記事本");
	RECT boardWinRect;
	GetWindowRect(boardWin, &boardWinRect);
	hookSkyboard = SetWindowsHookEx(WH_CALLWNDPROC, CallWndProc, GetModuleHandle(NULL), 0L);

	HWND skypeWin = FindWindowEx(NULL, NULL, L"tSkMainForm.UnicodeClass", NULL);
	SetWindowPos (skypeWin, HWND_TOP, boardWinRect.right, boardWinRect.top, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);
	::UnhookWindowsHookEx(hookSkyboard); 
	//MSG msg;
	// while ( GetMessage(&msg, NULL, 0, 0) )
	// {
	//	 TranslateMessage(&msg);
	//	 DispatchMessage(&msg);
	// }
}

int _tmain(int argc, _TCHAR* argv[])
{
	//HINSTANCE  ret = ShellExecute(NULL, L"open", L"d:\\FindWindowTest.exe", NULL, NULL, SW_SHOWNORMAL);	
//	return 0;

	//LockWindow();
/*
	if (win != NULL){
		if (!IsWindow( win )){
			cout << "N";
		}else{
			//::PostMessage(win, WM_USER + 1, 0, 0);
			//TCHAR title[255];
			//::GetWindowText(win, title, 255);
			//wcout << title << endl;	
			//if ( 0 == wcscmp(title, L"Skyboard Utility") ){
			//	cout << "equal\n";
			//}else{
			//	cout << "not equal\n";
			//}
			char tmp[255];
			sprintf(tmp, "%x", win);
			cout << tmp << endl;
			cout << "Y";
		}		
	}else{
		cout << "N";
	}
*/
	//
	//win = FindWindowEx(NULL, NULL, NULL, L"Skyboard Utility:  Print in progress");
	//if (win != NULL){
	//	if (!IsWindow( win )){
	//		cout << "N";
	//	}else{
	//		::PostMessage(win, WM_USER + 1, 0, 0);
	//		cout << "Y";
	//	}		
	//}else{
	//	cout << "N";
	//}

	HANDLE icon = LoadImage(NULL, L"c:\\icon.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
	HWND win = FindWindowEx(NULL, NULL, L"Notepad", NULL);
	SendMessage(win, (UINT)WM_SETICON, ICON_BIG, (LPARAM)icon);
	SetWindowText(win, L"fdsafdas");
	


	return 0;
}

