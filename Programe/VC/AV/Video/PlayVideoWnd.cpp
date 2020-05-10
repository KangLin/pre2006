/*******************************************************************************************************
文件名：PlayVideoWnd.cpp
功  能：显示视频窗口实现文件
用  法：
        1、先在容器类中建立此类的对象指针 m_PlaypVidWnd
        2、再容器类中重载容器类的 OnCreate 函数
		3、在容器类的 OnCreate 函数中 
		   m_PlayVidWnd = new CPlayVideoWnd；
		   
		   //如果只显示视频数据，而不需要捕获视频,加入下面一句：
		   //SetOnlyPlay();

		   m_PlayVidWnd->Create(WS_CHILD|WS_VISIBLE,rect,this,NULL);

		4、在成员函数 Display 中加入对视频帧数据的其它处理代码。例如：视频帧数据的发送。
		   如果只显示视频数据,调用Display传递视频数据的的指针和长度
		   这里已经对数据进行了压缩,不过你可以加入自己的压缩程序.
		5、在开始捕获的地方加入 m_PlayVidWnd->StartCapture();
		6、在要停止捕获操作的地方加入 m_PlayVidWnd->StopCapture();
		7、重载容器类的 OnDestroy() 函数，在其中加入
		   //发送关闭窗口消息,这是必须的,以保正窗口的正常关闭。
		   ::SendMessage(m_PlayVidWnd->GetSaftHwnd(), WM_CLOSE, NULL, NULL);
		   //因为这里仅调用析构函数
		   delete m_DispVidWnd;
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-11-3
时  间：17:11:32
*******************************************************************************************************/

#include "stdafx.h"
#include "playVideoWnd.h"

//测试头文件
#ifdef _TEST
#include "test\test.h"
#include "test\TestDlg.h"
#endif

//中国象棋头文件
#ifdef _CCHESS
#include "..\..\中国象棋\中国象棋view.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CPlayVideoWnd, CWnd)
	//{{AFX_MSG_MAP(CPlayVideoWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayVideoWnd

CPlayVideoWnd::CPlayVideoWnd()
{
	m_bOnlyPlay = FALSE;
	m_VideoCapture = NULL;

	//设置自己的位图结构		
	m_bmpInfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	m_bmpInfo.bmiHeader.biWidth=IMAGE_WIDTH;
	m_bmpInfo.bmiHeader.biHeight=IMAGE_HEIGHT;
	m_bmpInfo.bmiHeader.biPlanes=1;
	m_bmpInfo.bmiHeader.biBitCount=24;
	m_bmpInfo.bmiHeader.biCompression=0;
	m_bmpInfo.bmiHeader.biSizeImage=0;
	m_bmpInfo.bmiHeader.biXPelsPerMeter=0;
	m_bmpInfo.bmiHeader.biYPelsPerMeter=0;
	m_bmpInfo.bmiHeader.biClrUsed=0;
	m_bmpInfo.bmiHeader.biClrImportant=0;

	//设置显示缓存大小
	if(!m_bOnlyPlay)
		m_pOut = new BYTE[76032];
	else
		m_pOut = new BYTE[3000];
	m_dwOutSize = 0;

#ifdef _CCHESS
	bConnect = FALSE;
#endif

}

/////////////////////////////////////////////////////////////////////////////
// CPlayVideoWnd message handlers

BOOL CPlayVideoWnd::Create(const RECT& rect, CWnd* pParentWnd, DWORD dwStyle, UINT nID, CCreateContext* pContext) 
{
	return CWnd::Create(NULL, _T("视频显示-作者：康林"), dwStyle, rect, pParentWnd, nID, pContext);
}

void CPlayVideoWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_wndWidth = cx;      
	m_wndHeight = cy;	
}

