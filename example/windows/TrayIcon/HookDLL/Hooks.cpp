// Hooks.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <objbase.h>
#include <Shellapi.h>

// constant /////////////////////////////////////////////////////////////////////////
//
#define SC_TRAYME	2
#define TRAYICONID	4

// struct ///////////////////////////////////////////////////////////////////////////
//
struct WNDDATA{
	HWND			m_hWnd;
	NOTIFYICONDATA	m_niData;
	BOOL			m_bHooked;
	BOOL			m_bMinimized;
};

// define share section for all hooked process //////////////////////////////////////
//
#pragma data_seg(".SHARE")
	HHOOK			g_hInitMenuHook = NULL;
	HHOOK			g_hMenuCommandHook = NULL;
	WNDDATA			g_listWnd[255];
	UINT			g_iLastIndex = 0;
	UINT			SWM_TRAYMSG = 0;
#pragma data_seg()
#pragma comment(linker,"/SECTION:.SHARE, RWS")

// global variables /////////////////////////////////////////////////////////////////
//
HINSTANCE	ghModule	= NULL;

// function prototype ///////////////////////////////////////////////////////////////
//
LRESULT CALLBACK InitMenuHookProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MenuCommandHookProc(int nCode, WPARAM wParam, LPARAM lParam);
HICON GetFileIconHandle(LPCTSTR lpszFileName, BOOL bSmallIcon);

/*********************************************************************
*	Function: DllMain
*	Author:	Chau Nguyen
*	Created On: 2003/10/24
* --------------------------------------------------------------------
*	Purpose: Entry point for DLL.
* --------------------------------------------------------------------
*	Input Parameters: No
*
*	Output Parameters: No
*
*	Return Value: No
*
* --------------------------------------------------------------------
* NOTE:
*	- 
*
* --------------------------------------------------------------------
* REVISION HISTORY:
*	Version		Date		Author		Description
*
*********************************************************************/
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	// reserve the DLL handle
	ghModule = (HINSTANCE)hModule;

	// register system-wide message
	SWM_TRAYMSG = RegisterWindowMessage("MY_HOOK_MESSAGE");

	//
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

/*********************************************************************
*	Function: BOOL WINAPI InstallHook()
*	Author:	Chau Nguyen
*	Created On: 2003/10/24
* --------------------------------------------------------------------
*	Purpose: Install hooks
* --------------------------------------------------------------------
*	Input Parameters: No
*
*	Output Parameters: No
*
*	Return Value: TRUE : success, FALSE : fail
*
* --------------------------------------------------------------------
* NOTE:
*	- 
*
* --------------------------------------------------------------------
* REVISION HISTORY:
*	Version		Date		Author		Description
*
*********************************************************************/
BOOL WINAPI InstallHook()
{
	g_hInitMenuHook = SetWindowsHookEx(WH_CALLWNDPROC, InitMenuHookProc, ghModule, 0);
	if( g_hInitMenuHook == NULL ){
		return FALSE;	
	}

	g_hMenuCommandHook = SetWindowsHookEx(WH_GETMESSAGE, MenuCommandHookProc, ghModule, 0);
	if( g_hMenuCommandHook == NULL ){
		return FALSE;	
	}


	return TRUE;
}

/*********************************************************************
*	Function: BOOL WINAPI UnInstallHook()
*	Author:	Chau Nguyen
*	Created On: 2003/10/24
* --------------------------------------------------------------------
*	Purpose: Uninstall hooks
* --------------------------------------------------------------------
*	Input Parameters: No
*
*	Output Parameters: No
*
*	Return Value: No
*
* --------------------------------------------------------------------
* NOTE:
*	- 
*
* --------------------------------------------------------------------
* REVISION HISTORY:
*	Version		Date		Author		Description
*
*********************************************************************/
BOOL WINAPI UnInstallHook()
{
	BOOL bSuccess = FALSE;

/*	// free all minimized windows
	for(UINT i = 0; i < g_iLastIndex; i++){
		if(g_listWnd[i].m_bMinimized){
			Shell_NotifyIcon(NIM_DELETE, &g_listWnd[i].m_niData);
			ShowWindow(g_listWnd[i].m_hWnd, SW_SHOW);
			g_listWnd[i].m_bMinimized = FALSE;
		}
	}
*/
	// unhook InitMenu
	bSuccess = UnhookWindowsHookEx(g_hInitMenuHook);
	if(!bSuccess){
		return FALSE;
	}
	
	// unhook MenuCommmand
	bSuccess = UnhookWindowsHookEx(g_hMenuCommandHook);
	if(!bSuccess){
		return FALSE;
	}
	
	return TRUE;
}

