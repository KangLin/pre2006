/*******************************************************************************************************
文件名：UDPSocket.h
功  能：基于多线程的,实现UDP数据包的有序、确定的发送、接收。
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-12-4
时  间：15:09:25
*******************************************************************************************************/
#if !defined(AFX_UDPSOCKET_H__E6B5F286_B971_4627_8111_62EB7B7FFDC4__INCLUDED_)
#define AFX_UDPSOCKET_H__E6B5F286_B971_4627_8111_62EB7B7FFDC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UDPSocket.h : header file
//

#include <Afxtempl.h>

typedef DWORD(_stdcall * THREADPROC)(LPVOID lpParameter);

struct UDPSOCKREMOTEINFO
{
	CString szRemoteIP;  //远程主机IP
	UINT uRemotePort;    //远程主机端口号
	LPVOID pBuf;         //接收的数据
	int iLen;            //接收的数据长度
	LPVOID pParent;      //父指针
	HANDLE* phEvent;     //事件对象
};
	
/////////////////////////////////////////////////////////////////////////////
// CUDPSocket command target

class CUDPSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CUDPSocket();
	virtual ~CUDPSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUDPSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CUDPSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:

private:
	struct Data     //发送数据结构
	{
		LPVOID pBuf;
		int iLen;
	};
	enum
	{
		BUFFER_MAX_LEN = 4096,   //缓存区最大长度
		RESPONSION = 0x80000000, //确定应答包
		NUMBERMAX = 0x7ffffffe,  //最大数据包
		CLOSESOCKET = 0x7fffffff,//关闭socket
		SECOND = 10000000,       //1s
		MILLISECOND = 10000      //1ms
	};

	class ADDRESS
	{
	public:
		CString m_szIP;          //地址
		UINT m_uPort;            //端口
		long m_lNumber;          //当前要接收的/发送的数据包的序号
		                         //如果是确定应答数据包,
		                         //此值为:发送的数据包的序号* -1
		                         //或为:uNumber | RESPONSION
		                         //最大值为:0x7fffffff
		CUDPSocket* m_pParent;   //CUDPSocket的指针，用于传给线程调用此类中的成员
		BOOL m_bThreadEnd;       //TRUE:终止线程
		//--------------------------------------------
		ADDRESS()
		{
			m_bThreadEnd = FALSE;
			m_lNumber = 0;
		};
		~ADDRESS()
		{
			m_bThreadEnd = TRUE; //停止线程
		};
		/*******************************************************************************************************
		函数名：SetParent
		功  能：设置CUDPSocket的指针，用于传给线程调用此类中的成员
		参  数：
				CUDPSocket* pParent：CUDPSocket的指针
		返回值：无
		作  者：康  林
		版  本：1.0.0.1
		日  期：2004-12-3
		时  间：15:30:10
		*******************************************************************************************************/		
		void SetParent(CUDPSocket* pParent)
		{
			m_pParent = pParent;
		};
	};
	/*******************************************************************************************************
     类  名：SendData
     功  能：登记项。用于记录远程主机信息和缓存发送数据
	         1、记录发送数据的信息，并启动一个线程发送。
	         2、如果发送数据缓存区中没有发送数据，则挂起发送线程。
			 3、如果有数据到来，则启动挂起的线程发送数据。
			    此过程中 SendDataTo 中实现。
			 4、如果有发送数据，则发送，发送后挂起线程，并设置等待定时器设置一个重发时间。
			 5、如果在重发时间内没收到确定应答，等待定时器时间到后，则重新启动挂起的线程发送数据。
			 6、如果在重发时间内收到应答包。则重设置等待定时器，重新启动挂起的线程发送数据。
			    此过程在 OnReceive 中实现。
     作  者：康  林
	 版  本：1.0.0.1
	 日  期：2004-12-3
	 时  间：15:02:41
	*******************************************************************************************************/
	class SendData : public ADDRESS
	{
	public:
		HANDLE m_hTime;            //等待定时器对象句柄
		CRITICAL_SECTION m_cs;     //用于重发时的互拆访问
		DWORD m_dwLimitTime;       //限时，单位：秒
        DWORD m_dwOverTime;        //用时，单位：秒
		CList<Data, Data> m_pBuf;  //要发送的数据队列
		//--------------------------------------------
		SendData()
		{
			m_dwLimitTime = 60 * 10;
            m_dwOverTime = 0;
			InitializeCriticalSection(&m_cs);
			m_hTime = ::CreateWaitableTimer(NULL, FALSE, NULL);
			m_hThread = CreateThread(NULL, NULL, SendThread, this, NULL, NULL);
		};
		~SendData()
		{
            TRACE(_T("%s(%d) : SendData::~SendData。IP=%s:Port =%d:数据包序号=%d\n"),
                            __FILE__, __LINE__, m_szIP, m_uPort, m_lNumber);
            //清除数据队列
			::EnterCriticalSection(&m_cs);
			if(!m_pBuf.IsEmpty())
			{
				POSITION pos;
				pos = m_pBuf. GetHeadPosition();
				while(pos)
				{
					Data& d = m_pBuf.GetNext(pos);
				    delete []d.pBuf;
                    d.pBuf = NULL;
				}
				m_pBuf.RemoveAll();
			}
			::LeaveCriticalSection(&m_cs);
            //停止线程
			m_bThreadEnd = TRUE;
			LARGE_INTEGER li;
			li.QuadPart = -0;
			::SetWaitableTimer(m_hTime, &li, 1000000, NULL, NULL, FALSE);
			Sleep(10);
            //关闭等待定时器对象
			::CancelWaitableTimer(m_hTime);
			CloseHandle(m_hTime);			
			//关闭互拆对象
			DeleteCriticalSection(&m_cs);
			DWORD ExitCode;
			GetExitCodeThread(m_hThread, &ExitCode);
			if(ExitCode == STILL_ACTIVE && m_dwOverTime <= m_dwLimitTime)
			{
				int i = 0;
				while(!::TerminateThread(m_hThread, 1))//最好是线程自己退出
				{
					if(++i == -1 )
						break;
				}
                TRACE(_T("%s(%d) : class SendData强行终止发送线程,线程退出的代码为1。\n"), __FILE__, __LINE__);
            }
            //关闭线程
			CloseHandle(m_hThread);	
		};
	private:
		HANDLE m_hThread;
	};

	void Destroy();
public:
	CList<ADDRESS, ADDRESS> m_RecAdd;          //接收数据的远程主机登记项 
	CList<SendData*, SendData*> m_SendBuffer;  //发送数据的远程主机登记项

	BOOL Inital(LPVOID pParent, THREADPROC ReceiveThread = NULL,
                UINT nLocatePort = 0, BOOL bNewThread = TRUE,
                THREADPROC OverTimeThread = NULL);
	void Close();
	BOOL SendDataTo(LPVOID pBuf, int iLen, UINT uRemotePort, CString szRemoteIP);
	static DWORD _stdcall SendThread(LPVOID lpParameter);     //发送线程
	static DWORD _stdcall ReceiveThread(LPVOID lpParameter);  //接收线程

    THREADPROC m_OverTimeThread;  //超时事件
    LPVOID m_pParent;             //父类实例的指针

private:
    THREADPROC m_ReceiveThread;   //接收线程的地址     
    BOOL m_bNewThread;            //接收到的数据是否用新的线程进行
	HANDLE m_hEvent;              //接收事件对象
	long m_CLoseSleep;            //关闭时的延时
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDPSOCKET_H__E6B5F286_B971_4627_8111_62EB7B7FFDC4__INCLUDED_)
