/*******************************************************************************************************
�ļ�����UDPSocket.cpp
��  �ܣ����ڶ��̵߳�,ʵ��UDP���ݰ�������ȷ���ķ��͡����ա�
        ʵ�ַ��ͳ�ʱû�нӵ�Ӧ������ͽ��������̡߳����Ե�Զ������������ʱ����ʱ����ֹ�������ݰ�(2005��7��2�� ����)
��  �⣺��������ʱ�������ݴ��� BUFFER_MAX_LEN ʱ��û�п��ǡ�
��  ����1������һ������ CUDPSocket m_udpSocket;
        2������һ�������߳�(ReceiveThread)�����߳�ʽ��ʽ����CUDPSocket::ReceiveThread
           ע���ڴ��߳���һ��Ҫ�����¼�����Ϊ���ź�״̬��
           DWORD _stdcall ReceiveThread(LPVOID lpParameter)
           {
                 TRACE(_T("CUDPSocket::ReceiveThread\n"));
                 UDPSOCKREMOTEINFO* p = (UDPSOCKREMOTEINFO*)lpParameter;
                 CString szRemoteIP(p->szRemoteIP); //�������ݵ�������ַ
                 UINT uRemotePort = p->uRemotePort; //�������ݵ������˿�
                 
                 //���ƽ��յ�����
                 int iLen = p->iLen;                //�������ݵĳ���
                 LPVOID buf = new BYTE[iLen]; 
                 memcpy(buf, p->pBuf, iLen);
                 
                 CWinsocketexpDlg* pParent = (CWinsocketexpDlg*) p->pParent; //ת��Ϊ������
                 ::SetEvent(*(p->phEvent));   //�����¼�����Ϊ���ź�
                 
                 //�Խ��յ����ݽ��д���
                 //...........
                 //

                 delete []buf
                 return 0;
           }
        3�����Ҫ����ʱ�¼��Ļ�����Ҫ����һ����ʱ��Ա������
           ��ʽͬ�ϡ�������ֻ�� pParent��szRemoteIP �� uRemotePort �����塣������û�����塣
        4����ʼ������m_udpSocket.Init(this, ReceiveThread, uLocatePort, OverTimeThread);
        5����Ҫ��������ʱ���� m_udpSocket.SendDataTo(buf, iLen, szRemoteIP, uRemotePort);
        6�����߳�ReceiveThread�д�����յ�����
        7������г�ʱ������ʱ���ں����д���ʱ�¼���
        8���˳�ʱ������ m_udpSocket.Close();�ر� Socket
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-12-4
ʱ  �䣺13:48:27
*******************************************************************************************************/

#include "stdafx.h"
#include "test\winsocketexp.h"
#include "test\winsocketexpdlg.h"
#include "UDPSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CUDPSocket, CSocket)
    //{{AFX_MSG_MAP(CUDPSocket)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif    // 0

/////////////////////////////////////////////////////////////////////////////
// CUDPSocket

CUDPSocket::CUDPSocket()
{
    m_hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
    m_ReceiveThread = ReceiveThread;
    m_OverTimeThread = NULL;
    m_CLoseSleep = 100;
}

CUDPSocket::~CUDPSocket()
{
    Destroy();
}

/*******************************************************************************************************
��������Destroy
��  �ܣ���������,����ʱ���������
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-3
ʱ  �䣺14:48:42
*******************************************************************************************************/
void CUDPSocket::Destroy()
{
    POSITION pos = m_SendBuffer.GetHeadPosition();
    while(pos)
    {
        SendData* psd = m_SendBuffer.GetNext(pos);
        delete psd;
    }
    m_SendBuffer.RemoveAll();
}

