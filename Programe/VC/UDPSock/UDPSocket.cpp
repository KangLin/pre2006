/*******************************************************************************************************
文件名：UDPSocket.cpp
功  能：基于多线程的,实现UDP数据包的有序、确定的发送、接收。
        实现发送超时没有接到应答包，就结束发送线程。所以当远程主机不存在时，超时将终止发送数据包(2005年7月2日 增加)
问  题：接收数据时，当数据大于 BUFFER_MAX_LEN 时，没有考虑。
用  法：1、建立一个对象 CUDPSocket m_udpSocket;
        2、建立一个接收线程(ReceiveThread)，此线程式格式参照CUDPSocket::ReceiveThread
           注意在此线程中一个要设置事件对象为有信号状态。
           DWORD _stdcall ReceiveThread(LPVOID lpParameter)
           {
                 TRACE(_T("CUDPSocket::ReceiveThread\n"));
                 UDPSOCKREMOTEINFO* p = (UDPSOCKREMOTEINFO*)lpParameter;
                 CString szRemoteIP(p->szRemoteIP); //发送数据的主机地址
                 UINT uRemotePort = p->uRemotePort; //发送数据的主机端口
                 
                 //复制接收的数据
                 int iLen = p->iLen;                //接收数据的长度
                 LPVOID buf = new BYTE[iLen]; 
                 memcpy(buf, p->pBuf, iLen);
                 
                 CWinsocketexpDlg* pParent = (CWinsocketexpDlg*) p->pParent; //转换为父对象
                 ::SetEvent(*(p->phEvent));   //设置事件对象为有信号
                 
                 //对接收的数据进行处理
                 //...........
                 //

                 delete []buf
                 return 0;
           }
        3、如果要处理超时事件的话，就要建立一个超时成员函数。
           格式同上。但参数只有 pParent、szRemoteIP 和 uRemotePort 有意义。其它项没有意义。
        4、初始化对象：m_udpSocket.Init(this, ReceiveThread, uLocatePort, OverTimeThread);
        5、在要发送数据时调用 m_udpSocket.SendDataTo(buf, iLen, szRemoteIP, uRemotePort);
        6、在线程ReceiveThread中处理接收的数据
        7、如果有超时处理函数时，在函数中处理超时事件。
        8、退出时，调用 m_udpSocket.Close();关闭 Socket
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-12-4
时  间：13:48:27
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
函数名：Destroy
功  能：销毁数据,结束时的清除操作
参  数：无
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-3
时  间：14:48:42
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
函数名：Close
功  能：关闭CUDPSocket
参  数：无
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-3
时  间：16:15:11
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
        memcpy(p, &lCloseSocket, sizeof(long)); //设置数据包序号
        Data data;
        data.pBuf = p;
        data.iLen = sizeof(long);
        ::EnterCriticalSection(&psd->m_cs);
        psd->m_pBuf.AddHead(data);
        ::LeaveCriticalSection(&psd->m_cs);    
        //并启动发送线程
        LARGE_INTEGER li;
        li.QuadPart = -1;
        ::SetWaitableTimer(psd->m_hTime, &li, 1000000, NULL, NULL, FALSE);
    }
    Sleep(m_CLoseSleep);
    Destroy();
    CSocket::Close();
}

/*******************************************************************************************************
函数名：Inital
功  能：初始化，在这里建socket、设置父窗口指针、接收处理线程
参  数：
         LPVOID *pParent：父类实例指针
         THREADPROC ReceiveThread：接收数据处理线程。NULL为默认内部处理线程
         UINT nLocatePort：要绑定的端口号
         BOOL bNewThread：是否在接收时启用新的线程处理接收到的数据
         THREADPROC OverTimeThread：超时事件，当发送数据超时时激活。
返回值：成功返回TRUE，否则返回FALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-4
时  间：10:11:44
*******************************************************************************************************/
BOOL CUDPSocket::Inital(LPVOID pParent, THREADPROC ReceiveThread, UINT nLocatePort, BOOL bNewThread, THREADPROC OverTimeThread)
{
    m_pParent = pParent;
    m_bNewThread = bNewThread;
    if(ReceiveThread)
    {
        m_ReceiveThread = ReceiveThread;
    } // 结束 if(ReceiveThread)
       
    m_OverTimeThread = OverTimeThread;
   
    Close();
    if(!Create(nLocatePort, SOCK_DGRAM))
    {
        TRACE(_T("%s(%d) : CUDPSocket建立失败。\n"), __FILE__, __LINE__);
        return FALSE;
    }
    TRACE(_T("%s(%d) : CUDPSocket成功建立。\n"), __FILE__, __LINE__);
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CUDPSocket member functions

/*******************************************************************************************************
函数名：OnReceive
功  能：接收数据
说  明：数据格式：接收数据的前四个字节为长整型的数据包编号，最高位表示是否是确定包（1，为确定包。0，为数据包），
        后面的数据为数据包的编号。
算  法：1、得到数据。
        2、是否是确定包
           2.1、删除发送缓存区中的头(互拆访问)，并重设用时时间为0。
           2.2、启动缓存区中的发送线程
        3、是数据包
           3.1、查找是否有远程主机登记项
                3.1.1、有，接收数据。
                  3.1.1.1、是远程主机退出包。从登记项中删除此远程主机
                  3.1.1.2、是要接收的数据。收序号加一，发应答包，创建接收线程（或调用处理接收数据的函数），
                       注意：以上的顺序不能改变，否则当线程或函数要很长处理时间时，服务器将始终重发，将导致多次调用
                  3.1.1.3、是已接收的数据。只发应答包
                  3.1.1.4、不是要接收的数据，丢弃
                3.1.2、否，建立登记项。
		          3.1.2.1、是远程主机退出包。则退出。
                  3.1.2.2、接收序号在数据包的序号上加一
                          (可能原来已经接收，但由于某种情况程序退出，
                           又进入，所以数据包序号不一定是0)，
						   发应答包，创建接收线程（或调用处理接收数据的函数）。
                  3.1.2.3、创建接收线程
        4、在新的事件线程中复制完数据后，设置事件对象为有信号状态
           ::SetEvent(p->hEvent);
参  数：
         int nErrorCode：错误号
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-3
时  间：19:12:19
*******************************************************************************************************/
void CUDPSocket::OnReceive(int nErrorCode) 
{ 
    UDPSOCKREMOTEINFO remote;

    //1、接收数据
    BYTE buf[BUFFER_MAX_LEN];
    remote.iLen = ReceiveFrom(buf, BUFFER_MAX_LEN, remote.szRemoteIP, remote.uRemotePort);
    if(remote.iLen == SOCKET_ERROR)
    {
        if(GetLastError() == WSAEMSGSIZE)
        {
            //数据被截剪
            ASSERT(0);
        } // 结束 if(GetLastError() == WSAEMSGSIZE)
        TRACE(_T("%s(%d) : CUDPSocket::OnReceive 没接收到数据.\n"), __FILE__, __LINE__);
        //CSocket::OnReceive(nErrorCode);
        return;
    }
    TRACE(_T("%s(%d) : CUDPSocket::OnReceive 收到数据大小:%d.\n"), __FILE__, __LINE__, remote.iLen);
    
    //数据包的序号
    long lNumber;
    memcpy(&lNumber, buf, sizeof(long));

    //2、是确定应答包
    if(lNumber & RESPONSION)
    {
        TRACE(_T("是确定应答包：0x%x\n"), lNumber);
        //查找登记项中是否有此远程主机
        POSITION pos = m_SendBuffer.GetHeadPosition();
        SendData* psd;
        while(pos != NULL)
        {
            psd = m_SendBuffer.GetNext(pos);
			if((psd->m_szIP == remote.szRemoteIP) && (psd->m_uPort == remote.uRemotePort))
            {
                //删除发送缓存区中的头
                ::EnterCriticalSection(&psd->m_cs);    
                TRACE(_T("%s(%d) : 删除发送缓存区中的头,进入临界区\n"), __FILE__, __LINE__);
				if(!psd->m_pBuf.IsEmpty())
                {
                    if(psd->m_pBuf.GetHead().pBuf)//队列是否为空
                    {
                        long lNo;
                        memcpy(&lNo, psd->m_pBuf.GetHead().pBuf, sizeof(long));
                        lNo |= RESPONSION;
                        if(lNo == lNumber)//是当前队列头的应答包
                        {
                            delete []psd->m_pBuf.GetHead().pBuf;
                            psd->m_pBuf.GetHead().pBuf = NULL;
                            psd->m_pBuf.RemoveHead();
                            psd->m_dwOverTime = 0;  //重设用时时间
                            ::LeaveCriticalSection(&psd->m_cs);   
                            TRACE(_T("%s(%d) : 删除发送缓存区中的头,离开临界区\n"), __FILE__, __LINE__);
                            //启动发送线程
                            LARGE_INTEGER li;
                            li.QuadPart = -1;
                            ::SetWaitableTimer(psd->m_hTime, &li, 1, NULL, NULL, FALSE);
                            //CSocket::OnReceive(nErrorCode);
                            return;
                        }//是当前队列头的应答包
                        ::LeaveCriticalSection(&psd->m_cs);    
                        TRACE(_T("%s(%d) : 删除发送缓存区中的头,离开临界区\n"), __FILE__, __LINE__);
                        //CSocket::OnReceive(nErrorCode);
                        return;
                    }//队列不为空
                } // 结束 if(!psd->m_pBuf.IsEmpty())
                ::LeaveCriticalSection(&psd->m_cs);    
                TRACE(_T("%s(%d) : 删除发送缓存区中的头,离开临界区\n"), __FILE__, __LINE__);
                return;
            }// 结束 if((psd->m_szIP == remote.szRemoteIP) && (psd->m_uPort == remote.uRemotePort))
        }//while(psd = m_SendBuffer.GetNext(pos))
        //CSocket::OnReceive(nErrorCode);
        return;
    }//if(lNumber & RESPONSION)

    remote.pBuf = buf + sizeof(long);
    remote.iLen -= sizeof(long);
    remote.pParent = m_pParent;
    remote.phEvent = &m_hEvent;

	//3、是数据包
	//3.1.1、远程主机已在登记项中    
    if(!m_RecAdd.IsEmpty())
    {   //远程主机已在登记项中
        POSITION pos = m_RecAdd.GetHeadPosition();
        int index = -1; //用于删除接收远程主机信息的登记项
        while(pos != NULL)
        {            
            ADDRESS& recadd = m_RecAdd.GetNext(pos);
            index++;
			if((recadd.m_szIP == remote.szRemoteIP) && (recadd.m_uPort == remote.uRemotePort))
            {
				if(CLOSESOCKET == lNumber) //是远程主机退出信号包
                {
                    //发送应答包
                    lNumber |= RESPONSION;
                    SendTo(&lNumber, sizeof(long), remote.uRemotePort, remote.szRemoteIP);
                    TRACE(_T("%s(%d) : 远程主机：%s:%d 退出\n"), __FILE__, __LINE__, remote.szRemoteIP, remote.uRemotePort);
                    //删除接收远程主机信息的登记项
                    m_RecAdd.RemoveAt(m_RecAdd.FindIndex(index));

                    //删除向此远程主机发送登记项
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
                } // 结束 if(CLOSESOCKET == lNumber)

				if(recadd.m_lNumber == lNumber)//是当有要接收的数据包
                {  
                    //更新数据包的序号
                    recadd.m_lNumber = (recadd.m_lNumber == NUMBERMAX) ? 0 : (recadd.m_lNumber + 1);
                    //发送应答包
                    lNumber |= RESPONSION;
                    SendTo(&lNumber, sizeof(long), remote.uRemotePort, remote.szRemoteIP);                     
                    
                    if(m_bNewThread)
                    {
                        TRACE(_T("%s(%d) : 远程主机已在登记项中,UDPSocket启动新的线程处理接收数据\n"), __FILE__, __LINE__);
                        //启动线程
                        ::ResetEvent(m_hEvent);
                        CreateThread(NULL, NULL, m_ReceiveThread, &remote, NULL, NULL);
						::WaitForSingleObject(m_hEvent, INFINITE);//等待用户复制完数据后，设置事件对象为有信号状态
                    }
                    else
                    {
                        TRACE(_T("%s(%d) : 远程主机已在登记项中,UDPSocket调用函数,当前线程ID:%x\n"), __FILE__, __LINE__, ::GetCurrentThreadId());
                        m_ReceiveThread(&remote);
                    }                   
                }//是当有要接收的数据包
                else if(recadd.m_lNumber > lNumber || (lNumber == NUMBERMAX && recadd.m_lNumber == 0))
                {   //是已接收过的数据包，可能是发送端没有收到应答，又重发
                    //发送应答包
                    lNumber |= RESPONSION;
					SendTo(&lNumber, sizeof(long), remote.uRemotePort, remote.szRemoteIP);
                } // 结束 if(recadd.m_lNumber == lNumber)
                
                //CSocket::OnReceive(nErrorCode);
                return;
            } // 结束 if((recadd.m_szIP == remote.szRemoteIP) && (recadd.m_uPort == remote.uRemotePort))
        }//while(psd)
    }//if(!m_RecAdd.IsEmpty())

	//3.1.2、远程主机不在登记项中
    if(CLOSESOCKET == lNumber) //是远程主机退出信号包
    {
        //CSocket::OnReceive(nErrorCode);
        return;
    }

    ADDRESS recadd;
    recadd.m_szIP = remote.szRemoteIP;
    recadd.m_uPort = remote.uRemotePort;
    //if(recadd.m_lNumber == lNumber)//本程序在发送时退出后又进入，则数据包的序号不一定是0，因为已经发送了一些数据
    {          
        //更新数据包的序号
        recadd.m_lNumber = (lNumber == NUMBERMAX) ? 0 : (lNumber + 1);
        m_RecAdd.AddTail(recadd);//在登记项中添加远程主机
        //发送应答包
        lNumber |= RESPONSION;
        SendTo(&lNumber, sizeof(long), remote.uRemotePort, remote.szRemoteIP); 

        if(m_bNewThread)
        {
            TRACE(_T("%s(%d) : UDPSocket启动新的线程处理接收数据\n"), __FILE__, __LINE__);
            //启动线程
            ::ResetEvent(m_hEvent);
            CreateThread(NULL, NULL, m_ReceiveThread, &remote, NULL, NULL);
			::WaitForSingleObject(m_hEvent, INFINITE);
        }
        else
        {
            TRACE(_T("%s(%d) : UDPSocket调用函数,当前线程ID:%x\n"), __FILE__, __LINE__, ::GetCurrentThreadId());
            m_ReceiveThread(&remote);
        }
        
    }

    //CSocket::OnReceive(nErrorCode);
}

/*******************************************************************************************************
函数名：ReceiveThread
描  述：默认的接收线程。
参  数：
        LPVOID lpParameter：传递的参数。
返回值：类型为 DWORD 。
版  本：1.0.0.1
作  者：康  林
时  间：2005年8月27日 9:39:22
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
    TRACE(_T("%s(%d) : 主机名:%s\n"), __FILE__, __LINE__, hostname);
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
函数名：SendThread
功  能：发送线程,完成对数据缓存区中数据的顺序、确定发送
说  明：1、如果缓存区中没有要发送的数据，则把等待定时器设置一个长时间，挂起线程。
        2、如果有数据，则发送，并起动等待定时器设置为一个重发时间（在重发时间内没收到确定包，就重发）
           重发确定在 OnReceive 中实现。
        3、如果超时，则删除登记项中的远程主机。
参  数：
         LPVOID lpParameter：发送数据 SendData 的指针
返回值：返回0
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-3
时  间：11:05:16
*******************************************************************************************************/
DWORD _stdcall CUDPSocket::SendThread(LPVOID lpParameter)
{
    TRACE(_T("发送线程CUDPSocket::SendThread启动.线程ID=%x\n"), ::GetCurrentThreadId());
    SendData* p =(SendData*) lpParameter;
    ASSERT(p);
    LARGE_INTEGER li;
    while(TRUE)
    {
        if(p->m_bThreadEnd)
        {
            TRACE(_T("%s(%d) : 发送线程CUDPSocket::SendThread退出.线程ID=%x\n"), __FILE__, __LINE__, ::GetCurrentThreadId());
            return 0;
        }
        ::EnterCriticalSection(&p->m_cs);
        if(p->m_pBuf.IsEmpty())
		{
#pragma warning(disable:4307)
            //设置为5分钟报时
			li.QuadPart = -1 * (5 * 60 * SECOND);
#pragma warning(default:4307)
            p->m_dwOverTime = 0;
        }
        else
        {
            //设置为5秒后再次发送
            li.QuadPart = -5 * SECOND;
            p->m_dwOverTime += 5;
            //超时，可能对方主机未开，不能接收数据，删除发送登记项中的远程主机
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
						   p->m_pParent->m_OverTimeThread(&info); //调用用户的超时事件处理函数
                       } // 结束 if(p->m_pParent->m_OverTimeThread)
                       
                       ::LeaveCriticalSection(&p->m_cs);
                       p->m_pParent->m_SendBuffer.RemoveAt(prePos);
                       delete psd;
                       
                       TRACE(_T("%s(%d) : 超时，删除发送主机登记项。\n"), __FILE__, __LINE__);
                       return 0;
                   } // 结束 if(psd->m_szIP == p->m_szIP && psd->m_uPort == p->m_uPort)
               } // 结束 while(pos)
            } // 结束 if(p->m_dwOverTime > p->m_dwLimitTime)

