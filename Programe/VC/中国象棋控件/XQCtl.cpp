// XQCtl.cpp : Implementation of the CXQCtrl ActiveX Control class.

#include "stdafx.h"
#include "�й�����ؼ�.h"
#include "XQCtl.h"
#include "XQPpg.h"
#include ".\xqctl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CXQCtrl, COleControl)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CXQCtrl, COleControl)
	//{{AFX_MSG_MAP(CXQCtrl)
	ON_WM_SIZE()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CXQCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CXQCtrl)
	DISP_PROPERTY_NOTIFY(CXQCtrl, "QiPangColor", m_QiPangColor, OnQiPangColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY(CXQCtrl, "TiShiBoxColor", m_TiShiBoxColor, OnTiShiBoxColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY(CXQCtrl, "QiPangLayout", m_QiPang, OnQiPangLayoutChanged, VT_I4)
	DISP_PROPERTY_EX(CXQCtrl, "QiPangPicture", GetQiPangPicture, SetQiPangPicture, VT_PICTURE)
	DISP_PROPERTY_EX(CXQCtrl, "StartSide", GetStartSide, SetStartSide, VT_I4)
	DISP_PROPERTY_EX(CXQCtrl, "CurrentSide", GetCurrentSide, SetCurrentSide, VT_I2)
	DISP_FUNCTION(CXQCtrl, "NextStep", NextStep, VT_I4, VTS_NONE)
	DISP_FUNCTION(CXQCtrl, "PreviouStep", PreviouStep, VT_I4, VTS_NONE)
	DISP_FUNCTION(CXQCtrl, "ReStart", ReStart, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CXQCtrl, "SaveChess", SaveChess, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CXQCtrl, "LoadChess", LoadChess, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CXQCtrl, "LoadChessStart", LoadChessStart, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CXQCtrl, "QiPangInterconvert", QiPangInterconvert, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CXQCtrl, "Walk", Walk, VT_BOOL, VTS_I2 VTS_I2)
	DISP_FUNCTION(CXQCtrl, "InterConvertCoordinate", InterConvertCoordinate, VT_EMPTY, VTS_I2 VTS_I2 VTS_PI2 VTS_PI2)
	DISP_STOCKPROP_ENABLED()
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CXQCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CXQCtrl, COleControl)
	//{{AFX_EVENT_MAP(CXQCtrl)
	EVENT_CUSTOM("MoveChess", FireMoveChess, VTS_I2  VTS_I2  VTS_I4)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CXQCtrl, 1)
	PROPPAGEID(CXQPropPage::guid)
END_PROPPAGEIDS(CXQCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CXQCtrl, "CChess.XQCtrl.1",
	0x71ad322, 0x22ba, 0x45bf, 0x9e, 0x1f, 0x15, 0x4e, 0xfa, 0xf4, 0xe4, 0x2b)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CXQCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DXQ =
		{ 0xe64cbbbf, 0x1b35, 0x4334, { 0xb9, 0x7a, 0xf0, 0x42, 0x7, 0xf3, 0x83, 0xd8 } };
const IID BASED_CODE IID_DXQEvents =
		{ 0xd15120c1, 0x9b3c, 0x4e56, { 0x8f, 0x32, 0xd0, 0xac, 0xb6, 0xfc, 0x7b, 0x89 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwXQOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CXQCtrl, IDS_XQ, _dwXQOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CXQCtrl::DoPropExchange - Persistence support

void CXQCtrl::DoPropExchange(CPropExchange* pPX)
{
	TRACE(_T("DoPropExchange-Start\n"));
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
    PX_Color(pPX, _T("QiPangColor"), m_QiPangColor, RGB(0, 0, 0));
	PX_Color(pPX, _T("TiShiBoxColor"), m_TiShiBoxColor, RGB(0, 255, 0));

	PX_Picture(pPX, _T("QiPangPicture"), m_QiPangPictureHolder);
	GetCBitmapFromCPictureHolder(&m_QiPangPictureHolder, &m_QiPangPicture);

	PX_Long(pPX, _T("StartSide"), (long&)m_WalkState, BlackReadly);
    PX_Long(pPX, _T("QiPangLayout"), m_QiPang, TopRedAndBottomBlack);
	TRACE(_T("DoPropExchange-End\n"));
}

/////////////////////////////////////////////////////////////////////////////
// CXQCtrl::CXQCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CXQCtrl

BOOL CXQCtrl::CXQCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_XQ,
			IDB_XQ,
			afxRegApartmentThreading,
			_dwXQOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CXQCtrl::CXQCtrl - Constructor

CXQCtrl::CXQCtrl()
{
	InitializeIIDs(&IID_DXQ, &IID_DXQEvents);
    
	// TODO: Initialize your control's instance data here.
	
	if(m_QiPangPicture.GetSafeHandle() == NULL)
	{
		m_QiPangPicture.LoadBitmap(IDB_QIPANG);
	}

	if(m_RedShuai.GetSafeHandle() == NULL)
	{
		m_RedShuai.LoadBitmap(IDB_RSHUAI);
	}

    if(m_RedShi.GetSafeHandle() == NULL)
	{
		m_RedShi.LoadBitmap(IDB_RSHI);
	}

	if(m_RedXiang.GetSafeHandle() == NULL)
	{
		m_RedXiang.LoadBitmap(IDB_RXIANG);
	}

	if(m_RedMa.GetSafeHandle() == NULL)
	{
		m_RedMa.LoadBitmap(IDB_RMA);
	}

	if(m_RedChe.GetSafeHandle() == NULL)
	{
		m_RedChe.LoadBitmap(IDB_RCHE);
	}

	if(m_RedPao.GetSafeHandle() == NULL)
	{
		m_RedPao.LoadBitmap(IDB_RPAO);
	}

	if(m_RedBing.GetSafeHandle() == NULL)
	{
		m_RedBing.LoadBitmap(IDB_RBING);
	}


	if(m_BlackShuai.GetSafeHandle() == NULL)
	{
		m_BlackShuai.LoadBitmap(IDB_BSHUAI);
	}

    if(m_BlackShi.GetSafeHandle() == NULL)
	{
		m_BlackShi.LoadBitmap(IDB_BSHI);
	}

	if(m_BlackXiang.GetSafeHandle() == NULL)
	{
		m_BlackXiang.LoadBitmap(IDB_BXIANG);
	}

	if(m_BlackMa.GetSafeHandle() == NULL)
	{
		m_BlackMa.LoadBitmap(IDB_BMA);
	}

	if(m_BlackChe.GetSafeHandle() == NULL)
	{
		m_BlackChe.LoadBitmap(IDB_BCHE);
	}

	if(m_BlackPao.GetSafeHandle() == NULL)
	{
		m_BlackPao.LoadBitmap(IDB_BPAO);
	}

	if(m_BlackBing.GetSafeHandle() == NULL)
	{
		m_BlackBing.LoadBitmap(IDB_BBING);
	}

	m_pGoRule = new CGoRule;
}


/////////////////////////////////////////////////////////////////////////////
// CXQCtrl::~CXQCtrl - Destructor

CXQCtrl::~CXQCtrl()
{
	// TODO: Cleanup your control's instance data here.
	delete m_pGoRule;
}

int CXQCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	TRACE(_T("CXQCtrl::OnCreate.��ǰ���̺߳�:%x\n"), ::GetCurrentThreadId());

	SetInitialSize(100, 110);//���ÿؼ���ʼ���Ĵ�С	

	ReStart();	

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CXQCtrl::OnResetState - Reset control to default state

void CXQCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CXQCtrl::AboutBox - Display an "About" box to the user

void CXQCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_XQ);
	dlgAbout.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CXQCtrl::OnDraw - Drawing function

void CXQCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	DrawQiPang(pdc, rcBounds);   //������
}

void CXQCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);

	if(cx > cy)
	{
		SetControlSize(cy * 10 / 11, cy);
		m_QiPangDistance = cy / 11;
	}
	else
	{
		SetControlSize(cx, cx * 11 / 10);
		m_QiPangDistance = cx / 10;
	}

	//TRACE("OnSize=%d,%d,distance=%f\n", cx,cy,m_QiPangDistance);
	
	m_QiPangStartX = m_QiPangDistance;
	m_QiPangStartY = m_QiPangDistance;
}

void CXQCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int i, j;
	ConvertCoordinate(&point.x, &point.y, &i, &j);
	TRACE(_T("CXQCtrl::OnLButtonUp�ĵ�ǰ�߳�:%x\n"), ::GetCurrentThreadId());
	if(WalkChess(i, j))
	{
	  
	}
	
	COleControl::OnLButtonUp(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
// CXQCtrl message handlers

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//��������� ===�й���������=== �ĺ�����
//

/*******************************************************************************************************
��������OnQiPangColorChanged
��  �ܣ�������ɫ����ͨ�溯��
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-8-18
ʱ  �䣺15:51:24
*******************************************************************************************************/
void CXQCtrl::OnQiPangColorChanged() 
{
	SetModifiedFlag();
	//�ػ�ؼ�
	InvalidateControl();
}

void CXQCtrl::OnTiShiBoxColorChanged() 
{
	SetModifiedFlag();
	//�ػ�ؼ�
	InvalidateControl();
}

LPPICTUREDISP CXQCtrl::GetQiPangPicture() 
{
	// TODO: Add your property handler here

	return m_QiPangPictureHolder.GetPictureDispatch();
}

void CXQCtrl::SetQiPangPicture(LPPICTUREDISP newValue) 
{
	// TODO: Add your property handler here

	m_QiPangPictureHolder.SetPictureDispatch(newValue);

	GetCBitmapFromCPictureHolder(&m_QiPangPictureHolder, &m_QiPangPicture);

	//�����޸ı�־
	SetModifiedFlag();
	//�ػ�ؼ�
	InvalidateControl();
}

short CXQCtrl::GetCurrentSide() 
{
	return m_WalkState;
}

void CXQCtrl::SetCurrentSide(short nNewValue) 
{
	ENUM_WalkState val;
	if(nNewValue < 4 && nNewValue >= 0)
		val = (ENUM_WalkState)nNewValue;
	else
		val = BlackReadly;
	if(val == RedWalked)
		val = RedReadly;
	if(val == BlackWalked)
        val = BlackReadly;
	m_WalkState = val;
	SetModifiedFlag();
	InvalidateControl();
}

/*******************************************************************************************************
��������SetStartSide
��  �ܣ�˭�����塣
��  ����
         long nNewValue�����߷�
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-2
ʱ  �䣺12:55:52
*******************************************************************************************************/
void CXQCtrl::SetStartSide(long nNewValue) 
{
    //if(m_WalkState == RedWalked || m_WalkState == BlackWalked)
	//	return;

	ENUM_WalkState val;
	if(nNewValue < 4 && nNewValue >= 0)
		val = (ENUM_WalkState)nNewValue;
	else
		val = BlackReadly;
	if(val == RedWalked)
		val = RedReadly;
	if(val == BlackWalked)
        val = BlackReadly;
	m_WalkState = val;
	m_FileHead.iStartSide = m_WalkState;

	SetModifiedFlag();
	//�ػ�ؼ�
	InvalidateControl();
}

/*******************************************************************************************************
��������GetStartSide
��  �ܣ��õ���ʼ��
��  ������
����ֵ����ʼ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-2
ʱ  �䣺13:05:09
*******************************************************************************************************/
long CXQCtrl::GetStartSide() 
{
	return m_FileHead.iStartSide;
}

/*******************************************************************************************************
��������OnQiPangLayoutChanged
��  �ܣ����̲���
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-30
ʱ  �䣺18:02:10
*******************************************************************************************************/
void CXQCtrl::OnQiPangLayoutChanged() 
{
	SetModifiedFlag();
	Inital();
	//�ػ�ؼ�
	InvalidateControl();
}

//
//��������� ===�й���������=== �ĺ�����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//��������� ===����=== ���ܵĺ�����
//

/*******************************************************************************************************
��������TransparentBlt2
��  �ܣ���͸��ͼ
��  ����
         HDC hdcDest��       Ŀ��DC
         int nXOriginDest��Ŀ��Xƫ��
         int nYOriginDest��Ŀ��Yƫ��
         int nWidthDest��Ŀ����
         int nHeightDest��Ŀ��߶�
         HDC hdcSrc��ԴDC
         int nXOriginSrc��ԴX���
         int nYOriginSrc��ԴY���
         int nWidthSrc��Դ���
         int nHeightSrc��Դ�߶�
         UINT crTransparent��͸��ɫ,COLORREF����
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-9-1
ʱ  �䣺19:50:00
*******************************************************************************************************/
void TransparentBlt2( HDC hdcDest,      // Ŀ��DC
					 int nXOriginDest,   // Ŀ��Xƫ��
					 int nYOriginDest,   // Ŀ��Yƫ��
					 int nWidthDest,     // Ŀ����
					 int nHeightDest,    // Ŀ��߶�
					 HDC hdcSrc,         // ԴDC
					 int nXOriginSrc,    // ԴX���
					 int nYOriginSrc,    // ԴY���
					 int nWidthSrc,      // Դ���
					 int nHeightSrc,     // Դ�߶�
					 UINT crTransparent  // ͸��ɫ,COLORREF����
					 )
{
	HBITMAP hOldImageBMP, hImageBMP = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);	// ��������λͼ
	HBITMAP hOldMaskBMP, hMaskBMP = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);			// ������ɫ����λͼ
	HDC		hImageDC = CreateCompatibleDC(hdcDest);
	HDC		hMaskDC = CreateCompatibleDC(hdcDest);
	hOldImageBMP = (HBITMAP)SelectObject(hImageDC, hImageBMP);
	hOldMaskBMP = (HBITMAP)SelectObject(hMaskDC, hMaskBMP);
	
	// ��ԴDC�е�λͼ��������ʱDC��
	if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
		BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, SRCCOPY);
	else
		StretchBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, 
		hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, SRCCOPY);
	
	// ����͸��ɫ
	SetBkColor(hImageDC, crTransparent);

	// ����͸������Ϊ��ɫ����������Ϊ��ɫ������λͼ
	BitBlt(hMaskDC, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCCOPY);
	
	// ����͸������Ϊ��ɫ���������򱣳ֲ����λͼ
	SetBkColor(hImageDC, RGB(0,0,0));
	SetTextColor(hImageDC, RGB(255,255,255));
	BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

	// ͸�����ֱ�����Ļ���䣬�������ֱ�ɺ�ɫ
	SetBkColor(hdcDest,RGB(0xff,0xff,0xff));
	SetTextColor(hdcDest,RGB(0,0,0));
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);
	
	// "��"����,��������Ч��
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCPAINT);
	
	SelectObject(hImageDC, hOldImageBMP);
	DeleteDC(hImageDC);
	SelectObject(hMaskDC, hOldMaskBMP);
	DeleteDC(hMaskDC);
	DeleteObject(hImageBMP);
	DeleteObject(hMaskBMP);
	
}

