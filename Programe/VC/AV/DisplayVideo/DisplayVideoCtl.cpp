/*******************************************************************************************************
文件名：DisplayVideoCtl.cpp
功  能：显示压缩的视频数据
用  法：调用方法 Display 显示压缩的视频数据
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-11-17
时  间：22:30:26
*******************************************************************************************************/

#include "stdafx.h"
#include "DisplayVideo.h"
#include "DisplayVideoCtl.h"
#include "DisplayVideoPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CDisplayVideoCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CDisplayVideoCtrl, COleControl)
	//{{AFX_MSG_MAP(CDisplayVideoCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CDisplayVideoCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CDisplayVideoCtrl)
	DISP_FUNCTION(CDisplayVideoCtrl, "Display", Display, VT_EMPTY, VTS_PBSTR VTS_I4)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CDisplayVideoCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CDisplayVideoCtrl, COleControl)
	//{{AFX_EVENT_MAP(CDisplayVideoCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CDisplayVideoCtrl, 1)
	PROPPAGEID(CDisplayVideoPropPage::guid)
END_PROPPAGEIDS(CDisplayVideoCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CDisplayVideoCtrl, "DISPLAYVIDEO.DisplayVideoCtrl.1",
	0xafd9ec81, 0x5ced, 0x4d82, 0xba, 0x94, 0x81, 0x90, 0x86, 0xc4, 0xd5, 0x69)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CDisplayVideoCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DDisplayVideo =
		{ 0xba0b24d5, 0xbf89, 0x44c5, { 0xa3, 0xf5, 0x35, 0xc4, 0xc6, 0x2b, 0x7a, 0x28 } };
const IID BASED_CODE IID_DDisplayVideoEvents =
		{ 0x58bbd3bb, 0xc66d, 0x4a9d, { 0x8b, 0x35, 0x64, 0xba, 0x35, 0x60, 0xb5, 0x46 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwDisplayVideoOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CDisplayVideoCtrl, IDS_DISPLAYVIDEO, _dwDisplayVideoOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CDisplayVideoCtrl::CDisplayVideoCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CDisplayVideoCtrl

BOOL CDisplayVideoCtrl::CDisplayVideoCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_DISPLAYVIDEO,
			IDB_DISPLAYVIDEO,
			afxRegApartmentThreading,
			_dwDisplayVideoOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayVideoCtrl::CDisplayVideoCtrl - Constructor

CDisplayVideoCtrl::CDisplayVideoCtrl()
{
	InitializeIIDs(&IID_DDisplayVideo, &IID_DDisplayVideoEvents);

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
	m_bDraw = FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayVideoCtrl::~CDisplayVideoCtrl - Destructor

CDisplayVideoCtrl::~CDisplayVideoCtrl()
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

/////////////////////////////////////////////////////////////////////////////
// CDisplayVideoCtrl::OnDraw - Drawing function

void CDisplayVideoCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	if(!m_bDraw)
		pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayVideoCtrl::DoPropExchange - Persistence support

void CDisplayVideoCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CDisplayVideoCtrl::OnResetState - Reset control to default state

void CDisplayVideoCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayVideoCtrl::AboutBox - Display an "About" box to the user

void CDisplayVideoCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_DISPLAYVIDEO);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayVideoCtrl message handlers

int CDisplayVideoCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//得到显示窗口的 HDC
	m_hdc = this->GetDC()->m_hDC;
    
	//为画图初始化 DIB ...
	m_hdib = ::DrawDibOpen();//打开DrawDib库
	if(m_hdib != NULL)
	{	 
		::DrawDibBegin(m_hdib,
			m_hdc,
            m_wndWidth,  //-1,                   // don't zoom x
            m_wndHeight,  //-1,                  // don't zoom y
			&m_bmpInfo.bmiHeader,
			IMAGE_WIDTH,         //图像的宽度 
			IMAGE_HEIGHT,        //图像的高度 
			0				
			);
		
	}
	
	return 0;
}

void CDisplayVideoCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);
	
	m_wndWidth = cx;      
	m_wndHeight = cy;	
}


/*******************************************************************************************************
函数名：Display
功  能：显示压缩的视频数据
参  数：
         BSTR FAR* lpData：压缩的视频数据
         long dwSize：压缩的视频数据的大小
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-17
时  间：22:31:14
*******************************************************************************************************/
void CDisplayVideoCtrl::Display(BSTR FAR* lpData, long dwSize) 
{
	if(!m_Compressor.SeqDecompress((LPVOID)lpData, dwSize, m_pOut, (DWORD*)&m_dwOutSize))
	{
		TRACE(_T("Display:解压缩失败\n"));
	}
	TRACE(_T("解压缩后的大小为%d\n"), m_dwOutSize);
	m_bDraw = TRUE;
	::DrawDibDraw(m_hdib,
		m_hdc,
        0,                     // dest : left pos
        0,                     // dest : top pos
        m_wndWidth,            //-1,                   // don't zoom x
        m_wndHeight,           //-1,                  // don't zoom y
        &m_bmpInfo.bmiHeader,  // bmp header info
        m_pOut,                // bmp data
        0,                     // src :left
        0,                     // src :top
        IMAGE_WIDTH,           // src : width
        IMAGE_HEIGHT,          // src : height
		0//DDF_SAME_DRAW 			 // use prev params....
		);
	m_bDraw = FALSE;
}