/*******************************************************************************************************
��������Close
��  �ܣ��ر�CUDPSocket
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-3
ʱ  �䣺16:15:11
*******************************************************************************************************/
void CUDPSocket::Close()
{
    TRACE(_T("%s(%d) : CUDPSocket::Close\n"), __FILE__, __LINE__);

    POSITION pos = m_SendBuffer.GetHeadPosition();
    SendData* psd;
    while(pos != NULL)
    {
        psd = m_SendBuffer.GetNext(pos);
        LPVOID p = new BYTE[sizeof(long)];
        long lCloseSocket = CLOSESOCKET;
        memcpy(p, &lCloseSocket, sizeof(long)); //�������ݰ����
        Data data;
        data.pBuf = p;
        data.iLen = sizeof(long);
        ::EnterCriticalSection(&psd->m_cs);
        psd->m_pBuf.AddHead(data);
        ::LeaveCriticalSection(&psd->m_cs);    
        //�����������߳�
        LARGE_INTEGER li;
        li.QuadPart = -1;
        ::SetWaitableTimer(psd->m_hTime, &li, 1000000, NULL, NULL, FALSE);
    }
    Sleep(m_CLoseSleep);
    Destroy();
    CSocket::Close();
}

/*******************************************************************************************************
��������Inital
��  �ܣ���ʼ���������ｨsocket�����ø�����ָ�롢���մ����߳�
��  ����
         LPVOID *pParent������ʵ��ָ��
         THREADPROC ReceiveThread���������ݴ����̡߳�NULLΪĬ���ڲ������߳�
         UINT nLocatePort��Ҫ�󶨵Ķ˿ں�
         BOOL bNewThread���Ƿ��ڽ���ʱ�����µ��̴߳�����յ�������
         THREADPROC OverTimeThread����ʱ�¼������������ݳ�ʱʱ���
����ֵ���ɹ�����TRUE�����򷵻�FALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-4
ʱ  �䣺10:11:44
*******************************************************************************************************/
BOOL CUDPSocket::Inital(LPVOID pParent, THREADPROC ReceiveThread, UINT nLocatePort, BOOL bNewThread, THREADPROC OverTimeThread)
{
    m_pParent = pParent;
    m_bNewThread = bNewThread;
    if(ReceiveThread)
    {
        m_ReceiveThread = ReceiveThread;
    } // ���� if(ReceiveThread)
       
    m_OverTimeThread = OverTimeThread;
   
    Close();
    if(!Create(nLocatePort, SOCK_DGRAM))
    {
        TRACE(_T("%s(%d) : CUDPSocket����ʧ�ܡ�\n"), __FILE__, __LINE__);
        return FALSE;
    }
    TRACE(_T("%s(%d) : CUDPSocket�ɹ�������\n"), __FILE__, __LINE__);
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CUDPSocket member functions

/*******************************************************************************************************
��������OnReceive
��  �ܣ���������
˵  �������ݸ�ʽ���������ݵ�ǰ�ĸ��ֽ�Ϊ�����͵����ݰ���ţ����λ��ʾ�Ƿ���ȷ������1��Ϊȷ������0��Ϊ���ݰ�����
        ���������Ϊ���ݰ��ı�š�
��  ����1���õ����ݡ�
        2���Ƿ���ȷ����
           2.1��ɾ�����ͻ������е�ͷ(�������)����������ʱʱ��Ϊ0��
           2.2�������������еķ����߳�
        3�������ݰ�
           3.1�������Ƿ���Զ�������Ǽ���
                3.1.1���У��������ݡ�
                  3.1.1.1����Զ�������˳������ӵǼ�����ɾ����Զ������
                  3.1.1.2����Ҫ���յ����ݡ�����ż�һ����Ӧ��������������̣߳�����ô���������ݵĺ�������
                       ע�⣺���ϵ�˳���ܸı䣬�����̻߳���Ҫ�ܳ�����ʱ��ʱ����������ʼ���ط��������¶�ε���
                  3.1.1.3�����ѽ��յ����ݡ�ֻ��Ӧ���
                  3.1.1.4������Ҫ���յ����ݣ�����
                3.1.2���񣬽����Ǽ��
		          3.1.2.1����Զ�������˳��������˳���
                  3.1.2.2��������������ݰ�������ϼ�һ
                          (����ԭ���Ѿ����գ�������ĳ����������˳���
                           �ֽ��룬�������ݰ���Ų�һ����0)��
						   ��Ӧ��������������̣߳�����ô���������ݵĺ�������
                  3.1.2.3�����������߳�
        4�����µ��¼��߳��и��������ݺ������¼�����Ϊ���ź�״̬
           ::SetEvent(p->hEvent);
��  ����
         int nErrorCode�������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-3
ʱ  �䣺19:12:19
*******************************************************************************************************/
void CUDPSocket::OnReceive(int nErrorCode) 
{ 
    UDPSOCKREMOTEINFO remote;

    //1����������
    BYTE buf[BUFFER_MAX_LEN];
    remote.iLen = ReceiveFrom(buf, BUFFER_MAX_LEN, remote.szRemoteIP, remote.uRemotePort);
    if(remote.iLen == SOCKET_ERROR)
    {
        if(GetLastError() == WSAEMSGSIZE)
        {
            //���ݱ��ؼ�
            ASSERT(0);
        } // ���� if(GetLastError() == WSAEMSGSIZE)
        TRACE(_T("%s(%d) : CUDPSocket::OnReceive û���յ�����.\n"), __FILE__, __LINE__);
        //CSocket::OnReceive(nErrorCode);
        return;
    }
    TRACE(_T("%s(%d) : CUDPSocket::OnReceive �յ����ݴ�С:%d.\n"), __FILE__, __LINE__, remote.iLen);
    
    //���ݰ������
    long lNumber;
    memcpy(&lNumber, buf, sizeof(long));

    //2����ȷ��Ӧ���
    if(lNumber & RESPONSION)
    {
        TRACE(_T("��ȷ��Ӧ�����0x%x\n"), lNumber);
        //���ҵǼ������Ƿ��д�Զ������
        POSITION pos = m_SendBuffer.GetHeadPosition();
        SendData* psd;
        while(pos != NULL)
        {
            psd = m_SendBuffer.GetNext(pos);
			if((psd->m_szIP == remote.szRemoteIP) && (psd->m_uPort == remote.uRemotePort))
            {
                //ɾ�����ͻ������е�ͷ
                ::EnterCriticalSection(&psd->m_cs);    
                TRACE(_T("%s(%d) : ɾ�����ͻ������е�ͷ,�����ٽ���\n"), __FILE__, __LINE__);
				if(!psd->m_pBuf.IsEmpty())
                {
                    if(psd->m_pBuf.GetHead().pBuf)//�����Ƿ�Ϊ��
                    {
                        long lNo;
                        memcpy(&lNo, psd->m_pBuf.GetHead().pBuf, sizeof(long));
                        lNo |= RESPONSION;
                        if(lNo == lNumber)//�ǵ�ǰ����ͷ��Ӧ���
                        {
                            delete []psd->m_pBuf.GetHead().pBuf;
                            psd->m_pBuf.GetHead().pBuf = NULL;
                            psd->m_pBuf.RemoveHead();
                            psd->m_dwOverTime = 0;  //������ʱʱ��
                            ::LeaveCriticalSection(&psd->m_cs);   
                            TRACE(_T("%s(%d) : ɾ�����ͻ������е�ͷ,�뿪�ٽ���\n"), __FILE__, __LINE__);
                            //���������߳�
                            LARGE_INTEGER li;
                            li.QuadPart = -1;
                            ::SetWaitableTimer(psd->m_hTime, &li, 1, NULL, NULL, FALSE);
                            //CSocket::OnReceive(nErrorCode);
                            return;
                        }//�ǵ�ǰ����ͷ��Ӧ���
                        ::LeaveCriticalSection(&psd->m_cs);    
                        TRACE(_T("%s(%d) : ɾ�����ͻ������е�ͷ,�뿪�ٽ���\n"), __FILE__, __LINE__);
                        //CSocket::OnReceive(nErrorCode);
                        return;
                    }//���в�Ϊ��
                } // ���� if(!psd->m_pBuf.IsEmpty())
                ::LeaveCriticalSection(&psd->m_cs);    
                TRACE(_T("%s(%d) : ɾ�����ͻ������е�ͷ,�뿪�ٽ���\n"), __FILE__, __LINE__);
                return;
            }// ���� if((psd->m_szIP == remote.szRemoteIP) && (psd->m_uPort == remote.uRemotePort))
        }//while(psd = m_SendBuffer.GetNext(pos))
        //CSocket::OnReceive(nErrorCode);
        return;
    }//if(lNumber & RESPONSION)

    remote.pBuf = buf + sizeof(long);
    remote.iLen -= sizeof(long);
    remote.pParent = m_pParent;
    remote.phEvent = &m_hEvent;

	//3�������ݰ�
	//3.1.1��Զ���������ڵǼ�����    
    if(!m_RecAdd.IsEmpty())
    {   //Զ���������ڵǼ�����
        POSITION pos = m_RecAdd.GetHeadPosition();
        int index = -1; //����ɾ������Զ��������Ϣ�ĵǼ���
        while(pos != NULL)
        {            
            ADDRESS& recadd = m_RecAdd.GetNext(pos);
            index++;
			if((recadd.m_szIP == remote.szRemoteIP) && (recadd.m_uPort == remote.uRemotePort))
            {
				if(CLOSESOCKET == lNumber) //��Զ�������˳��źŰ�
                {
                    //����Ӧ���
                    lNumber |= RESPONSION;
                    SendTo(&lNumber, sizeof(long), remote.uRemotePort, remote.szRemoteIP);
                    TRACE(_T("%s(%d) : Զ��������%s:%d �˳�\n"), __FILE__, __LINE__, remote.szRemoteIP, remote.uRemotePort);
                    //ɾ������Զ��������Ϣ�ĵǼ���
                    m_RecAdd.RemoveAt(m_RecAdd.FindIndex(index));

                    //ɾ�����Զ���������͵Ǽ���
                    POSITION spos = m_SendBuffer.GetHeadPosition();
                    int sindex = 0;
                    while(spos)
                    {
                        SendData* psd = m_SendBuffer.GetNext(spos);
                        if((psd->m_szIP == remote.szRemoteIP) && (psd->m_uPort == remote.uRemotePort))
                        {                            
                            m_SendBuffer.RemoveAt(m_SendBuffer.FindIndex(sindex));
                            delete psd;
                        }
                        sindex++;
                        return;
                    }
                    return;
                } // ���� if(CLOSESOCKET == lNumber)

				if(recadd.m_lNumber == lNumber)//�ǵ���Ҫ���յ����ݰ�
                {  
                    //�������ݰ������
                    recadd.m_lNumber = (recadd.m_lNumber == NUMBERMAX) ? 0 : (recadd.m_lNumber + 1);
                    //����Ӧ���
                    lNumber |= RESPONSION;
                    SendTo(&lNumber, sizeof(long), remote.uRemotePort, remote.szRemoteIP);                     
                    
                    if(m_bNewThread)
                    {
                        TRACE(_T("%s(%d) : Զ���������ڵǼ�����,UDPSocket�����µ��̴߳����������\n"), __FILE__, __LINE__);
                        //�����߳�
                        ::ResetEvent(m_hEvent);
                        CreateThread(NULL, NULL, m_ReceiveThread, &remote, NULL, NULL);
						::WaitForSingleObject(m_hEvent, INFINITE);//�ȴ��û����������ݺ������¼�����Ϊ���ź�״̬
                    }
                    else
                    {
                        TRACE(_T("%s(%d) : Զ���������ڵǼ�����,UDPSocket���ú���,��ǰ�߳�ID:%x\n"), __FILE__, __LINE__, ::GetCurrentThreadId());
                        m_ReceiveThread(&remote);
                    }                   
                }//�ǵ���Ҫ���յ����ݰ�
                else if(recadd.m_lNumber > lNumber || (lNumber == NUMBERMAX && recadd.m_lNumber == 0))
                {   //���ѽ��չ������ݰ��������Ƿ��Ͷ�û���յ�Ӧ�����ط�
                    //����Ӧ���
                    lNumber |= RESPONSION;
					SendTo(&lNumber, sizeof(long), remote.uRemotePort, remote.szRemoteIP);
                } // ���� if(recadd.m_lNumber == lNumber)
                
                //CSocket::OnReceive(nErrorCode);
                return;
            } // ���� if((recadd.m_szIP == remote.szRemoteIP) && (recadd.m_uPort == remote.uRemotePort))
        }//while(psd)
    }//if(!m_RecAdd.IsEmpty())

	//3.1.2��Զ���������ڵǼ�����
    if(CLOSESOCKET == lNumber) //��Զ�������˳��źŰ�
    {
        //CSocket::OnReceive(nErrorCode);
        return;
    }

    ADDRESS recadd;
    recadd.m_szIP = remote.szRemoteIP;
    recadd.m_uPort = remote.uRemotePort;
    //if(recadd.m_lNumber == lNumber)//�������ڷ���ʱ�˳����ֽ��룬�����ݰ�����Ų�һ����0����Ϊ�Ѿ�������һЩ����
    {          
        //�������ݰ������
        recadd.m_lNumber = (lNumber == NUMBERMAX) ? 0 : (lNumber + 1);
        m_RecAdd.AddTail(recadd);//�ڵǼ��������Զ������
        //����Ӧ���
        lNumber |= RESPONSION;
        SendTo(&lNumber, sizeof(long), remote.uRemotePort, remote.szRemoteIP); 

        if(m_bNewThread)
        {
            TRACE(_T("%s(%d) : UDPSocket�����µ��̴߳����������\n"), __FILE__, __LINE__);
            //�����߳�
            ::ResetEvent(m_hEvent);
            CreateThread(NULL, NULL, m_ReceiveThread, &remote, NULL, NULL);
			::WaitForSingleObject(m_hEvent, INFINITE);
        }
        else
        {
            TRACE(_T("%s(%d) : UDPSocket���ú���,��ǰ�߳�ID:%x\n"), __FILE__, __LINE__, ::GetCurrentThreadId());
            m_ReceiveThread(&remote);
        }
        
    }

    //CSocket::OnReceive(nErrorCode);
}

/*******************************************************************************************************
��������ReceiveThread
��  ����Ĭ�ϵĽ����̡߳�
��  ����
        LPVOID lpParameter�����ݵĲ�����
����ֵ������Ϊ DWORD ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��8��27�� 9:39:22
*******************************************************************************************************/
DWORD _stdcall CUDPSocket::ReceiveThread(LPVOID lpParameter)
{
    TRACE(_T("CUDPSocket::ReceiveThread\n"));
    UDPSOCKREMOTEINFO* p = (UDPSOCKREMOTEINFO*)lpParameter;
    CString szRemoteIP(p->szRemoteIP);
    UINT uRemotePort = p->uRemotePort;
    int iLen = p->iLen;
    LPVOID buf = new BYTE[iLen];
    memcpy(buf, p->pBuf, iLen);
    CWinsocketexpDlg* m_pParent = (CWinsocketexpDlg*) p->pParent;
    ::SetEvent(*(p->phEvent));

#ifdef _TEST
    char str[4096];
    hostent* host = gethostbyaddr(szRemoteIP, 4, PF_INET);

    char hostname[256];
    int res = gethostname(hostname, sizeof(hostname));
    if (res != 0) {
       printf("Error: %u\n", WSAGetLastError());
       return -1;
    }
    TRACE(_T("%s(%d) : ������:%s\n"), __FILE__, __LINE__, hostname);
    if(host)
    {
        sprintf(str, _T("%s - %s:%d >> %s"), host->h_name, szRemoteIP, uRemotePort,buf);
    }
    else
    {
        sprintf(str, _T("%s:%d >> %s"),szRemoteIP, uRemotePort, buf );
    }
    m_pParent->m_ctrLstRecive.AddString(str);
#endif

    delete []buf;
    return 0;
};

/*******************************************************************************************************
��������SendThread
��  �ܣ������߳�,��ɶ����ݻ����������ݵ�˳��ȷ������
˵  ����1�������������û��Ҫ���͵����ݣ���ѵȴ���ʱ������һ����ʱ�䣬�����̡߳�
        2����������ݣ����ͣ����𶯵ȴ���ʱ������Ϊһ���ط�ʱ�䣨���ط�ʱ����û�յ�ȷ���������ط���
           �ط�ȷ���� OnReceive ��ʵ�֡�
        3�������ʱ����ɾ���Ǽ����е�Զ��������
��  ����
         LPVOID lpParameter���������� SendData ��ָ��
����ֵ������0
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-3
ʱ  �䣺11:05:16
*******************************************************************************************************/
DWORD _stdcall CUDPSocket::SendThread(LPVOID lpParameter)
{
    TRACE(_T("�����߳�CUDPSocket::SendThread����.�߳�ID=%x\n"), ::GetCurrentThreadId());
    SendData* p =(SendData*) lpParameter;
    ASSERT(p);
    LARGE_INTEGER li;
    while(TRUE)
    {
        if(p->m_bThreadEnd)
        {
            TRACE(_T("%s(%d) : �����߳�CUDPSocket::SendThread�˳�.�߳�ID=%x\n"), __FILE__, __LINE__, ::GetCurrentThreadId());
            return 0;
        }
        ::EnterCriticalSection(&p->m_cs);
        if(p->m_pBuf.IsEmpty())
		{
#pragma warning(disable:4307)
            //����Ϊ5���ӱ�ʱ
			li.QuadPart = -1 * (5 * 60 * SECOND);
#pragma warning(default:4307)
            p->m_dwOverTime = 0;
        }
        else
        {
            //����Ϊ5����ٴη���
            li.QuadPart = -5 * SECOND;
            p->m_dwOverTime += 5;
            //��ʱ�����ܶԷ�����δ�������ܽ������ݣ�ɾ�����͵Ǽ����е�Զ������
            if(p->m_dwOverTime > p->m_dwLimitTime)
            {
               POSITION pos = p->m_pParent->m_SendBuffer.GetHeadPosition();
               SendData* psd;
               while(pos)
               {
                   POSITION prePos;
                   prePos = pos;
                   psd = p->m_pParent->m_SendBuffer.GetNext(pos);
                   if(psd->m_szIP == p->m_szIP && psd->m_uPort == p->m_uPort)
                   {
                       UDPSOCKREMOTEINFO info;
                       info.szRemoteIP = p->m_szIP;
                       info.uRemotePort = p->m_uPort;
                       info.pParent = p->m_pParent->m_pParent;
                       if(p->m_pParent->m_OverTimeThread)
                       {
						   p->m_pParent->m_OverTimeThread(&info); //�����û��ĳ�ʱ�¼�������
                       } // ���� if(p->m_pParent->m_OverTimeThread)
                       
                       ::LeaveCriticalSection(&p->m_cs);
                       p->m_pParent->m_SendBuffer.RemoveAt(prePos);
                       delete psd;
                       
                       TRACE(_T("%s(%d) : ��ʱ��ɾ�����������Ǽ��\n"), __FILE__, __LINE__);
                       return 0;
                   } // ���� if(psd->m_szIP == p->m_szIP && psd->m_uPort == p->m_uPort)
               } // ���� while(pos)
            } // ���� if(p->m_dwOverTime > p->m_dwLimitTime)

#ifdef _DEBUG 
            long lNo;
            memcpy(&lNo, p->m_pBuf.GetHead().pBuf, sizeof(long));
            TRACE(_T("%s(%d) : �߳�ID=%x,���е����ݰ��ĸ���=%d, ��ǰ���͵����ݰ����=%d, ���ݴ�С%d, Զ������IP=%s,�˿�=%d\n"), 
				__FILE__, __LINE__,
				::GetCurrentThreadId(), p->m_lNumber, lNo,
				p->m_pBuf.GetHead().iLen, p->m_szIP, p->m_uPort);
#endif

            if(SOCKET_ERROR  == p->m_pParent->SendTo(p->m_pBuf.GetHead().pBuf, p->m_pBuf.GetHead().iLen, p->m_uPort, p->m_szIP))
			{
				if(GetLastError() == WSAEMSGSIZE)
				{
					ASSERT(0); //Ҫ���͵����ݳ��������ݱ�����󳤶�
				} // ���� if(GetLastError() == WSAEMSGSIZE)
                TRACE(_T("%s(%d) : ��������ʧ��\n"), __FILE__, __LINE__);
            }
        }
        ::LeaveCriticalSection(&p->m_cs);
        ::SetWaitableTimer(p->m_hTime, &li, 0, NULL, NULL, FALSE);
        ::WaitForSingleObject(p->m_hTime, INFINITE);
    }

    return 0;
}

/*******************************************************************************************************
��������SendDataTo
��  �ܣ�����һ���̷߳������ݡ�
˵  ����
        1�����Զ�������ѵǼǣ��ҵ���
           1.1�������������û�з������������������߳�
           1.2���ѷ������ݼӵ����Ͷ��в����ء�
           1.3��������������з������ݣ���ѷ������ݼӵ����Ͷ��к󷵻ء�
           �Ǽ����SendBuffer
        2�����Զ������û�еǼǣ��½�һ���Ǽ��
           ����ʼ���Ǽ���ѷ������ݼӵ����Ͷ��з��ء�
           ���������̡߳�
��  ����
         LPVOID pBuf����������
         int iLen���������ݵĳ���
         UINT uRemotePort��Զ�������˿ں�
         CString szRemoteIP��Զ������IP
����ֵ���ɹ�����TRUE��ʧ�ܷ���FALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-3
ʱ  �䣺14:51:32
*******************************************************************************************************/
BOOL CUDPSocket::SendDataTo(LPVOID pBuf, int iLen, UINT uRemotePort, CString szRemoteIP)
{
    ASSERT(pBuf && iLen >= 0);

    //��ʼsizeof(long)�ֽ�Ϊ���ݵ����
    LPVOID p = new BYTE[iLen + sizeof(long)];
    if(NULL == p)
    {
        ASSERT(p);//�����ڴ�ʧ��
        return FALSE;
    }
    BYTE* bp =(BYTE*) p + sizeof(long);
    memcpy((LPVOID)bp, pBuf, iLen);
    
    //�Ǽ�������������
    if(!m_SendBuffer.IsEmpty())
    {
        //���ҵǼ������Ƿ��д�Զ������
        POSITION pos = m_SendBuffer.GetHeadPosition();
        SendData* psd;
        while(pos != NULL)
        {
            psd = m_SendBuffer.GetNext(pos);
            if((psd->m_szIP == szRemoteIP) && (psd->m_uPort == uRemotePort))
            {
                //�Ǽ������д�Զ������
                memcpy(p, &psd->m_lNumber, sizeof(long));//�������ݰ����
                psd->m_lNumber = (psd->m_lNumber == NUMBERMAX) ? 0 : (psd->m_lNumber + 1);
                Data data;
                data.pBuf = p;
                data.iLen = iLen + sizeof(long);
                ::EnterCriticalSection(&psd->m_cs);
                if(psd->m_pBuf.IsEmpty())
                {
                    //���ͻ�������û������
                    //��Ҫ���͵����ݼӵ����ͻ�����                    
                    psd->m_pBuf.AddTail(data);
                    ::LeaveCriticalSection(&psd->m_cs);    
                    //�����������߳�
                    LARGE_INTEGER li;
                    li.QuadPart = -1;
                    ::SetWaitableTimer(psd->m_hTime, &li, 1000000, NULL, NULL, FALSE);
                    return TRUE;
                }
                //���ͻ�������������
                //��Ҫ���͵����ݼӵ����ͻ��������к�                
                psd->m_pBuf.AddTail(data);
                ::LeaveCriticalSection(&psd->m_cs);    
                return TRUE;
            }//if
        }//while(psd)
    }//if(!m_SendBuffer.IsEmpty())    

    //�Ǽ�����û��Զ������
    SendData* psd = new SendData;
    if(psd == NULL)
    {
        ASSERT(psd);
        return FALSE;
    }
    psd->SetParent(this);
    psd->m_szIP = szRemoteIP;
    psd->m_uPort = uRemotePort;
    memcpy(p, (void *)&psd->m_lNumber, sizeof(long));  //�������ݰ����
    psd->m_lNumber = (psd->m_lNumber == NUMBERMAX) ? 0 : (psd->m_lNumber + 1);
    Data data;
    data.pBuf = p;
    data.iLen = iLen + sizeof(long);
    ::EnterCriticalSection(&psd->m_cs);
    psd->m_pBuf.AddTail(data);
    ::LeaveCriticalSection(&psd->m_cs);
    m_SendBuffer.AddTail(psd);
    //����ȴ���ʱ�������������߳�
    LARGE_INTEGER li;
    li.QuadPart = -1;
    ::SetWaitableTimer(psd->m_hTime, &li, 1000000, NULL, NULL, FALSE);
    return TRUE;
}