/*******************************************************************************************************
��������GetQiZiSide
��  �ܣ��õ������Ǻ���,���Ǻ���
��  ����
         ENUM_QiZi qz��Ҫר�ϵ�����
����ֵ�����غ��廹�Ǻ��������
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-9-26
ʱ  �䣺12:10:36
*******************************************************************************************************/
ENUM_QiZi GetQiZiSide(ENUM_QiZi qz)
{
	if(qz > NoQiZi)
		return RQi;
	if(qz < NoQiZi)
		return BQi;
	//if(qz = NoQiZi)
		return NoQiZi;
}

/*******************************************************************************************************
��������PromptSound
��  �ܣ���������
˵  ����1���ڡ�����->����->link->����/�⡱�м���winmm.lib 
        2������ͷ�ļ� #include <mmsystem.h>
��  ����
         LPCTSTR ID���������ַ���־
����ֵ������ɹ����� true,���򷵻� false
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-9-1
ʱ  �䣺20:47:29
*******************************************************************************************************/
BOOL CXQCtrl::PromptSound(LPCTSTR ID)
{
	if(NULL != ID)
	{
		HINSTANCE hInstance = AfxGetInstanceHandle();
		HRSRC hr = FindResource(hInstance, ID, _T("WAVE"));
		HGLOBAL hg = LoadResource(hInstance, hr);
		LPCTSTR lp=(LPCTSTR)LockResource(hg);
		::sndPlaySound(lp, SND_MEMORY | SND_ASYNC);
		FreeResource(hg);
	}
	else
	{
		Beep(1000, 20);
	}
	return true;
}

/*******************************************************************************************************
��������QiZiBianMa
��  �ܣ����ӱ����
��  ����
         int *i�����̺�����[0-8]
         int *j������������[0-9]
         ENUM_QiZi *QZ������
         int *Code�����ӱ���
         ENUM_BianMa��ö�ٳ�����BianMa:����(Ĭ��ֵ)��JieMa�����룩
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-9-2
ʱ  �䣺7:36:32
*******************************************************************************************************/
int CXQCtrl::QiZiBianMa(int *i, int *j, ENUM_QiZi *QZ, int *Code, ENUM_BianMa bianma)
{
	switch(bianma)
	{
	case BianMa:
		int val;
		if(*QZ != NoQiZi)
		{
			val = sig(*QZ) * (*i + *j * 10 + abs(*QZ) * 100);
		}
		else
		{
			val = *i + *j * 10;
		}
		*Code = val;
		return val;
		break;
	case JieMa:
		*QZ =(ENUM_QiZi) (*Code / 100);
		TRACE(_T("CODE=%d,QZ=%d\n"), *Code, *QZ);
        int v;
		v = abs(*Code) % 100;
		*j = v / 10;
		*i = v % 10;
		return 0;
		break;
	}
	return 0;
}

/*******************************************************************************************************
��������ConvertCoordinate
��  �ܣ�����ת��
��  ����
         long *x���豸������
         long *y���豸������
         int *i�����̺�����[0,8]
         int *j������������[0,9]
         ENUM_ConvertCoordinate eCC��ת����ʽ 
		                             XYToIJ:���豸����ת������������(Ĭ��ֵ)
									 IJToXY:����������ת�����豸����
����ֵ��������ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-8-24
ʱ  �䣺15:01:37
*******************************************************************************************************/
BOOL CXQCtrl::ConvertCoordinate(long *x, long *y, int *i, int *j, ENUM_ConvertCoordinate eCC)
{
	switch(eCC)
	{
	case XYToIJ:
		*i = (*x - m_QiPangStartX + m_QiPangDistance / 2) / m_QiPangDistance;
		*j = (*y - m_QiPangStartY + m_QiPangDistance / 2) / m_QiPangDistance;
		break;		
	case IJToXY:
         *x = m_QiPangStartX + *i * m_QiPangDistance;
	     *y = m_QiPangStartY + *j * m_QiPangDistance;
		break;
	}
	return true;
}

/*******************************************************************************************************
��������GetCBitmapFromCPictureHolder
��  �ܣ���CPictureHolder�õ�CBitmap
��  ����
         CPictureHolder *ph��
         CBitmap *pb��
����ֵ���ɹ����� true;����,���� false��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-8-18
ʱ  �䣺21:23:01
*******************************************************************************************************/
BOOL CXQCtrl::GetCBitmapFromCPictureHolder(CPictureHolder *ph, CBitmap *pb)
{
	ASSERT(ph != NULL && pb != NULL);

	// if picture is a bitmap
	if (PICTYPE_BITMAP == ph->GetType())
	{
		HBITMAP hBitmap = NULL;

		// get handle of the bitmap
		ph->m_pPict->get_Handle((OLE_HANDLE FAR *) &hBitmap);
		if(hBitmap != NULL) 
		{
			if(pb->GetSafeHandle() != NULL)
				pb->Detach();
			pb->Attach(hBitmap);
			return true;
		}	
	}
	return false;
}

//
//��������� ===����=== ���ܵĺ�����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//��������� ===�й�������洦��=== �ĺ�����
//

