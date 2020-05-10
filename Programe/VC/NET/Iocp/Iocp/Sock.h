#pragma once
#include <WinSock2.h>

//初始化 Socket 库
class CInitSock
{
public:
	CInitSock(BYTE minorVer = 2, BYTE majorVer = 2);
	~CInitSock();
};

//初始化SOCKET库
int InitalizeSocket();

class CSocket
{
public:
	CSocket(int nFd = SOCKET_ERROR);
	virtual ~CSocket(void);

	// information about this end of the socket
	virtual _tstring GetMyAddress() = 0;     // a string e.g. "192.168.0.1"
	virtual int GetMyPort() = 0;
	virtual _tstring GetMyEndpoint() = 0;    // <address>::<port>

	// information about the remote end of the socket
	virtual _tstring GetPeerAddress() = 0;   // a string e.g. "192.168.0.1"
	virtual int GetPeerPort() = 0;
	virtual _tstring GetPeerEndpoint() = 0;  // <address>::<port>

	//// Is the remote end on the same machine?
	//virtual bool SameMachine() = 0;

	virtual int Send(void * pBuf, int nLen, int nFlags = 0);
	virtual int Recv(void * pBuf, int nLen, int nFlags = 0);
	virtual int ShutDown(int nHow = SD_BOTH);
	virtual int Close();

	int GetFd();

protected:
	int m_nFd;
};
