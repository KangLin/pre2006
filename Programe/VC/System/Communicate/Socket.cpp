#include "stdafx.h"

#include "socket.h"
#pragma comment(lib, "Ws2_32.lib")

SystemException::SystemException(const char* s, int err_)
  : Exception(s, "rdr::SystemException"), err(err_)
{
  strncat(str_, ": ", len-1-strlen(str_));
#ifdef _WIN32
  // Windows error messages are crap, so use unix ones for common errors.
  const char* msg = 0;
  switch (err) {
  case WSAECONNREFUSED: msg = "Connection refused";       break;
  case WSAETIMEDOUT:    msg = "Connection timed out";     break;
  case WSAECONNRESET:   msg = "Connection reset by peer"; break;
  case WSAECONNABORTED: msg = "Connection aborted";       break;
  }
  if (msg) {
    strncat(str_, msg, len-1-strlen(str_));
  } else {
#ifdef UNICODE
    WCHAR* tmsg = new WCHAR[len-strlen(str_)];
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                  0, err, 0, tmsg, len-1-strlen(str_), 0);
    WideCharToMultiByte(CP_ACP, 0, tmsg, wcslen(tmsg)+1,
		              str_+strlen(str_), len-strlen(str_), 0, 0);
    delete [] tmsg;
#else
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                  0, err, 0, str_+strlen(str_), len-1-strlen(str_), 0);
#endif
  }
    
#else
  strncat(str_, strerror(err), len-1-strlen(str_));
#endif
  strncat(str_, " (", len-1-strlen(str_));
  char buf[20];
  sprintf(buf,"%d",err);
  strncat(str_, buf, len-1-strlen(str_));
  strncat(str_, ")", len-1-strlen(str_));
}

namespace Network
{

BOOL g_bInitialized = FALSE;

CInitSock::CInitSock(BYTE minorVer, BYTE majorVer)
{
	// 初始化WS2_32.dll
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(minorVer, majorVer);
	if(::WSAStartup(sockVersion, &wsaData) != 0)
	{
		throw CTException(_T("unable to initialise Winsock2"), WSAGetLastError());
	}
	TRACE(_T("Initialized Socket\n"));
}

CInitSock::~CInitSock()
{	
	::WSACleanup();
	TRACE(_T("Cleanup Socket\n"));
}


int InitalizeSocket()
{
	if(!g_bInitialized)
	{
		static CInitSock s;
		g_bInitialized = TRUE;
		return S_OK;
	}// 结束 if(!m_bInitialized)
	return S_FALSE;
}

CSocket::CSocket(): m_fd(INVALID_SOCKET)
{
	//初始化 Socket 库
	InitalizeSocket();
}

CSocket::CSocket(int fd) : m_fd(fd)
{
};

CSocket::~CSocket()
{
	Close();
}

int CSocket::Shutdown()
{
	return ::shutdown(GetFd(), SD_BOTH);
}

int CSocket::Close()
{
	if(INVALID_SOCKET != GetFd())
	{
		if(SOCKET_ERROR == ::closesocket(m_fd))
		{
			return S_FALSE;
		} // 结束 if(SOCKET_ERROR == ::closesocket(m_fd))
	}// 结束 if(INVALID_SOCKET != m_fd)
	return S_OK;
}

CSocketListener::CSocketListener()
{
	m_fd = INVALID_SOCKET;
	InitalizeSocket();
}

};