/*******************************************************************************************************
��������DrawQiPang
��  �ܣ�������
��  ����
         CDC *pdc���豸������
         CRect rcBounds���ؼ�����(�����߽�)
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-8-18
ʱ  �䣺17:10:23
*******************************************************************************************************/
void CXQCtrl::DrawQiPang(CDC *pdc, CRect rcBounds)
{
	ASSERT(pdc != NULL);

	//����ͼƬ
	BITMAP bitmap;
	m_QiPangPicture.GetBitmap(&bitmap);

	CDC psdc;
	psdc.CreateCompatibleDC(pdc);
	psdc.SelectObject(&m_QiPangPicture);

	pdc->StretchBlt(0, 0, rcBounds.Width(), rcBounds.Height(), 
		&psdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		
	psdc.DeleteDC();

	int i, j;
	for(i = 0; i < 9; i++) //�ݸ�
	{
		if (i == 0 || i == 8)
		{
			CPen Pen, *oldPen;
			Pen.CreatePen(PS_SOLID, 2, m_QiPangColor);
			oldPen = (CPen*)pdc->SelectObject(&Pen);

			pdc->MoveTo(m_QiPangStartX + i * m_QiPangDistance,
			            m_QiPangStartY);
			pdc->LineTo(m_QiPangStartX + i * m_QiPangDistance, 
			            m_QiPangStartY + 9 * m_QiPangDistance);

			pdc->SelectObject(&oldPen);
		}
		else
		{
			CPen Pen, *oldPen;
			Pen.CreatePen(PS_SOLID, 1, m_QiPangColor);
			oldPen = (CPen*)pdc->SelectObject(&Pen);

			pdc->MoveTo(m_QiPangStartX + i * m_QiPangDistance,
			            m_QiPangStartY);
			pdc->LineTo(m_QiPangStartX + i * m_QiPangDistance, 
			            m_QiPangStartY + 4 * m_QiPangDistance);

		    pdc->MoveTo(m_QiPangStartX + i * m_QiPangDistance,
			            m_QiPangStartY + 5 * m_QiPangDistance);
		    pdc->LineTo(m_QiPangStartX + i * m_QiPangDistance, 
			            m_QiPangStartY + 9 * m_QiPangDistance);
			
			pdc->SelectObject(&oldPen);
		}
	}

	for(i = 0; i < 10; i++)  //���
	{
		CPen Pen, *oldPen;
		if (i == 0 || i == 9)
		{
			Pen.CreatePen(PS_SOLID, 2, m_QiPangColor);
			oldPen = (CPen*)pdc->SelectObject(&Pen);
		}
		else
		{
			Pen.CreatePen(PS_SOLID, 1, m_QiPangColor);
			oldPen = (CPen*)pdc->SelectObject(&Pen);
		}


		pdc->MoveTo(m_QiPangStartX ,
			        m_QiPangStartY + i * m_QiPangDistance);
		pdc->LineTo(m_QiPangStartX + 8 * m_QiPangDistance, 
			        m_QiPangStartY + i * m_QiPangDistance);
	
		pdc->SelectObject(&oldPen);
	}

	//�Ź�
	CPen Pen, *oldPen;
	Pen.CreatePen(PS_SOLID, 1, m_QiPangColor);
	oldPen = (CPen*)pdc->SelectObject(&Pen);

	pdc->MoveTo(m_QiPangStartX + 3 * m_QiPangDistance,
		        m_QiPangStartY);
	pdc->LineTo(m_QiPangStartX + 5 * m_QiPangDistance,
		        m_QiPangStartY + 2 * m_QiPangDistance);

	pdc->MoveTo(m_QiPangStartX + 5 * m_QiPangDistance,
		        m_QiPangStartY);
	pdc->LineTo(m_QiPangStartX + 3 * m_QiPangDistance,
		        m_QiPangStartY + 2 * m_QiPangDistance);

    pdc->MoveTo(m_QiPangStartX + 3 * m_QiPangDistance,
		        m_QiPangStartY + 7 * m_QiPangDistance);
	pdc->LineTo(m_QiPangStartX + 5 * m_QiPangDistance,
		        m_QiPangStartY + 9 * m_QiPangDistance);

	pdc->MoveTo(m_QiPangStartX + 5 * m_QiPangDistance,
		        m_QiPangStartY + 7 * m_QiPangDistance);
	pdc->LineTo(m_QiPangStartX + 3 * m_QiPangDistance,
		        m_QiPangStartY + 9 * m_QiPangDistance);

	pdc->SelectObject(&oldPen);

	//��λ
	DrawXinWei(pdc, 1, 2);
	DrawXinWei(pdc, 7, 2);
    DrawXinWei(pdc, 1, 7);
	DrawXinWei(pdc, 7, 7);
	DrawXinWei(pdc, 0, 3, Right_XinWei);
	DrawXinWei(pdc, 2, 3);
	DrawXinWei(pdc, 4, 3);
	DrawXinWei(pdc, 6, 3);
	DrawXinWei(pdc, 8, 3, Left_XinWei);
    DrawXinWei(pdc, 0, 6, Right_XinWei);
	DrawXinWei(pdc, 2, 6);
	DrawXinWei(pdc, 4, 6);
	DrawXinWei(pdc, 6, 6);
	DrawXinWei(pdc, 8, 6, Left_XinWei);

	//���Ӻ���
	CBitmap bmp;
	bmp.LoadBitmap(IDB_CHU);  //��
	DrawPicture(pdc, 7, 4, &bmp, true);
	bmp.Detach();
	bmp.LoadBitmap(IDB_HE);   //��
	DrawPicture(pdc, 6, 4, &bmp, true);
    bmp.Detach();
	bmp.LoadBitmap(IDB_HAN);  //��
	DrawPicture(pdc, 1, 4, &bmp, true);
	bmp.Detach();
	bmp.LoadBitmap(IDB_JIE);  //��
	DrawPicture(pdc, 2, 4, &bmp, true);
    bmp.Detach();
	bmp.LoadBitmap(IDB_KL);   //KL
	DrawPicture(pdc, 4, 4, &bmp, true);

    //������
    for(i = 0; i < 9; i++)
		for(j = 0; j < 10; j++)
		{
			DrawQiZi(pdc, i, j, m_ChessBoard[i][j]);
		}

	//��ʾ��ʾ��
	CPoint point(-1, -1);
	if(m_TiShiBoxPostion.p1 != point)
		DrawTiShiBox(pdc, m_TiShiBoxPostion.p1);
	if(m_TiShiBoxPostion.p2 != point)
		DrawTiShiBox(pdc, m_TiShiBoxPostion.p2);

}

/*******************************************************************************************************
��������DrawXinWei
��  �ܣ�����λ
��  ����
         CDC *pdc���豸������
         int i����λ�ĺ�����[0-8]
         int j����λ��������[0-9]
         ENUM_XINWEI xinwei������λ��ȡ����ֵ��֮һ:
		                     XinWei:ȫ��(Ĭ��ֵ), 
							 Left_XinWei:����ߵ���λ
							 Right_XinWei:���ұߵ���λ
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-8-18
ʱ  �䣺17:56:58
*******************************************************************************************************/
void CXQCtrl::DrawXinWei(CDC *pdc, int i, int j, ENUM_XINWEI xinwei)
{
	int d, ds;
	long x, y;

	d = m_QiPangDistance * 4 / 10;
	ds = m_QiPangDistance * 2 / 10;

	/*x = m_QiPangStartX + i * m_QiPangDistance;
	y = m_QiPangStartY + j * m_QiPangDistance;
    */
	ConvertCoordinate(&x, &y, &i, &j, IJToXY);

	CPen Pen, *oldPen;
	Pen.CreatePen(PS_SOLID, 1, m_QiPangColor);
	oldPen = (CPen*)pdc->SelectObject(&Pen);
	
	if(xinwei != Left_XinWei)			
	{
		pdc->MoveTo(x + ds,
			y + ds);
		pdc->LineTo(x + d,
			y + ds);
		
		pdc->MoveTo(x + ds,
			y - ds);
		pdc->LineTo(x + d,
			y - ds);
		
		pdc->MoveTo(x + ds,
			y + ds);
		pdc->LineTo(x + ds,
			y + d);

		pdc->MoveTo(x + ds,
			y - ds);
		pdc->LineTo(x + ds,
			y - d);
	}

	if(xinwei != Right_XinWei)			
	{
		pdc->MoveTo(x - ds,
			y - ds);
		pdc->LineTo(x - ds,
			y - d);
		
		pdc->MoveTo(x - ds,
			y + ds);
		pdc->LineTo(x - ds,
			y + d);	
		
		pdc->MoveTo(x - ds,
			y + ds);
		pdc->LineTo(x - d,
			y + ds);
		
		pdc->MoveTo(x - ds,
			y - ds);
		pdc->LineTo(x - d,
			y - ds);
	}
	pdc->SelectObject(&oldPen);
}

/*******************************************************************************************************
��������DrawTiShiBox
��  �ܣ�����ʾ��
��  ����
         int i�����̺�����[0-8]
         int j������������[0-9]
����ֵ���ɹ����� true,���򷵻� false
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�04-9-2
ʱ  �䣺21:01:23
*******************************************************************************************************/
BOOL CXQCtrl::DrawTiShiBox(CDC *pdc, int i, int j)
{
//	CClientDC dc(this);
	ASSERT(pdc != NULL);
	long m_X, m_Y, m_L = m_QiPangDistance / 2;
	CPen pen, *oldpen;
	pen.CreatePen(PS_SOLID, 2, m_TiShiBoxColor);
	oldpen = (CPen*)pdc->SelectObject(&pen);
	
	ConvertCoordinate(&m_X, &m_Y, &i, &j, IJToXY);
	pdc->MoveTo(m_X - m_L, m_Y - m_L);
	pdc->LineTo(m_X - m_L, m_Y - m_L / 2);
	
	pdc->MoveTo(m_X - m_L, m_Y - m_L);
	pdc->LineTo(m_X - m_L / 2, m_Y - m_L);

	pdc->MoveTo(m_X + m_L, m_Y + m_L);
	pdc->LineTo(m_X + m_L, m_Y + m_L / 2);
	
	pdc->MoveTo(m_X + m_L, m_Y + m_L);
	pdc->LineTo(m_X + m_L / 2, m_Y + m_L);

	pdc->MoveTo(m_X - m_L, m_Y + m_L);
	pdc->LineTo(m_X - m_L, m_Y + m_L / 2);
	
	pdc->MoveTo(m_X - m_L, m_Y + m_L);
	pdc->LineTo(m_X - m_L / 2, m_Y + m_L);

	pdc->MoveTo(m_X + m_L, m_Y - m_L);
	pdc->LineTo(m_X + m_L, m_Y - m_L / 2);
	
	pdc->MoveTo(m_X + m_L, m_Y - m_L);
	pdc->LineTo(m_X + m_L / 2, m_Y - m_L);


    pdc->SelectObject(oldpen);
	return true;
}

/*******************************************************************************************************
��������DrawTiShiBox
��  �ܣ�����ʾ��
��  ����
         POINT p����ʾ��λ��
����ֵ���ɹ����� true,���򷵻� false
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-9-26
ʱ  �䣺10:55:03
*******************************************************************************************************/
BOOL CXQCtrl::DrawTiShiBox(CDC *pdc, CPoint p)
{
	ASSERT(pdc != NULL);
	return DrawTiShiBox(pdc, p.x, p.y);
}

/*******************************************************************************************************
��������DrawQiZi
��  �ܣ�������
��  ����
         int i�����Ӻ�����[0-8]
         int j������������[0-9]
         ENUM_QiZi eQiZi������
����ֵ������ɹ����� true,���򷵻� false
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-9-1
ʱ  �䣺19:47:24
*******************************************************************************************************/
BOOL CXQCtrl::DrawQiZi(CDC *pdc, int i, int j, ENUM_QiZi eQiZi)
{
	ASSERT(pdc != NULL);

    CBitmap *m_QiZi = NULL;
	
#pragma warning( disable : 4806 )

	switch(eQiZi)
	{
	case RShuai:
		m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_RedShuai : &m_BlackShuai;
		break;
	case RShi:
		m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_RedShi : &m_BlackShi;
		break;
	case RXiang:
		m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ?&m_RedXiang : &m_BlackXiang;
        break;
	case RMa:
		m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_RedMa : &m_BlackMa;
       	break;
	case RChe:
		m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_RedChe : &m_BlackChe;
        break;
	case RPao:	
		m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_RedPao : &m_BlackPao;
		break;
	case RBing:		
        m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_RedBing : &m_BlackBing;
		break;
	case BShuai:
        m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_BlackShuai : &m_RedShuai;
		break;
	case BShi:
        m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_BlackShi : &m_RedShi;
		break;
	case BXiang:
        m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_BlackXiang : &m_RedXiang;
	    break;
	case BMa:
        m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_BlackMa : &m_RedMa;
	    break;
	case BChe:
        m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_BlackChe : &m_RedChe;
		break;
	case BPao:
        m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_BlackPao : &m_RedPao;
		break;
	case BBing:
        m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_BlackBing : &m_RedBing;
		break;
	}

#pragma warning( default : 4806 )

	if(NULL != m_QiZi)
	{
		return DrawPicture(pdc, i, j, m_QiZi);
	}
	else
	{
		return false;
	}
}

/*******************************************************************************************************
��������DrawPicture
��  �ܣ���ͼƬ
��  ����
         CDC *pdc���豸������
         int i��ͼƬλ�ú�����[0-8]
         int j��ͼƬλ��������[0-9]
         CBitmap *pbmp��ͼƬָ��
		 BOOL CHHJKL�������Ӻ��磨Ĭ��ֵΪ false��
����ֵ���ɹ����� true
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺18:59:53
*******************************************************************************************************/
BOOL CXQCtrl::DrawPicture(CDC *pdc, int i, int j, CBitmap *pbmp, BOOL CHHJKL)
{
	ASSERT(pdc != NULL && pbmp != NULL);

	long m_X, m_Y;

	ConvertCoordinate(&m_X, &m_Y, &i, &j, IJToXY);
	if(CHHJKL)//�����Ӻ���
	{
		m_X -= m_QiPangDistance / 2;
	}
	else
	{
		m_X -= m_QiPangDistance / 2;
		m_Y -= m_QiPangDistance / 2;
	}

	//����ͼƬ
	BITMAP bitmap;
	pbmp->GetBitmap(&bitmap);
	
	CDC psdc;
	psdc.CreateCompatibleDC(pdc);
	psdc.SelectObject(pbmp);

	TransparentBlt2(pdc->GetSafeHdc(), m_X, m_Y, m_QiPangDistance, m_QiPangDistance, 
		   psdc.GetSafeHdc(), 0, 0, bitmap.bmWidth, bitmap.bmHeight, RGB(255, 255, 255));
    

	/*------------------------------------------------------------------------
	//�������� ---��  ��--- ɾ���� 2004-12-17 : 21:39:09
	//

    //����Windows 2000 ���ϰ汾
	TransparentBlt(pdc->GetSafeHdc(), m_X, m_Y, m_QiPangDistance, m_QiPangDistance, 
		   psdc.GetSafeHdc(), 0, 0, bitmap.bmWidth, bitmap.bmHeight, RGB(255, 255, 255));

	//
	//�������� ---��  ��--- ɾ���� 2004-12-17 : 21:39:09
	//------------------------------------------------------------------------*/

	psdc.DeleteDC();
	return true;
}

/*******************************************************************************************************
��������InvalidateRectage
��  �ܣ�������Ч����,����ɾ������
��  ����
         int i�����̺�����[0-8]
         int j�����̺�����[0-9]
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-9-26
ʱ  �䣺10:49:56
*******************************************************************************************************/
void CXQCtrl::InvalidateRectage(int i, int j)
{
	long x, y;
	if(i >= 0 && i <= 8 && j >= 0 && j <= 9)
	{
		ConvertCoordinate(&x, &y, &i, &j, IJToXY);
		RECT rect;
		rect.top = y - m_QiPangDistance / 2 - 1;
		rect.left = x - m_QiPangDistance / 2 - 1;
		rect.bottom = y + m_QiPangDistance / 2 + 1;
		rect.right = x + m_QiPangDistance / 2 + 1;
		InvalidateControl(&rect);
	}
}

/*******************************************************************************************************
��������InvalidateRectage
��  �ܣ�������Ч����,����ɾ������
��  ����
         CPoint p����������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-9-26
ʱ  �䣺11:20:12
*******************************************************************************************************/
void CXQCtrl::InvalidateRectage(CPoint p)
{
	InvalidateRectage(p.x, p.y);
}

/*******************************************************************************************************
��������Inital
��  �ܣ���ʼ��
��  ������
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-9-1
ʱ  �䣺19:49:39
*******************************************************************************************************/
BOOL CXQCtrl::Inital()
{
    
	//��ʾ��λ��
	m_TiShiBoxPostion.p1.x = -1;
    m_TiShiBoxPostion.p1.y = -1;
	m_TiShiBoxPostion.p2.x = -1;
    m_TiShiBoxPostion.p2.y = -1;	

	//------------------------------------------------------------------------
	//��������� ===��ʼ����ʼ���=== ���ܵ�����
	//

	//��ʼ�������
	int i, j;
	for(i = 0; i < 9; i++)
		for(j = 0; j < 10; j++)
			m_ChessBoard[i][j] = NoQiZi;

	//�������̲���,���Ϻ���
	if(m_QiPang & OnlyTopRed)
	{
		m_ChessBoard[0][0] = m_ChessBoard[8][0] = RChe;
		m_ChessBoard[1][0] = m_ChessBoard[7][0] = RMa;
		m_ChessBoard[2][0] = m_ChessBoard[6][0] = RXiang;
		m_ChessBoard[3][0] = m_ChessBoard[5][0] = RShi;
		m_ChessBoard[4][0] = RShuai;
		m_ChessBoard[1][2] = m_ChessBoard[7][2] = RPao;
		m_ChessBoard[0][3] = m_ChessBoard[2][3] = m_ChessBoard[4][3]= m_ChessBoard[6][3] = m_ChessBoard[8][3] = RBing;
	}

    if(m_QiPang & OnlyBottomBlack)
	{
		m_ChessBoard[0][9] = m_ChessBoard[8][9] = BChe;
		m_ChessBoard[1][9] = m_ChessBoard[7][9] = BMa;
		m_ChessBoard[2][9] = m_ChessBoard[6][9] = BXiang;
		m_ChessBoard[3][9] = m_ChessBoard[5][9] = BShi;
		m_ChessBoard[4][9] = BShuai;
		m_ChessBoard[1][7] = m_ChessBoard[7][7] = BPao;
		m_ChessBoard[0][6] = m_ChessBoard[2][6] = m_ChessBoard[4][6]= m_ChessBoard[6][6] = m_ChessBoard[8][6] = BBing;
	}

	//
	//��������� ===��ʼ����ʼ���=== ���ܵ�����
	//------------------------------------------------------------------------

	return true;
}

//
//��������� ===�й�������洦��=== �ĺ�����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//��������� ===�����㷨=== �ĺ�����
//

/*******************************************************************************************************
��������bWalkChess
��  �ܣ��ж��ܷ�����
��  ����
         int i����ǰ�����λ��,������[0-8]
         int j����ǰ�����λ��,������[0-9]
         ENUM_QiZi qz����ǰ����
����ֵ������������巵�� true,���򷵻� false
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-9-26
ʱ  �䣺10:47:40
*******************************************************************************************************/
BOOL CXQCtrl::bWalkChess(int i, int j)
{
     if(i < 0 || i > 8 || j < 0 || j > 9)
	 {//����
		 return false;
	 }

	 switch(m_WalkState)
	 {
	 case RedReadly:
		 return RQi == GetQiZiSide(m_ChessBoard[i][j]) ? true : false;
		 break;
	 case RedWalked:
		 //��������,����ѡȡ
		 if(GetQiZiSide(m_ChessBoard[i][j]) == RQi)
		 {
			 m_iBuShu--;//�ض�����ʱ������һλ��
			 m_WalkState = RedReadly;
			 return true;
		 }
		 //�ж��ܷ�����
		 switch(m_pGoRule->GoChess(i, j, m_TiShiBoxPostion.p1.x, m_TiShiBoxPostion.p1.y, m_ChessBoard))
		 {
		 case JIANGJUN://����
			 PromptSound(_T("IDW_CHECK"));
			 return true;
			 break;
		 case RETURNTRUE://��������
			 m_ChessBoard[i][j] ? PromptSound(_T("IDW_EAT")) : PromptSound(_T("IDW_GO"));
			 return true;
			 break;
		 case BEIJIANGJUN://����
			 ::MessageBox(NULL, _T("�ⲽ�岻���ߣ�������Ҫ���ˡ�"), _T("������"), MB_OK );
			 return false;
			 break;
		 case JIANGDUIMIAN://������
			 ::MessageBox(NULL, _T("�ⲽ�岻���ߣ�������Ҫ���ˡ�"), _T("������"), MB_OK );
			 return false;
			 break;
		 case RETURNFALSE://�Ƿ�����
			 return false;
			 break;
		 }

		 break;
	 case BlackReadly:
		 return BQi == GetQiZiSide(m_ChessBoard[i][j]) ? true : false;
		 break;
	 case BlackWalked:
		 //��������,����ѡȡ
		 if(GetQiZiSide(m_ChessBoard[i][j]) == BQi)
		 {
			 m_iBuShu--;//�ض�����ʱ������һλ��
			 m_WalkState = BlackReadly;
			 return true;
		 }
		 //�ж��ܷ�����
		 switch(m_pGoRule->GoChess(i, j, m_TiShiBoxPostion.p1.x, m_TiShiBoxPostion.p1.y, m_ChessBoard))
		 {
		 case JIANGJUN://����
			 PromptSound(_T("IDW_CHECK"));
			 return true;
			 break;
		 case RETURNTRUE://��������
			 m_ChessBoard[i][j] ? PromptSound(_T("IDW_EAT")) : PromptSound(_T("IDW_GO"));
			 return true;
			 break;
		 case BEIJIANGJUN://����
			 ::MessageBox(NULL, _T("�ⲽ�岻���ߣ�������Ҫ���ˡ�"), _T("������"), MB_OK );
			 return false;
			 break;
		 case JIANGDUIMIAN://������
			 ::MessageBox(NULL, _T("�ⲽ�岻���ߣ�������Ҫ���ˡ�"), _T("������"), MB_OK );
			 return false;
			 break;
		 case RETURNFALSE://�Ƿ�����
			 return false;
			 break;
		 }

		 break;
	 }

	 return true;
}

/*******************************************************************************************************
��������WalkChess
��  �ܣ�����
��  ����
         int i�����̸������[0-8]
         int j�����̸�������[0-9]
         BOOL bEnvet���Ƿ񼤻��¼���Ĭ��ΪTRUE��
����ֵ���ɹ�����true�����򷵻�false��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-5
ʱ  �䣺10:17:56
*******************************************************************************************************/
BOOL CXQCtrl::WalkChess(int i, int j, BOOL bEnvet)
{
	int code;
	if(bWalkChess(i, j))
    { //����
        if(bEnvet)
        {
            FireMoveChess(i, j, m_ChessBoard[i][j]); //�¼�
        } //���� if(bEnvet)
		
		QiZiBianMa(&i, &j, &m_ChessBoard[i][j], &code);
		TRACE(_T("code=%d,m_chessbord=%d\n"),code,m_ChessBoard[i][j]);
        m_iBuShu++;
        TRACE(_T("m_iBuShu=%d\n"), m_iBuShu);
		if(!m_bFuPang)
		{   //���浽�����
			if(m_iBuShu < m_QiJu.GetSize()) 
			{
				m_QiJu[m_iBuShu] = code;
				m_QiJu.SetSize(m_iBuShu + 1);
			}
			else//����
			{
				m_QiJu.Add(code);//���浽�����
			}
		}

		//��ʾ��
		//DrawTiShiBox(i, j);
		switch(m_WalkState)
		{
		case RedReadly:
			PromptSound(_T("IDW_SELECT"));

			InvalidateRectage(m_TiShiBoxPostion.p1);
			InvalidateRectage(m_TiShiBoxPostion.p2);
			m_TiShiBoxPostion.p1.x = i;
			m_TiShiBoxPostion.p1.y = j;
			m_TiShiBoxPostion.p2.x = -1;
			m_TiShiBoxPostion.p2.y = -1;
			InvalidateRectage(m_TiShiBoxPostion.p1);

			m_WalkState = RedWalked;
			break;
		case RedWalked:
			m_TiShiBoxPostion.p2.x = i;
			m_TiShiBoxPostion.p2.y = j;
				
			m_ChessBoard[i][j] = m_ChessBoard[m_TiShiBoxPostion.p1.x][m_TiShiBoxPostion.p1.y];
			m_ChessBoard[m_TiShiBoxPostion.p1.x][m_TiShiBoxPostion.p1.y] = NoQiZi;

			InvalidateRectage(m_TiShiBoxPostion.p1);
			InvalidateRectage(m_TiShiBoxPostion.p2);

			m_WalkState = BlackReadly;
			break;
		case BlackReadly:
			PromptSound(_T("IDW_SELECT"));

			InvalidateRectage(m_TiShiBoxPostion.p1);
			InvalidateRectage(m_TiShiBoxPostion.p2);
			m_TiShiBoxPostion.p1.x = i;
			m_TiShiBoxPostion.p1.y = j;
			m_TiShiBoxPostion.p2.x = -1;
			m_TiShiBoxPostion.p2.y = -1;
			InvalidateRectage(m_TiShiBoxPostion.p1);
			
			m_WalkState = BlackWalked;
			break;		
		case BlackWalked:
			m_TiShiBoxPostion.p2.x = i;
			m_TiShiBoxPostion.p2.y = j;

			m_ChessBoard[i][j] = m_ChessBoard[m_TiShiBoxPostion.p1.x][m_TiShiBoxPostion.p1.y];
			m_ChessBoard[m_TiShiBoxPostion.p1.x][m_TiShiBoxPostion.p1.y] = NoQiZi;

			InvalidateRectage(m_TiShiBoxPostion.p1);
			InvalidateRectage(m_TiShiBoxPostion.p2);
			
			m_WalkState = RedReadly;
			break;
		}
		return true;
	}
	else//������
	{
		PromptSound(NULL);
		return false;
	}
}

//
//��������� ===�����㷨=== �ĺ�����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//��������� ===�й�����ؼ�����=== �ĺ�����
//

/*******************************************************************************************************
��������QiPangInterconvert
��  �ܣ�������̱任,�Ϻ�ı�Ϊ�º�
��  ������
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-6-9
ʱ  �䣺13:53:44
*******************************************************************************************************/
void CXQCtrl::QiPangInterconvert() 
{
	if(m_QiPang & SwapRedBetweenBlack)
		m_QiPang = m_QiPang & ~SwapRedBetweenBlack;
	else
	    m_QiPang = m_QiPang | SwapRedBetweenBlack;
	
	//�ػ�ؼ�
	InvalidateControl();
}

/*******************************************************************************************************
��������ReStart
��  �ܣ����¿�ʼ����
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-29
ʱ  �䣺19:24:07
*******************************************************************************************************/
void CXQCtrl::ReStart() 
{
	//��ʼ����������
	m_iBuShu = -1;       //����
	m_bFuPang = FALSE;   //���̱�־
	m_QiJu.RemoveAll();  //ɾ�����
	//���������巽
	if(m_WalkState == RedWalked)
		m_WalkState = RedReadly;
	if(m_WalkState == BlackWalked)
		m_WalkState = BlackReadly;

	//�����ļ�ͷ
	memset(&m_FileHead, 0, sizeof(m_FileHead));	    
    m_FileHead.dwVersion = MAKEWORD(_wVerMajor, _wVerMinor); //�汾
	HINSTANCE h=AfxGetInstanceHandle();
	LoadString(h, IDS_XQ, m_FileHead.szAppName, MAX_STRING_BUFFER);
	_tcscpy(m_FileHead.szAuthor, AUTHOR); //����
	CTime t;
	t = CTime::GetCurrentTime();
	m_FileHead.timeStart = t.GetTime();   //��ʼʱ��
	m_FileHead.iStartSide = m_WalkState;  //�����巽

	Inital();                             //��ʼ��������

	SetModifiedFlag();
	InvalidateControl();                  //�ػ�ؼ�	
}

/*******************************************************************************************************
��������SaveChess
��  �ܣ��������
��  ����
         LPCTSTR lpcszFileName���ļ���(����ȫ·��)
����ֵ���ɹ�����TRUE,���򷵻�FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-30
ʱ  �䣺10:16:51
*******************************************************************************************************/
BOOL CXQCtrl::SaveChess(LPCTSTR lpcszFileName) 
{
	if(m_iBuShu < 0)
		return FALSE;

    TRY
	{
		CStdioFile file(lpcszFileName, CFile::modeWrite | CFile::modeCreate);

		m_FileHead.iBuShu = m_iBuShu;
		file.Write(&m_FileHead, sizeof(m_FileHead));
		
		for(int i = 0; i <= m_iBuShu; i++)
		{
			TCHAR buf[16];
			_stprintf(buf, _T("%d\n"), m_QiJu[i]);				
			file.WriteString(buf);
		}
		file.Close();
	}
	CATCH(CFileException, e)
	{
		TCHAR szErr[MAX_STRING_BUFFER];
		e->GetErrorMessage(szErr, MAX_STRING_BUFFER);
		::MessageBox(NULL, szErr, _T("������� - ���ļ�����."), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	END_CATCH
	
	return TRUE;
}

/*******************************************************************************************************
��������LoadChess
��  �ܣ�װ�����,Ϊ��ֽ���״̬
��  ����
         LPCTSTR lpcszFileName������ļ���(����·��)
����ֵ���ɹ�����TRUE,���򷵻�FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-30
ʱ  �䣺11:00:03
*******************************************************************************************************/
BOOL CXQCtrl::LoadChess(LPCTSTR lpcszFileName) 
{
	TRY
	{
		CStdioFile file(lpcszFileName, CFile::modeRead);
		
		file.Read(&m_FileHead, sizeof(m_FileHead));
		if(_tcscmp(m_FileHead.szAuthor, AUTHOR))
			return FALSE;

		ReStart();//���¿�ʼ
		SetStartSide(m_FileHead.iStartSide);//˭������
		CString str;
		while(file.ReadString(str))
		{
			int i, j;
			ENUM_QiZi QZ;
			int code = _ttoi(str);
			QiZiBianMa(&i, &j, &QZ, &code, JieMa);		
			WalkChess(i, j);
		}
		file.Close();
	}
	CATCH(CFileException, e)
	{
		TCHAR szErr[MAX_STRING_BUFFER];
		e->GetErrorMessage(szErr, MAX_STRING_BUFFER);
		::MessageBox(NULL, szErr, _T("����� - ���ļ�����."), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	END_CATCH
	return TRUE;
}

/*******************************************************************************************************
��������LoadChessStart
��  �ܣ�װ�����,����Ϊ��ʼ״̬
˵  �������������,�����ÿؼ���״̬Ϊ����Ӧ:EnableWindow(FALSE);
		Ȼ����� NextStep() �� PreviouStep ���и���.
��  ����
         LPCTSTR lpcszFileName������ļ���
����ֵ���ɹ�����TRUE,���򷵻�FALSE.
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-30
ʱ  �䣺11:03:00
*******************************************************************************************************/
BOOL CXQCtrl::LoadChessStart(LPCTSTR lpcszFileName) 
{
	TRY
	{
		CStdioFile file(lpcszFileName, CFile::modeRead);
	
		file.Read(&m_FileHead, sizeof(m_FileHead));
		if(_tcscmp(m_FileHead.szAuthor, AUTHOR))
			return FALSE;
		
		ReStart();//���¿�ʼ
		SetStartSide(m_FileHead.iStartSide);//˭������
		CString str;
		while(file.ReadString(str))
		{
			m_iBuShu++;
			m_QiJu.Add(_ttoi(str));
		}
		m_iBuShu = -1;
		//m_bFuPang = TRUE; //�������˵��
		file.Close();
	}
	CATCH(CFileException, e)
	{
		TCHAR szErr[MAX_STRING_BUFFER];
		e->GetErrorMessage(szErr, MAX_STRING_BUFFER);
		::MessageBox(NULL, szErr, _T("����� - ���ļ�����."), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	END_CATCH
	
	return TRUE;
}

/*******************************************************************************************************
��������NextStep
��  �ܣ��²���
��  ������
����ֵ�����岽��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-5
ʱ  �䣺10:19:33
*******************************************************************************************************/
long CXQCtrl::NextStep() 
{
	if(m_QiJu.GetSize() > m_iBuShu + 1)
	{
		int i, j;
		ENUM_QiZi QZ;
		QiZiBianMa(&i, &j, &QZ, &m_QiJu[m_iBuShu + 1], JieMa);
		m_bFuPang = true;
		WalkChess(i, j);
		m_bFuPang = false;
	}
	else
	{
		PromptSound();
	}
	return m_iBuShu;//��Ϊ��WalkChess���Ѽ�һ
}

/*******************************************************************************************************
��������PreviouStep
��  �ܣ��ϲ���
��  ������
����ֵ�����岽��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-5
ʱ  �䣺10:19:51
*******************************************************************************************************/
long CXQCtrl::PreviouStep() 
{
	int i, j;
	ENUM_QiZi QZ;
	if(m_iBuShu > 0)
	{
		switch(m_WalkState)
		{
		case RedWalked:
		case BlackWalked:
            m_iBuShu--;
            TRACE(_T("%s(%d) : m_iBuShu=%d\n"), __FILE__, __LINE__, m_iBuShu);
		case RedReadly:
		case BlackReadly:
			InvalidateRectage(m_TiShiBoxPostion.p1);
			InvalidateRectage(m_TiShiBoxPostion.p2);
			
			QiZiBianMa(&i, &j, &QZ, &m_QiJu[m_iBuShu], JieMa);
			m_ChessBoard[i][j] = QZ;
			m_TiShiBoxPostion.p2.x = i;
			m_TiShiBoxPostion.p2.y = j;
			TRACE(_T("i=%d, j=%d, QZ=%d\n"), i, j, QZ);
			
			QiZiBianMa(&i, &j, &QZ, &m_QiJu[--m_iBuShu], JieMa);
			m_ChessBoard[i][j] = QZ;
			TRACE(_T("i=%d, j=%d, QZ=%d\n"), i, j, QZ);
			m_TiShiBoxPostion.p1.x = i;
			m_TiShiBoxPostion.p1.y = j;
			InvalidateRectage(m_TiShiBoxPostion.p1);
			InvalidateRectage(m_TiShiBoxPostion.p2);
            TRACE(_T("%s(%d) : m_iBuShu=%d\n"), __FILE__, __LINE__, m_iBuShu);

			m_iBuShu--;
			switch(m_WalkState)
			{
			case RedReadly:
			case RedWalked:
				m_WalkState = BlackReadly;
			    break;
			case BlackReadly:
			case BlackWalked:
				m_WalkState = RedReadly;
			}
			break;
		}
	}
	else
	{
		PromptSound();
		return 0;
	}
	return m_iBuShu;
}

/*******************************************************************************************************
��������InterConvertCoordinate
��  ��������������ת���ɶԷ�λ�õ�����,��Ҫ���������аѶԷ���������λ�ø�Ϊ�Է�λ��
��  ����
         short x��Դ����x
         short y��Դ����y
         short FAR* pi��Ŀ������x
         short FAR* pj��Ŀ������y
����ֵ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-9 14:18:30
*******************************************************************************************************/
void CXQCtrl::InterConvertCoordinate(short x, short y, short FAR* pi, short FAR* pj) 
{
	 *pi = 8 - x;
	 *pj = 9 - y;
}

/*******************************************************************************************************
��������Walk
��  �ܣ�����
��  ����
         short i��������
         short j��������
����ֵ���ɹ�����TRUE,���򷵻�FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-6-9
ʱ  �䣺14:25:34
*******************************************************************************************************/
BOOL CXQCtrl::Walk(short i, short j) 
{
    if(WalkChess(i, j, FALSE))
	{
	 	return TRUE; 
	}
	return FALSE;
}

//
//��������� ===�й�����ؼ�����=== �ĺ�����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
