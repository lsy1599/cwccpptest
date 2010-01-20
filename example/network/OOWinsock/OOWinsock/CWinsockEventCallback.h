#ifndef __CWINSOCKEVENTCALLBACK__
#define __CWINSOCKEVENTCALLBACK__
#include <windows.h>
#include <list>
#include <tchar.h>

/**
 *
 *
 **/
static BOOL sg_bWinsockStarted = FALSE;
static HWND sg_hwndWSCEventWindow = NULL;
static TCHAR sg_szWSCWindowClass[] = _T("WSAEventWindow");

/** 
 *
 *
 **/
#define WPARAM_TYPE_HANDLE	0
#define WPARAM_TYPE_SOCKET	0

/**
 * winsock 訊息定義
 *
 **/
#define  WM_WSAGETHOSTBYADDR		(WM_USER + 0)
#define  WM_WSAGETHOSTBYNAME		(WM_USER + 1)
#define  WM_WSAGETPROTOBYNAME		(WM_USER + 2)
#define  WM_WSAGETHPROTOBYNUMBER	(WM_USER + 3)
#define  WM_WSAGETSERVBYNAME		(WM_USER + 4)
#define  WM_WSAGETSERVBYPORT		(WM_USER + 5)
#define  WM_WSAASYNCSELECT			(WM_USER + 6)

/**
 * 輔助函數
 *
 **/
BOOL WSCCreateEventWindow(HINSTANCE hInstance, HINSTANCE hPreInstance);
HWND WSCGetEventWindow();
void ReportWSAError(LPCTSTR lpszMsg, int iError, HWND hwmd, HINSTANCE hInstance);
void WSCFatalError(LPCTSTR lpszMsg);

static LRESULT CALLBACK WSCEventWndProc(HWND hwmd, UINT msg, WPARAM wParam, LPARAM lParam);

/**
 * 需要接收 Winsock 事件的物件必須繼承此物件
 *
 **/
class CWinsockEventCallback{
protected: // method
	void Register(WPARAM wParam, int iType);
	void Deregister(WPARAM wParam, int iType);

protected: // property
	HWND GetEventWindow();

public: // virtual
	virtual void WinsockEventCallback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

private:

};


struct Node{
public:
	Node(WPARAM wParam, int iType, CWinsockEventCallback*	lpecbCallback){
		this->wParam = wParam;
		this->iType = iType;
		this->lpecbCallback = lpecbCallback;
	}

	WPARAM					wParam;
	int						iType;
	CWinsockEventCallback*	lpecbCallback; 
// operator overload
	inline bool operator == (const Node& r){
		return iType == r.iType && wParam == r.wParam && r.lpecbCallback == lpecbCallback;
	}
};
// ------------------------------------------------------------------------------------
class CWParamList:public std::list<Node>{
public: // 
	CWParamList();
	~CWParamList();

public: // method
	BOOL Add(WPARAM wParam, int iType, CWinsockEventCallback*	lpecbCallback);
	void Remove(WPARAM wParam, int iType, CWinsockEventCallback*	lpecbCallback);	
	BOOL IsExist(WPARAM wParam, int iType, CWinsockEventCallback*	lpecbCallback);


	BOOL Find(WPARAM wParam, int iType, CWinsockEventCallback*&	lpecbCallback);
};


#endif