/*********************************************************************
*	Function: LRESULT CALLBACK InitMenuHookProc(int nCode, WPARAM wParam, LPARAM lParam)
*	Author:	Chau Nguyen
*	Created On: 2003/10/24
* --------------------------------------------------------------------
*	Purpose: Intercept InitPopupMenu message to change menu before its displaying
* --------------------------------------------------------------------
*	Input Parameters: No
*
*	Output Parameters: No
*
*	Return Value: No
*
* --------------------------------------------------------------------
* NOTE:
*	- 
*
* --------------------------------------------------------------------
* REVISION HISTORY:
*	Version		Date		Author		Description
*
*********************************************************************/
LRESULT CALLBACK InitMenuHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	// return immediately if system required
    if (nCode < 0){
        return CallNextHookEx(g_hInitMenuHook, nCode, wParam, lParam); 
	}
 
	// get window procedure struct
	CWPSTRUCT *wps = (CWPSTRUCT*)lParam;
	
	// check if this message is not the my own registered message (it is a system message)
	if(wps->message != SWM_TRAYMSG) {		
		switch (wps->message) {
		case WM_MENUSELECT:
			// menu is being closed
			if(wps->lParam == NULL && HIWORD(wps->wParam) == 0xFFFF){
				// determine what window
				for(UINT i = 0; i < g_iLastIndex; i++){
					if(g_listWnd[i].m_hWnd == (HWND)wps->hwnd){
						// remove menu item if it was added
						if(g_listWnd[i].m_bHooked){
							RemoveMenu(GetSystemMenu(g_listWnd[i].m_hWnd, FALSE), SC_TRAYME, MF_BYCOMMAND);
						}
						
						break;
					}
				}
			}
			break;
		case WM_INITMENUPOPUP:{
			// get the menu handle
			HMENU hMenu = (HMENU)wps->wParam;

			// check if it is a menu
			if(IsMenu(hMenu)){
				// is system menu
				if(HIWORD(wps->lParam) == TRUE){ 
					// check if this window was hooked or not
					for(UINT i = 0; i < g_iLastIndex; i++){
						if(g_listWnd[i].m_hWnd == (HWND)wps->hwnd){
							break; // exit the for loop
						}
					}
					
					// not hooked yet
					if(i == g_iLastIndex){
						// store the window handle
						g_listWnd[i].m_hWnd = (HWND)wps->hwnd;
						g_listWnd[i].m_bMinimized = FALSE;

						// get title od that window
						char szText[255];
						GetWindowText(g_listWnd[i].m_hWnd, szText, 255);
												
						// prepare a NotifyData struct for this winfow
						ZeroMemory(&(g_listWnd[i].m_niData), sizeof(NOTIFYICONDATA));
						g_listWnd[i].m_niData.cbSize = sizeof(NOTIFYICONDATA);
						g_listWnd[i].m_niData.hWnd = (HWND)wps->hwnd;
						
						HICON hIcon = (HICON)SendMessage(g_listWnd[i].m_hWnd, WM_GETICON, ICON_SMALL,0);					
						if(!hIcon){
							char szPath[255];
							HMODULE hModule = (HMODULE)OpenProcess(0, FALSE, GetWindowThreadProcessId(g_listWnd[i].m_hWnd, 0));
							GetModuleFileName(hModule, szPath, 255);
							hIcon = GetFileIconHandle(szPath, TRUE);
						}
						
						
						if(hIcon){
							g_listWnd[i].m_niData.hIcon = CopyIcon(hIcon);
						}
						else{
							g_listWnd[i].m_niData.hIcon = LoadIcon(NULL, IDI_QUESTION);
						}
						g_listWnd[i].m_niData.uID = TRAYICONID;
						g_listWnd[i].m_niData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
						strcpy(g_listWnd[i].m_niData.szTip, szText);
						g_listWnd[i].m_niData.uCallbackMessage = SWM_TRAYMSG;
		
						// append our own menu item
						AppendMenu(GetSystemMenu(g_listWnd[i].m_hWnd, FALSE), MF_BYPOSITION|MF_STRING, SC_TRAYME, "&Tray Me");					

						// set the flag on
						g_listWnd[i].m_bHooked = TRUE;
						
						// increase count
						g_iLastIndex++;
					}
					else if(i < g_iLastIndex){// hook allready
						// append our own menu item
						AppendMenu(GetSystemMenu(g_listWnd[i].m_hWnd, FALSE), MF_BYPOSITION|MF_STRING, SC_TRAYME, "&Tray Me");					

						// set the flag on
						g_listWnd[i].m_bHooked = TRUE;
					}
				}
			}
			break;
		}			
		
		}
		
	}
	else{ // this is my registered message
		switch(wps->lParam)
		{
		case WM_LBUTTONDOWN:
			// determine what window
			for(UINT i = 0; i < g_iLastIndex; i++){
				if(g_listWnd[i].m_hWnd == (HWND)wps->hwnd){
					Shell_NotifyIcon(NIM_DELETE, &g_listWnd[i].m_niData);
					ShowWindow(g_listWnd[i].m_hWnd, SW_SHOW);

					g_listWnd[i].m_bMinimized = FALSE;
					break;
				}
			}
			
			break;
		}
	}
		
    return CallNextHookEx(g_hInitMenuHook, nCode, wParam, lParam); 
}


