#ifndef __CWINSOCK__
#define __CWINSOCK__
#include <Winsock2.h>
#include "CWinsockEventCallback.h"


#define WSANOERROR	0 
// ----------------------------------------------------------------------------------------

/**
 * �o�����O�ΨӪ�l�� Winsock�A�æb���涥�q���� Winsock ��T
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
	WSADATA		m_wsaData;		// WSAStartup �I�s���G
	int			m_iLastError;	// winsock �̫�@�ӵo�ͪ����~
	BOOL		m_bNeedCleanup;	// �O�_�ݭn�I�s WSACleanup
};

// ----------------------------------------------------------------------------------------

#endif