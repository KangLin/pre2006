/*******************************************************************************************************
�ļ�����UDPSocket.h
��  �ܣ����ڶ��̵߳�,ʵ��UDP���ݰ�������ȷ���ķ��͡����ա�
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-12-4
ʱ  �䣺15:09:25
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
	CString szRemoteIP;  //Զ������IP
	UINT uRemotePort;    //Զ�������˿ں�
	LPVOID pBuf;         //���յ�����
	int iLen;            //���յ����ݳ���
	LPVOID pParent;      //��ָ��
	HANDLE* phEvent;     //�¼�����
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
	struct Data     //�������ݽṹ
	{
		LPVOID pBuf;
		int iLen;
	};
	enum
	{
		BUFFER_MAX_LEN = 4096,   //��������󳤶�
		RESPONSION = 0x80000000, //ȷ��Ӧ���
		NUMBERMAX = 0x7ffffffe,  //������ݰ�
		CLOSESOCKET = 0x7fffffff,//�ر�socket
		SECOND = 10000000,       //1s
		MILLISECOND = 10000      //1ms
	};

	class ADDRESS
	{
	public:
		CString m_szIP;          //��ַ
		UINT m_uPort;            //�˿�
		long m_lNumber;          //��ǰҪ���յ�/���͵����ݰ������
		                         //�����ȷ��Ӧ�����ݰ�,
		                         //��ֵΪ:���͵����ݰ������* -1
		                         //��Ϊ:uNumber | RESPONSION
		                         //���ֵΪ:0x7fffffff
		CUDPSocket* m_pParent;   //CUDPSocket��ָ�룬���ڴ����̵߳��ô����еĳ�Ա
		BOOL m_bThreadEnd;       //TRUE:��ֹ�߳�
		//--------------------------------------------
		ADDRESS()
		{
			m_bThreadEnd = FALSE;
			m_lNumber = 0;
		};
		~ADDRESS()
		{
			m_bThreadEnd = TRUE; //ֹͣ�߳�
		};
		/*******************************************************************************************************
		��������SetParent
		��  �ܣ�����CUDPSocket��ָ�룬���ڴ����̵߳��ô����еĳ�Ա
		��  ����
				CUDPSocket* pParent��CUDPSocket��ָ��
		����ֵ����
		��  �ߣ���  ��
		��  ����1.0.0.1
		��  �ڣ�2004-12-3
		ʱ  �䣺15:30:10
		*******************************************************************************************************/		
		void SetParent(CUDPSocket* pParent)
		{
			m_pParent = pParent;
		};
	};
	/*******************************************************************************************************
     ��  ����SendData
     ��  �ܣ��Ǽ�����ڼ�¼Զ��������Ϣ�ͻ��淢������
	         1����¼�������ݵ���Ϣ��������һ���̷߳��͡�
	         2������������ݻ�������û�з������ݣ���������̡߳�
			 3����������ݵ�����������������̷߳������ݡ�
			    �˹����� SendDataTo ��ʵ�֡�
			 4������з������ݣ����ͣ����ͺ�����̣߳������õȴ���ʱ������һ���ط�ʱ�䡣
			 5��������ط�ʱ����û�յ�ȷ��Ӧ�𣬵ȴ���ʱ��ʱ�䵽������������������̷߳������ݡ�
			 6��������ط�ʱ�����յ�Ӧ������������õȴ���ʱ������������������̷߳������ݡ�
			    �˹����� OnReceive ��ʵ�֡�
     ��  �ߣ���  ��
	 ��  ����1.0.0.1
	 ��  �ڣ�2004-12-3
	 ʱ  �䣺15:02:41
	*******************************************************************************************************/
	class SendData : public ADDRESS
	{
	public:
		HANDLE m_hTime;            //�ȴ���ʱ��������
		CRITICAL_SECTION m_cs;     //�����ط�ʱ�Ļ������
		DWORD m_dwLimitTime;       //��ʱ����λ����
        DWORD m_dwOverTime;        //��ʱ����λ����
		CList<Data, Data> m_pBuf;  //Ҫ���͵����ݶ���
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
            TRACE(_T("%s(%d) : SendData::~SendData��IP=%s:Port =%d:���ݰ����=%d\n"),
                            __FILE__, __LINE__, m_szIP, m_uPort, m_lNumber);
            //������ݶ���
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
            //ֹͣ�߳�
			m_bThreadEnd = TRUE;
			LARGE_INTEGER li;
			li.QuadPart = -0;
			::SetWaitableTimer(m_hTime, &li, 1000000, NULL, NULL, FALSE);
			Sleep(10);
            //�رյȴ���ʱ������
			::CancelWaitableTimer(m_hTime);
			CloseHandle(m_hTime);			
			//�رջ������
			DeleteCriticalSection(&m_cs);
			DWORD ExitCode;
			GetExitCodeThread(m_hThread, &ExitCode);
			if(ExitCode == STILL_ACTIVE && m_dwOverTime <= m_dwLimitTime)
			{
				int i = 0;
				while(!::TerminateThread(m_hThread, 1))//������߳��Լ��˳�
				{
					if(++i == -1 )
						break;
				}
                TRACE(_T("%s(%d) : class SendDataǿ����ֹ�����߳�,�߳��˳��Ĵ���Ϊ1��\n"), __FILE__, __LINE__);
            }
            //�ر��߳�
			CloseHandle(m_hThread);	
		};
	private:
		HANDLE m_hThread;
	};

	void Destroy();
public:
	CList<ADDRESS, ADDRESS> m_RecAdd;          //�������ݵ�Զ�������Ǽ��� 
	CList<SendData*, SendData*> m_SendBuffer;  //�������ݵ�Զ�������Ǽ���

	BOOL Inital(LPVOID pParent, THREADPROC ReceiveThread = NULL,
                UINT nLocatePort = 0, BOOL bNewThread = TRUE,
                THREADPROC OverTimeThread = NULL);
	void Close();
	BOOL SendDataTo(LPVOID pBuf, int iLen, UINT uRemotePort, CString szRemoteIP);
	static DWORD _stdcall SendThread(LPVOID lpParameter);     //�����߳�
	static DWORD _stdcall ReceiveThread(LPVOID lpParameter);  //�����߳�

    THREADPROC m_OverTimeThread;  //��ʱ�¼�
    LPVOID m_pParent;             //����ʵ����ָ��

private:
    THREADPROC m_ReceiveThread;   //�����̵߳ĵ�ַ     
    BOOL m_bNewThread;            //���յ��������Ƿ����µ��߳̽���
	HANDLE m_hEvent;              //�����¼�����
	long m_CLoseSleep;            //�ر�ʱ����ʱ
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDPSOCKET_H__E6B5F286_B971_4627_8111_62EB7B7FFDC4__INCLUDED_)
