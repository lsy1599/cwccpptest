#include "CWinsockLib.h"
#include "CSockAddr.h"

struct IStreamCallback{
	enum STREAMEVENT{
		SE_CONNECT
		, SE_ACCEPT
		, SE_DATAREADY
		, SE_DATASEND
		, SE_CLOSE
	};

	virtual void StreamCallback(int iToken, STREAMEVENT iEvent, int iError, TCHAR* lpBuffer) = 0;
};
//--------------------------------------------------------------------------------------------------------------------
class CStreamSocket:private CWinsockEventCallback{
public:
	CStreamSocket();
	virtual ~CStreamSocket();

private:
	CStreamSocket(SOCKET s, IStreamCallback* pCallback, int i);
	CStreamSocket(CStreamSocket&);
	CStreamSocket& operator=(CStreamSocket&);

public: // interface implement
	virtual void WinsockEventCallback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

public: // method
	BOOL DataQueue();
	int LastError();
	void SetCallback(IStreamCallback* pCallback, int iToken);

	int Open();
	int Bind(CSockAddr& saBindAddr);
	int Close();
	int Connect(CSockAddr& saForeignAddr);
	int Listen(CSockAddr& saServiceAddr, int iQueueLen);
	CStreamSocket* Accept(IStreamCallback* pCallback, int iToken, CSockAddr* pcsaAddr = NULL);
	int Receive(TCHAR* lpBuffer, int* piBuffLength, int iFlags = 0);
	int Send(TCHAR* lpBuffer, int iLength, int iFlags = 0);

	int GetPeerName(CSockAddr* psaPeerName);
	int GetSockName(CSockAddr* psaSockName);

	int GetSockOpt(int iLevel, int oOptName, char* pOpVal, int* pnLen);
	int SetSockOpt(int iLevel, int iOptName, char* pOptVal, int nLen);

	int IoctlSocket(long lCommand, u_long* pArg);

private: // method
	//void AddTail(TCHAR*, TCHAR*, int);
	//void DeleteHead();

private:
	//struct BufferDescriptor{

	//};

	enum SOCKETSTATE{
		  IDLE
		, CONNECTING
		, CONNECTED
		, LISTENING
	};
private: // data
	SOCKET				m_s;
	int					m_iLastError;
	IStreamCallback*	m_pCallback;
	int					m_iToken;
	SOCKETSTATE			m_iState;
	//BufferDescriptor*	m_pbdHead;
	//BufferDescriptor*	m_pbdTail;
};
//--------------------------------------------------------------------------------------------------------------------