/*******************************************************************************************************
函数名：SetOnlyPlay
功  能：设置此窗口类只显示视频数据，不捕获视频
注  意：这个函数只能用在Create之前，设置，以后就不能设置了。
参  数：
         BOOL bOnlyPlay：如果为TRUE，只显示数据，
		                     为FALSE，同时还捕获视频数据
返回值：调用前的状态。
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-11
时  间：19:14:49
*******************************************************************************************************/
BOOL CPlayVideoWnd::SetOnlyPlay(BOOL bOnlyPlay)
{
	BOOL r = m_bOnlyPlay;
	m_bOnlyPlay = bOnlyPlay;
	return r;
}

/*******************************************************************************************************
函数名：OnCreate
功  能：初始化
参  数：
         LPCREATESTRUCT lpCreateStruct：
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-11
时  间：19:14:18
*******************************************************************************************************/
int CPlayVideoWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if(!m_bOnlyPlay) //初始化视频捕获
	{
		m_VideoCapture = new CVideoCapture;

		if(m_VideoCapture)
		{
			m_VideoCapture->Initialize();
			m_VideoCapture->SetDisplayWindow(this);
			m_bmpInfo = m_VideoCapture->m_bmpInfo;
		}	
	}
	
	//得到显示窗口的 HDC
	m_hdc = this->GetDC()->m_hDC;
    
	//为画图初始化 DIB ...
	m_hdib = ::DrawDibOpen();//打开DrawDib库
	if(m_hdib != NULL)
	{	 
		::DrawDibBegin(m_hdib,
					   m_hdc,
					   -1,				// 不进行缩放
					   -1,				// 不进行缩放
					   &m_bmpInfo.bmiHeader,
					   IMAGE_WIDTH,         //图像的宽度 
					   IMAGE_HEIGHT,        //图像的高度 
					   0				
					   );
	
	}

	return 0;
}

CPlayVideoWnd::~CPlayVideoWnd()
{
	/*******************************************************************************************************
	注意：
    因为在这没有调用
    CWnd::OnDestroy();
	所以在窗口类中调用
	delete m_DispVidWnd;
	前，先调用：
	::SendMessage(m_PlayVidWnd->GetSaftHwnd(), WM_CLOSE, NULL, NULL);
	来正常关闭窗口。
    *******************************************************************************************************/
	if(m_hdib != NULL)
	{
		if(!::DrawDibEnd(m_hdib))
		{
			TRACE(_T("DrawDibEnd失败!\n"));
		}
	    if(!::DrawDibClose(m_hdib))
		{
			TRACE(_T("DrawDibClose失败!\n"));
		}
	}
	
	if(m_VideoCapture)
	{
		m_VideoCapture->StopCapture();
	}

	delete m_VideoCapture;
	delete []m_pOut;

#ifdef _CCHESS
	m_DSocket.Close();
#endif
}

/*******************************************************************************************************
函数名：StartCapture
功  能：开始捕获
参  数：无
返回值：成功返回TRUE，否则返回FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-11
时  间：19:11:59
*******************************************************************************************************/
BOOL CPlayVideoWnd::StartCapture()
{
	if(m_VideoCapture && !m_bOnlyPlay)
	{
		return m_VideoCapture->StartCapture();
	}
	return true;
}

/*******************************************************************************************************
函数名：StopCapture
功  能：停止捕获
参  数：无
返回值：成功返回TRUE，否则返回FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-11
时  间：19:12:03
*******************************************************************************************************/
BOOL CPlayVideoWnd::StopCapture()
{
	BOOL retVal;
	if(m_VideoCapture && !m_bOnlyPlay)
	{
		retVal = m_VideoCapture->StopCapture();
	}

	return retVal;
}