/*********************************************************************
*	Function: LRESULT CALLBACK MenuCommandHookProc(int nCode, WPARAM wParam, LPARAM lParam)
*	Author:	Chau Nguyen
*	Created On: 2003/10/24
* --------------------------------------------------------------------
*	Purpose: Intercept all command message to process my own menu command.
* --------------------------------------------------------------------
*	Input Parameters: No
*
*	Output Parameters: No
*
*	Return Value: No
*
* --------------------------------------------------------------------
* NOTE:
*	- 
*
* --------------------------------------------------------------------
* REVISION HISTORY:
*	Version		Date		Author		Description
*
*********************************************************************/
LRESULT CALLBACK MenuCommandHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	// return immediately if system required
    if (nCode < 0){
        return CallNextHookEx(g_hMenuCommandHook, nCode, wParam, lParam); 
	}

	// process the arrival message
	MSG *msg = (MSG*)lParam;
	switch (msg->message) {
	case WM_SYSCOMMAND:
		if(LOWORD(msg->wParam) == SC_TRAYME ){
			// iterate to determine the arrival command belongs to which window
			for(UINT i = 0; i < g_iLastIndex; i++){
				if(g_listWnd[i].m_hWnd == (HWND)msg->hwnd){
					// check if it was not minimized yet
					if(!g_listWnd[i].m_bMinimized){
						// Add icon to tray
						Shell_NotifyIcon(NIM_ADD, &g_listWnd[i].m_niData);

						// free icon handle
						

						// hide window
						ShowWindow(g_listWnd[i].m_hWnd, SW_HIDE);

						// set the flag
						g_listWnd[i].m_bMinimized = TRUE;
					}
					
					break; // exit the for loop
				}
			}
		}
		break;
	}
	
	// call next hook
    return CallNextHookEx(g_hMenuCommandHook, nCode, wParam, lParam); 
}


HICON GetFileIconHandle(LPCTSTR lpszFileName, BOOL bSmallIcon)
{
    UINT uFlags = SHGFI_ICON | SHGFI_USEFILEATTRIBUTES;

    if (bSmallIcon)
        uFlags |= SHGFI_SMALLICON;
    else
        uFlags |= SHGFI_LARGEICON;

    SHFILEINFO sfi;
    SHGetFileInfo(lpszFileName, FILE_ATTRIBUTE_NORMAL, &sfi, sizeof(SHFILEINFO), uFlags);

    return sfi.hIcon;
}

