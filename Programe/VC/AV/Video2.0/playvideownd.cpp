/*******************************************************************************************************
文件名：PlayVideoWnd.cpp
功  能：显示视频窗口实现文件

增  加；单独显示视频数据类 CDisplayWnd
用  法：1、先在容器类中建立此类的对象指针 
		   CDisplayWnd* m_DisplayWnd;
        2、再容器类中重载容器类的 OnCreate 函数
		3、在容器类的 OnCreate 函数中 
		   m_DisplayWnd = new CDisplayWnd；
		   m_DisplayWnd->Create(WS_CHILD|WS_VISIBLE,rect,this,NULL);
		4、调用成员函数 Display 中显示视频数据(已压缩).
		5、重载容器类的 OnDestroy() 函数，在其中加入
		   //发送关闭窗口消息,这是必须的,以保正窗口的正常关闭。
		   ::SendMessage(m_DisplayWnd->GetSaftHwnd(), WM_CLOSE, NULL, NULL);
		   //因为这里仅调用析构函数
		   delete m_DisplayWnd;
作  者：康  林
版  本：2.0.0.1
日  期：2004-11-17
时  间：14:39:10

用  法：
        1、先在容器类中建立此类的对象指针 
		   CPlayVideoWnd* m_PlaypVidWnd;
        2、再容器类中重载容器类的 OnCreate 函数
		3、在容器类的 OnCreate 函数中 
		   m_PlayVidWnd = new CPlayVideoWnd；
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisplayWnd

BEGIN_MESSAGE_MAP(CDisplayWnd, CWnd)
	//{{AFX_MSG_MAP(CDisplayWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDisplayWnd::CDisplayWnd()
{
	//设置自己的位图结构		
	m_bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_bmpInfo.bmiHeader.biWidth = IMAGE_WIDTH;
	m_bmpInfo.bmiHeader.biHeight = IMAGE_HEIGHT;
	m_bmpInfo.bmiHeader.biPlanes = 1;
	m_bmpInfo.bmiHeader.biBitCount = 24;
	m_bmpInfo.bmiHeader.biCompression = 0;
	m_bmpInfo.bmiHeader.biSizeImage = 0;
	m_bmpInfo.bmiHeader.biXPelsPerMeter = 0;
	m_bmpInfo.bmiHeader.biYPelsPerMeter = 0;
	m_bmpInfo.bmiHeader.biClrUsed = 0;
	m_bmpInfo.bmiHeader.biClrImportant = 0;

	m_pOut = new BYTE[76032];
	m_dwOutSize = 0;

	m_hdib = NULL;
	m_hdc = NULL;
}

CDisplayWnd::~CDisplayWnd()
{
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

	delete []m_pOut;	
}

BOOL CDisplayWnd::Create(const RECT& rect, CWnd* pParentWnd, DWORD dwStyle, UINT nID, CCreateContext* pContext) 
{
	return CWnd::Create(NULL, _T("视频显示-作者：康林"), dwStyle, rect, pParentWnd, nID, pContext);
}

/////////////////////////////////////////////////////////////////////////////
// CDisplayWnd message handlers
int CDisplayWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
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

void CDisplayWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	m_wndWidth = cx;      
	m_wndHeight = cy;		
}

/*******************************************************************************************************
函数名：Display
功  能：显示视频数据
参  数：
         LPVOID pData：视频数据
         DWORD iSize：视频数据的大小
返回值：无
作  者：康  林
版  本：2.0.0.1
日  期：2004-11-17
时  间：14:40:41
*******************************************************************************************************/
void CDisplayWnd::Display(LPVOID pData, DWORD iSize)
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

/////////////////////////////////////////////////////////////////////////////
// CPlayVideoWnd

BEGIN_MESSAGE_MAP(CPlayVideoWnd, CWnd)
	//{{AFX_MSG_MAP(CPlayVideoWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CPlayVideoWnd::CPlayVideoWnd()
{
	m_VideoCapture = NULL;

	/*if(m_pOut)
		delete []m_pOut;
	m_pOut = new BYTE[2048];
	*/
}

/////////////////////////////////////////////////////////////////////////////
// CPlayVideoWnd message handlers

BOOL CPlayVideoWnd::Create(const RECT& rect, CWnd* pParentWnd, DWORD dwStyle, UINT nID, CCreateContext* pContext) 
{
	return CWnd::Create(NULL, _T("视频显示-作者：康林"), dwStyle, rect, pParentWnd, nID, pContext);
}

/*******************************************************************************************************
函数名：OnCreate
功  能：在此初始化捕获设备
参  数：
         LPCREATESTRUCT lpCreateStruct：
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-17
时  间：13:19:36
*******************************************************************************************************/
int CPlayVideoWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDisplayWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_VideoCapture = new CVideoCapture;
	
	if(m_VideoCapture)
	{
		m_VideoCapture->Initialize();
		m_VideoCapture->SetDisplayWindow(this);
		m_bmpInfo = m_VideoCapture->m_bmpInfo;
	}	
	
	return 0;
}

void CPlayVideoWnd::OnSize(UINT nType, int cx, int cy) 
{
	CDisplayWnd::OnSize(nType, cx, cy);	
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

	if(m_VideoCapture)
	{
		m_VideoCapture->Destroy();
	}

	delete m_VideoCapture;
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
	if(m_VideoCapture)
	{
		return m_VideoCapture->StartCapture();
	}
	return TRUE;
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
	if(m_VideoCapture)
	{
		retVal = m_VideoCapture->StopCapture();
	}

	return retVal;
}

/*******************************************************************************************************
函数名：Display
功  能：在窗口中显示给定的数据,并在此对视频进行压缩和发送
参  数：
         LPVOID pData：视频数据
         DWORD iSize：视频数据的大小
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-11
时  间：19:13:31
*******************************************************************************************************/
void CPlayVideoWnd::Display(LPVOID pData, DWORD iSize)
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
	((CTestDlg*)AfxGetMainWnd())->m_DisplayWnd->Display(m_pOut, m_dwOutSize);
	//*/
#endif	
}

