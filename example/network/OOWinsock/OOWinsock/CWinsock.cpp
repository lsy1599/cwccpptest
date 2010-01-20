#include "CWinsock.h"
#include <crtdbg.h>
// ----------------------------------------------------------------------------
CWinsock::CWinsock(WORD wVersionRequested, WORD wMinVersion){
	_ASSERT(sg_bWinsockStarted == FALSE);

	m_iLastError = WSAStartup(wVersionRequested, (LPWSADATA) &m_wsaData);
	
	if (m_iLastError != WSANOERROR ){
		m_bNeedCleanup = FALSE;
		return ;
	}

	sg_bWinsockStarted	= TRUE;
	m_bNeedCleanup		= TRUE;

	if ( (HIBYTE(m_wsaData.wVersion) < HIBYTE(wMinVersion)) 
		|| ( HIBYTE(m_wsaData.wVersion) == HIBYTE(wMinVersion) && LOBYTE(m_wsaData.wVersion) < LOBYTE(wMinVersion))
		){

		m_iLastError = WSAVERNOTSUPPORTED; 
	}
}
// ----------------------------------------------------------------------------
CWinsock::~CWinsock(){
	if (!m_bNeedCleanup){
		return;
	}

	if (WSACleanup() == SOCKET_ERROR){
		m_iLastError = WSAGetLastError();
		// ...
	}

	sg_bWinsockStarted = FALSE;
}
// ----------------------------------------------------------------------------