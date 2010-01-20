#ifndef __CWINSOCK__
#define __CWINSOCK__
#include <Winsock2.h>
#include "CWinsockEventCallback.h"


#define WSANOERROR	0 
// ----------------------------------------------------------------------------------------

/**
 * 這個類別用來初始化 Winsock，並在執行階段收集 Winsock 資訊
 *
 **/
class CWinsock{
public: //
	CWinsock(WORD wVersionRequested, WORD wMinVersion);
	~CWinsock();

public: // property
	int LastError(){
		return m_iLastError;
	}

	LPWSADATA GetWSAData(){
		return (LPWSADATA)&m_wsaData;
	}

private:
	WSADATA		m_wsaData;		// WSAStartup 呼叫結果
	int			m_iLastError;	// winsock 最後一個發生的錯誤
	BOOL		m_bNeedCleanup;	// 是否需要呼叫 WSACleanup
};

// ----------------------------------------------------------------------------------------

#endif