/*******************************************************************************************************
函数名：Display
功  能：在窗口中显示给定的数据,并在此对视频进行压缩和发送
参  数：
         BYTE *pData：视频数据
         DWORD iSize：视频数据的大小
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-11
时  间：19:13:31
*******************************************************************************************************/
void CPlayVideoWnd::Display(BYTE *pData, DWORD iSize)
{
	if(m_bOnlyPlay)
	{
		if(!m_Compressor.SeqDecompress(pData, iSize, m_pOut, (DWORD*)&m_dwOutSize))
		{
			TRACE(_T("Display:解压缩失败\n"));
		}
		TRACE(_T("解压缩后的大小为%d\n"), m_dwOutSize);
		::DrawDibDraw(m_hdib,
			m_hdc,
			0,		// dest : left pos
			0,		// dest : top pos
			m_wndWidth,//-1,					 // don't zoom x
			m_wndHeight,//-1,					 // don't zoom y
			&m_bmpInfo.bmiHeader,			 // bmp header info
			m_pOut,					 // bmp data
			0,					 // src :left
			0,					 // src :top
			IMAGE_WIDTH,				 // src : width
			IMAGE_HEIGHT,				 // src : height
			0//DDF_SAME_DRAW			 // use prev params....
			);
	}
	else
	{
		TRACE(_T("捕获的一帧数据大小为%d\n"), iSize);
		::DrawDibDraw(m_hdib,
			m_hdc,
			0,		// dest : left pos
			0,		// dest : top pos
			m_wndWidth,//-1,					 // don't zoom x
			m_wndHeight,//-1,					 // don't zoom y
			&m_bmpInfo.bmiHeader,			 // bmp header info
			pData,					 // bmp data
			0,					 // src :left
			0,					 // src :top
			IMAGE_WIDTH,				 // src : width
			IMAGE_HEIGHT,				 // src : height
			DDF_SAME_DRAW			 // use prev params....
			);
		
		//TODO:在此可加入其它对捕获流数据操作的代码(例如：压缩数据)……		
		if(!m_Compressor.SeqCompress(pData, iSize, m_pOut, (DWORD*)&m_dwOutSize))
		{
			TRACE(_T("Display压缩失败\n"));
			return ;
		}
		TRACE(_T("捕获的一帧数据压缩后的大小为%d\n"), m_dwOutSize);

#ifdef _TEST
		//*例子:
		((CTestDlg*)AfxGetMainWnd())->m_onlywnd.Display(m_pOut, m_dwOutSize);
		//*/
#endif

#ifdef _CCHESS
		//*中国象棋
		try
		{
		
		
			CFrameWnd* mainwnd = (CFrameWnd*)AfxGetMainWnd();
			CChessView* view =(CChessView*) mainwnd->GetActiveView();
			view->m_pSocket->SendTo(m_pOut, m_dwOutSize, 6791, "127.0.0.1");
		/*	
			tagData* p = (tagData*) m_pOut;
			p->DataType = CDSocket::VideoData;
			p->DataLength = m_dwOutSize;
			p->lpData = m_pOut + sizeof(tagData);
			
			//if(!m_Compressor.SeqCompress(pData, iSize, m_pOut, (DWORD*)&m_dwOutSize))
			if(!m_Compressor.SeqCompress(pData, iSize, p->lpData, (DWORD*)&(p->DataLength)))
			{
				TRACE(_T("Display压缩失败\n"));
				return;
			}
			TRACE(_T("捕获的一帧数据压缩后的大小为%d\n"), p->DataLength);

			if(view->m_pSocket->SendTo(p, p->DataLength + sizeof(tagData), view->m_dwRemotePort, view->m_szRemoteIP)
				== SOCKET_ERROR)
			{
				TRACE(_T("发送数据出错.错误号:%d\n"), ::GetLastError());
			}
			
			if(bConnect)
				m_DSocket.SendTo(m_pOut, m_dwOutSize, m_uRemotePort, m_szRemoteName);*/
		}
		catch(...)
		{
			TRACE(_T("发送视频数据异常\n"));
		}
		//*/
#endif
	}
}

#ifdef _CCHESS
BOOL CPlayVideoWnd::CreateDSocket(CString szRemoteName, UINT uPort, UINT uRemotePort)
{
	if(!m_DSocket.CreateSock(uPort, CDSocket::VideoData))
	{
		TRACE(_T("视频DSocket建立失败.\n"));
		return FALSE;
	}
	m_uLocatPort = uPort;
	m_uRemotePort = uRemotePort;
	m_szRemoteName = szRemoteName;
	bConnect = TRUE;
	return TRUE;
}
#endif