#ifdef _DEBUG 
            long lNo;
            memcpy(&lNo, p->m_pBuf.GetHead().pBuf, sizeof(long));
            TRACE(_T("%s(%d) : 线程ID=%x,已有的数据包的个数=%d, 当前发送的数据包序号=%d, 数据大小%d, 远程主机IP=%s,端口=%d\n"), 
				__FILE__, __LINE__,
				::GetCurrentThreadId(), p->m_lNumber, lNo,
				p->m_pBuf.GetHead().iLen, p->m_szIP, p->m_uPort);
#endif

            if(SOCKET_ERROR  == p->m_pParent->SendTo(p->m_pBuf.GetHead().pBuf, p->m_pBuf.GetHead().iLen, p->m_uPort, p->m_szIP))
			{
				if(GetLastError() == WSAEMSGSIZE)
				{
					ASSERT(0); //要发送的数据超出了数据报的最大长度
				} // 结束 if(GetLastError() == WSAEMSGSIZE)
                TRACE(_T("%s(%d) : 发送数据失败\n"), __FILE__, __LINE__);
            }
        }
        ::LeaveCriticalSection(&p->m_cs);
        ::SetWaitableTimer(p->m_hTime, &li, 0, NULL, NULL, FALSE);
        ::WaitForSingleObject(p->m_hTime, INFINITE);
    }

    return 0;
}

