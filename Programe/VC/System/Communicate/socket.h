#ifndef __SOCKET_H_KL_2007_07_04__
#define __SOCKET_H_KL_2007_07_04__

#pragma once
#include <WinSock2.h>
#include <list>
using namespace std;

 struct Exception {
    enum { len = 256 };
    char str_[len];
    char type_[len];
    Exception(const char* s=0, const char* e="rdr::Exception") {
      str_[0] = 0;
      if (s)
        strncat(str_, s, len-1);
      else
        strcat(str_, "Exception");
      type_[0] = 0;
      strncat(type_, e, len-1);
    }
    virtual const char* str() const { return str_; }
    virtual const char* type() const { return type_; }
  };

  struct SystemException : public Exception {
    int err;
    SystemException(const char* s, int err_);
  };

namespace Network
{
	//初始化 Socket 库
	class CInitSock
	{
	public:
		CInitSock(BYTE minorVer = 2, BYTE majorVer = 2);
		~CInitSock();
	};

	int InitalizeSocket();

	class CSocket
	{
	public:
		CSocket(int fd);
		virtual ~CSocket();

		// information about this end of the socket
		virtual string GetMyAddress() = 0;     // a string e.g. "192.168.0.1"
		virtual int GetMyPort() = 0;
		virtual string GetMyEndpoint() = 0;    // <address>::<port>

		// information about the remote end of the socket
		virtual string GetPeerAddress() = 0;   // a string e.g. "192.168.0.1"
		virtual int GetPeerPort() = 0;
		virtual string GetPeerEndpoint() = 0;  // <address>::<port>
		virtual int Shutdown() = 0;
		virtual int Close() = 0;

		// Is the remote end on the same machine?
		virtual bool SameMachine() = 0;

		virtual int Send(const void * lpBuf, int nBufLen, int nFlags = 0) = 0;
		virtual int Receive(void * lpBuf, int nBufLen, int nFlags = 0) = 0;

		int GetFd() {return m_fd;}
		int SetFd(int fd) {m_fd = fd; return fd;}

	protected:
		CSocket();

	private:
		int m_fd;

	};

	class CSocketException : public SystemException
	{
	public:
		CSocketException(const char * text, int err_) : SystemException(text, err_)
		{
			m_Text = text;
			m_Err = err_;
		}

		CSocketException(const char * text): SystemException(text, 0)
		{
			m_Text = text; 
		}

		string m_Text;
		int m_Err;
	};

	/*class CConnectionFilter
	{
	public:
		virtual bool VerifyConnection(CSocket * s) = 0;
		virtual bool QueryUserAcceptConnection(CSocket* s) {return false;}
	};*/

	class CSocketListener
	{
	public:
		CSocketListener();
		virtual ~CSocketListener() {}

		// shutdown() stops the socket from accepting further connections
		virtual int Shutdown() = 0;
		virtual int Close() = 0;

		// accept() returns a new Socket object if there is a connection
		// attempt in progress AND if the connection passes the filter
		// if one is installed.  Otherwise, returns 0.
		virtual CSocket * Accept() = 0;

		/*void SetFilter(CConnectionFilter * f)
		{
			m_filter = f; 
		}*/
		int GetFd()
		{
			return m_fd; 
		}
	protected:
		int m_fd;
		//CConnectionFilter * m_filter;
	};

	class CSocketServer {
	public:
		virtual ~CSocketServer() {}

		// addClient() tells the server to manage the socket.
		//   If the server can't manage the socket, it must shutdown() it.
		virtual int AddClient(Network::CSocket* sock) = 0;
		virtual int RemoveClient(Network::CSocket * pSock) = 0;

		// processSocketEvent() tells the server there is a socket read event.
		//   If there is an error, or the socket has been closed/shutdown then
		//   the server DON'T delete the socket AND return false.
		//   so that CManageSocket delete it.
		virtual bool ProcessReadEvent(Network::CSocket * sock) = 0;
		//处理发送数据事件
		virtual bool ProcessWriteEvent(Network::CSocket * pSock) = 0;

		// checkTimeouts() allows the server to check socket timeouts, etc.  The
		// return value is the number of milliseconds to wait before
		// checkTimeouts() should be called again.  If this number is zero then
		// there is no timeout and checkTimeouts() should be called the next time
		// an event occurs.
		virtual int CheckTimeouts() = 0;

		// soonestTimeout() is a function to help work out the soonest of several
		// timeouts.
		static void SoonestTimeout(int* timeout, int newTimeout) {
			if (newTimeout && (!*timeout || newTimeout < *timeout))
				*timeout = newTimeout;
		}
	};
};

#endif //__SOCKET_H_KL_2007_07_04__
