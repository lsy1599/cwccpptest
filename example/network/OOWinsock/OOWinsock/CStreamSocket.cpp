#include "CStreamSocket.h"
//#include "Winsock2.h"
CStreamSocket::CStreamSocket(): m_s(INVALID_SOCKET), m_iLastError(WSANOERROR), m_pCallback(NULL), m_iToken(0), m_iState(IDLE) {
	
}

CStreamSocket::CStreamSocket(SOCKET s, IStreamCallback* pCallback, int iToken): m_s(s), m_iLastError(WSANOERROR), m_pCallback(pCallback), m_iToken(iToken), m_iState(CONNECTED) {
	WSAAsyncSelect(m_s,  WSCGetEventWindow(), WM_WSAASYNCSELECT, FD_READ | FD_WRITE | FD_CLOSE); 
}

CStreamSocket::~CStreamSocket(){
	if (m_s != INVALID_SOCKET){
		Close();
	}
}

void CStreamSocket::WinsockEventCallback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){

}