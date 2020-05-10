/*******************************************************************************************************
�ļ�����VideoCtl.cpp
��  �ܣ�������Ƶ����ʾ
��  �����¼�DisplayVideo�����������Ƶ����
        ���÷��� StartCapture ��ʼ����
		���÷��� StopCapture ֹͣ����
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-11-17
ʱ  �䣺22:20:49
*******************************************************************************************************/

#include "stdafx.h"
#include "VideoCtrl.h"
#include "VideoCtl.h"
#include "VideoPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CVideoCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CVideoCtrl, COleControl)
	//{{AFX_MSG_MAP(CVideoCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CVideoCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CVideoCtrl)
	DISP_FUNCTION(CVideoCtrl, "StartCapture", StartCapture, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CVideoCtrl, "StopCapture", StopCapture, VT_BOOL, VTS_NONE)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CVideoCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CVideoCtrl, COleControl)
	//{{AFX_EVENT_MAP(CVideoCtrl)
	EVENT_CUSTOM("DisplayVideo", FireDisplayVideo, VTS_PBSTR  VTS_I4)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CVideoCtrl, 1)
	PROPPAGEID(CVideoPropPage::guid)
END_PROPPAGEIDS(CVideoCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CVideoCtrl, "VIDEOCTRL.VideoCtrl.1",
	0x135c6036, 0x4af4, 0x4c68, 0xba, 0x2b, 0x3b, 0xb0, 0xc3, 0x1f, 0x33, 0xaa)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CVideoCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DVideo =
		{ 0x4772e532, 0x7177, 0x483a, { 0xa7, 0x22, 0x1, 0x1a, 0xc4, 0xd3, 0x13, 0x61 } };
const IID BASED_CODE IID_DVideoEvents =
		{ 0x133a6674, 0xcf5f, 0x48d6, { 0xb3, 0x9d, 0x1, 0xfd, 0x3e, 0x7f, 0xf0, 0xe3 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwVideoOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CVideoCtrl, IDS_VIDEO, _dwVideoOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CVideoCtrl::CVideoCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CVideoCtrl

BOOL CVideoCtrl::CVideoCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_VIDEO,
			IDB_VIDEO,
			afxRegApartmentThreading,
			_dwVideoOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CVideoCtrl::CVideoCtrl - Constructor

CVideoCtrl::CVideoCtrl()
{
	InitializeIIDs(&IID_DVideo, &IID_DVideoEvents);

	m_VideoCapture = NULL;
	m_bCapturing = FALSE;

	//�����Լ���λͼ�ṹ		
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

	m_pOut = new BYTE[3000];
	m_dwOutSize = 0;

	m_hdib = NULL;
	m_hdc = NULL;
}


/////////////////////////////////////////////////////////////////////////////
// CVideoCtrl::~CVideoCtrl - Destructor

CVideoCtrl::~CVideoCtrl()
{		
	if(m_hdib != NULL)
	{
		if(!::DrawDibEnd(m_hdib))
		{
			TRACE(_T("DrawDibEndʧ��!\n"));
		}
	    if(!::DrawDibClose(m_hdib))
		{
			TRACE(_T("DrawDibCloseʧ��!\n"));
		}
	}

	if(m_VideoCapture)
	{
		m_VideoCapture->Destroy();
	}

	delete m_VideoCapture;

	delete []m_pOut;
}


/////////////////////////////////////////////////////////////////////////////
// CVideoCtrl::OnDraw - Drawing function

void CVideoCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	if(!m_bCapturing)
		pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
}


/////////////////////////////////////////////////////////////////////////////
// CVideoCtrl::DoPropExchange - Persistence support

void CVideoCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));  
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CVideoCtrl::OnResetState - Reset control to default state

void CVideoCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CVideoCtrl::AboutBox - Display an "About" box to the user

void CVideoCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_VIDEO);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CVideoCtrl message handlers

/*******************************************************************************************************
��������StartCapture
��  �ܣ���ʼ������Ƶ����
��  ������
����ֵ���ɹ�����TRUE,���򷵻�FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-17
ʱ  �䣺22:22:49
*******************************************************************************************************/
BOOL CVideoCtrl::StartCapture() 
{
	if(m_VideoCapture)
	{
		m_bCapturing = TRUE;
		return m_VideoCapture->StartCapture();
	}
	return TRUE;
}

/*******************************************************************************************************
��������StopCapture
��  �ܣ�ֹͣ������Ƶ����
��  ������
����ֵ���ɹ�����TRUE,���򷵻�FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-17
ʱ  �䣺22:23:17
*******************************************************************************************************/
BOOL CVideoCtrl::StopCapture() 
{
	BOOL retVal;
	if(m_VideoCapture)
	{
		m_bCapturing = FALSE;
		retVal = m_VideoCapture->StopCapture();
	}

	return retVal;
}

int CVideoCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_VideoCapture = new CVideoCapture;
	
	if(m_VideoCapture)
	{
		m_VideoCapture->Initialize();
		m_VideoCapture->SetDisplayWindow(this);
		m_bmpInfo = m_VideoCapture->m_bmpInfo;
	}	
	
	//�õ���ʾ���ڵ� HDC
	m_hdc = this->GetDC()->m_hDC;
    
	//Ϊ��ͼ��ʼ�� DIB ...
	m_hdib = ::DrawDibOpen();//��DrawDib��
	if(m_hdib != NULL)
	{	 
		::DrawDibBegin(m_hdib,
					   m_hdc,
					   -1,				// ����������
					   -1,				// ����������
					   &m_bmpInfo.bmiHeader,
					   IMAGE_WIDTH,         //ͼ��Ŀ�� 
					   IMAGE_HEIGHT,        //ͼ��ĸ߶� 
					   0				
					   );
	
	}
	
	return 0;
}

void CVideoCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);
	
	m_wndWidth = cx;      
	m_wndHeight = cy;	
}

/*******************************************************************************************************
��������Display
��  �ܣ���Ƶ��ʾ,�������¼�
��  ����
         LPVOID lpData����Ƶ����
         DWORD dwSize����Ƶ���ݵĴ�С
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-17
ʱ  �䣺22:22:05
*******************************************************************************************************/
void CVideoCtrl::Display(LPVOID lpData, DWORD dwSize)
{		
	TRACE(_T("�����һ֡���ݴ�СΪ%d\n"), dwSize);
	::DrawDibDraw(m_hdib,
		m_hdc,
		0,		// dest : left pos
		0,		// dest : top pos
		m_wndWidth,//-1,					 // don't zoom x
		m_wndHeight,//-1,					 // don't zoom y
		&m_bmpInfo.bmiHeader,			 // bmp header info
		lpData,					 // bmp data
		0,					 // src :left
		0,					 // src :top
		IMAGE_WIDTH,				 // src : width
		IMAGE_HEIGHT,				 // src : height
		DDF_SAME_DRAW			 // use prev params....
		);
	
	//TODO:�ڴ˿ɼ��������Բ��������ݲ����Ĵ���(���磺ѹ������)����		
	if(!m_Compressor.SeqCompress(lpData, dwSize, m_pOut, (DWORD*)&m_dwOutSize))
	{
		TRACE(_T("Displayѹ��ʧ��\n"));
		return ;
	}
	TRACE(_T("�����һ֡����ѹ����Ĵ�СΪ%d\n"), m_dwOutSize);
	try
	{
		FireDisplayVideo((BSTR*)m_pOut, m_dwOutSize);
	}
	catch(...)
	{
		TRACE(_T("�¼�FireDisplayVideo����.\n"));
	};
}
