#include "CWinsockEventCallback.h"
#include "commonFunc.h"
#include <algorithm>
CWParamList sg_clWparamList;

// ----------------------------------------------------------------------------
void CWinsockEventCallback::Register(WPARAM wParam, int iType){
	if (!sg_clWparamList.Add(wParam, iType, this)){
		WSCFatalError( _T("Don't registe CWinsockEventCallback object") ); 
	}
}
// ----------------------------------------------------------------------------
void CWinsockEventCallback::Deregister(WPARAM wParam, int iType){
	sg_clWparamList.Remove(wParam, iType, this);  
}
// ----------------------------------------------------------------------------
inline HWND CWinsockEventCallback::GetEventWindow(){ 
	return WSCGetEventWindow();
}
// ----------------------------------------------------------------------------
using std::list;
CWParamList::CWParamList():list(){
}
// ----------------------------------------------------------------------------
CWParamList::~CWParamList(){
}
// ----------------------------------------------------------------------------
BOOL CWParamList::Add(WPARAM wParam, int iType, CWinsockEventCallback*	lpecbCallback){
	if (IsExist(wParam, iType, lpecbCallback) ){
		return FALSE;
	}
	push_back( Node(wParam, iType, lpecbCallback));
	return TRUE;
}
// ----------------------------------------------------------------------------
void CWParamList::Remove(WPARAM wParam, int iType, CWinsockEventCallback*	lpecbCallback){
	remove( Node(wParam, iType, lpecbCallback) );	
}
// ----------------------------------------------------------------------------
BOOL CWParamList::Find(WPARAM wParam, int iType, CWinsockEventCallback*&	lpecbCallback){
	 
	list<Node>::const_iterator begin = this->begin(); 
	while(begin != this->end()){
		if (begin->iType == iType && 			
			begin->wParam == wParam){
				lpecbCallback = begin->lpecbCallback;
				return TRUE;
		}
		++begin;
	}

	return FALSE;	
}
// ----------------------------------------------------------------------------
BOOL CWParamList::IsExist(WPARAM wParam, int iType, CWinsockEventCallback*	lpecbCallback){
	return std::find(begin(), end(), Node(wParam, iType, lpecbCallback)) != end() ? TRUE:FALSE;
}
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
BOOL WSCCreateEventWindow(HINSTANCE hInstance, HINSTANCE hPreInstance){
	_ASSERT(hInstance != NULL);
	if (sg_hwndWSCEventWindow != NULL){
		return FALSE;
	}

	if (!hPreInstance ){
		WNDCLASS wc;
		wc.style = 0;
		wc.lpfnWndProc = WSCEventWndProc;
		wc.cbClsExtra  =0;
		wc.cbWndExtra =0;
		wc.hInstance = hInstance;
		wc.hIcon = NULL;
		wc.hCursor = NULL;
		wc.hbrBackground = NULL;
		wc.lpszClassName = sg_szWSCWindowClass ;
		wc.lpszMenuName = NULL;

		if (!RegisterClass(&wc)){
			return FALSE;
		}
	}

	 
	sg_hwndWSCEventWindow = ::CreateWindow(
		sg_szWSCWindowClass
		, _T("")
		, 0
		, CW_USEDEFAULT, CW_USEDEFAULT 
		, CW_USEDEFAULT, CW_USEDEFAULT
		, NULL
		, NULL
		, hInstance
		, NULL);	

	return sg_hwndWSCEventWindow == NULL?FALSE:TRUE;
}
// ----------------------------------------------------------------------------
HWND WSCGetEventWindow(){
	return sg_hwndWSCEventWindow;
}
// ----------------------------------------------------------------------------
void ReportWSAError(LPCTSTR lpszMsg, int iError, HWND hwmd, HINSTANCE hInstance){

}
// ----------------------------------------------------------------------------
void WSCFatalError(LPCTSTR lpszMsg){
	MessageBox(NULL, lpszMsg, _T("CWinsock Error"), MB_OK | MB_ICONEXCLAMATION);
	exit(1);
}
// ----------------------------------------------------------------------------
static LRESULT CALLBACK WSCEventWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	CWinsockEventCallback* lpecCallback;

	switch(msg){
		case WM_WSAGETHOSTBYADDR:
		case WM_WSAGETHOSTBYNAME:
		case WM_WSAGETPROTOBYNAME:
		case WM_WSAGETHPROTOBYNUMBER:
		case WM_WSAGETSERVBYNAME:
		case WM_WSAGETSERVBYPORT:
			if (sg_clWparamList.Find(wParam, WPARAM_TYPE_HANDLE, lpecCallback) ){
				_ASSERT( lpecCallback != NULL );
				lpecCallback->WinsockEventCallback(hwnd, msg, wParam, lParam);
			}
			return 0;
		case WM_WSAASYNCSELECT:
			if (sg_clWparamList.Find(wParam, WPARAM_TYPE_HANDLE, lpecCallback) ){
				_ASSERT( lpecCallback != NULL );
				lpecCallback->WinsockEventCallback(hwnd, msg, wParam, lParam);
			}
			return 0;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);  			
	}	
}