/*******************************************************************************************************
函数名：SendDataTo
功  能：启动一个线程发送数据。
说  明：
        1、如果远程主机已登记，找到它
           1.1、如果缓存区中没有发送数据则启动发送线程
           1.2、把发送数据加到发送队列并返回。
           1.3、如果缓存区中有发送数据，则把发送数据加到发送队列后返回。
           登记项见SendBuffer
        2、如果远程主机没有登记，新建一个登记项。
           并初始化登记项，把发送数据加到发送队列返回。
           启动发送线程。
参  数：
         LPVOID pBuf：发送数据
         int iLen：发送数据的长度
         UINT uRemotePort：远程主机端口号
         CString szRemoteIP：远程主机IP
返回值：成功返回TRUE，失败返回FALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-3
时  间：14:51:32
*******************************************************************************************************/
BOOL CUDPSocket::SendDataTo(LPVOID pBuf, int iLen, UINT uRemotePort, CString szRemoteIP)
{
    ASSERT(pBuf && iLen >= 0);

    //开始sizeof(long)字节为数据的序号
    LPVOID p = new BYTE[iLen + sizeof(long)];
    if(NULL == p)
    {
        ASSERT(p);//分配内存失败
        return FALSE;
    }
    BYTE* bp =(BYTE*) p + sizeof(long);
    memcpy((LPVOID)bp, pBuf, iLen);
    
    //登记项中已有主机
    if(!m_SendBuffer.IsEmpty())
    {
        //查找登记项中是否有此远程主机
        POSITION pos = m_SendBuffer.GetHeadPosition();
        SendData* psd;
        while(pos != NULL)
        {
            psd = m_SendBuffer.GetNext(pos);
            if((psd->m_szIP == szRemoteIP) && (psd->m_uPort == uRemotePort))
            {
                //登记项中有此远程主机
                memcpy(p, &psd->m_lNumber, sizeof(long));//设置数据包序号
                psd->m_lNumber = (psd->m_lNumber == NUMBERMAX) ? 0 : (psd->m_lNumber + 1);
                Data data;
                data.pBuf = p;
                data.iLen = iLen + sizeof(long);
                ::EnterCriticalSection(&psd->m_cs);
                if(psd->m_pBuf.IsEmpty())
                {
                    //发送缓存区中没有数据
                    //把要发送的数据加到发送缓存区                    
                    psd->m_pBuf.AddTail(data);
                    ::LeaveCriticalSection(&psd->m_cs);    
                    //并启动发送线程
                    LARGE_INTEGER li;
                    li.QuadPart = -1;
                    ::SetWaitableTimer(psd->m_hTime, &li, 1000000, NULL, NULL, FALSE);
                    return TRUE;
                }
                //发送缓存区中有数据
                //把要发送的数据加到发送缓存区队列后                
                psd->m_pBuf.AddTail(data);
                ::LeaveCriticalSection(&psd->m_cs);    
                return TRUE;
            }//if
        }//while(psd)
    }//if(!m_SendBuffer.IsEmpty())    

    //登记项中没有远程主机
    SendData* psd = new SendData;
    if(psd == NULL)
    {
        ASSERT(psd);
        return FALSE;
    }
    psd->SetParent(this);
    psd->m_szIP = szRemoteIP;
    psd->m_uPort = uRemotePort;
    memcpy(p, (void *)&psd->m_lNumber, sizeof(long));  //设置数据包序号
    psd->m_lNumber = (psd->m_lNumber == NUMBERMAX) ? 0 : (psd->m_lNumber + 1);
    Data data;
    data.pBuf = p;
    data.iLen = iLen + sizeof(long);
    ::EnterCriticalSection(&psd->m_cs);
    psd->m_pBuf.AddTail(data);
    ::LeaveCriticalSection(&psd->m_cs);
    m_SendBuffer.AddTail(psd);
    //重设等待定时器，启动发送线程
    LARGE_INTEGER li;
    li.QuadPart = -1;
    ::SetWaitableTimer(psd->m_hTime, &li, 1000000, NULL, NULL, FALSE);
    return TRUE;
}