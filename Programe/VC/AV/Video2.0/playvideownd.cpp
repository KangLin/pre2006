/*******************************************************************************************************
�ļ�����PlayVideoWnd.cpp
��  �ܣ���ʾ��Ƶ����ʵ���ļ�

��  �ӣ�������ʾ��Ƶ������ CDisplayWnd
��  ����1�������������н�������Ķ���ָ�� 
		   CDisplayWnd* m_DisplayWnd;
        2����������������������� OnCreate ����
		3����������� OnCreate ������ 
		   m_DisplayWnd = new CDisplayWnd��
		   m_DisplayWnd->Create(WS_CHILD|WS_VISIBLE,rect,this,NULL);
		4�����ó�Ա���� Display ����ʾ��Ƶ����(��ѹ��).
		5������������� OnDestroy() �����������м���
		   //���͹رմ�����Ϣ,���Ǳ����,�Ա������ڵ������رա�
		   ::SendMessage(m_DisplayWnd->GetSaftHwnd(), WM_CLOSE, NULL, NULL);
		   //��Ϊ�����������������
		   delete m_DisplayWnd;
��  �ߣ���  ��
��  ����2.0.0.1
��  �ڣ�2004-11-17
ʱ  �䣺14:39:10

��  ����
        1�������������н�������Ķ���ָ�� 
		   CPlayVideoWnd* m_PlaypVidWnd;
        2����������������������� OnCreate ����
		3����������� OnCreate ������ 
		   m_PlayVidWnd = new CPlayVideoWnd��
		   m_PlayVidWnd->Create(WS_CHILD|WS_VISIBLE,rect,this,NULL);
		4���ڳ�Ա���� Display �м������Ƶ֡���ݵ�����������롣���磺��Ƶ֡���ݵķ��͡�
		   ���ֻ��ʾ��Ƶ����,����Display������Ƶ���ݵĵ�ָ��ͳ���
		   �����Ѿ������ݽ�����ѹ��,��������Լ����Լ���ѹ������.
		5���ڿ�ʼ����ĵط����� m_PlayVidWnd->StartCapture();
		6����Ҫֹͣ��������ĵط����� m_PlayVidWnd->StopCapture();
		7������������� OnDestroy() �����������м���
		   //���͹رմ�����Ϣ,���Ǳ����,�Ա������ڵ������رա�
		   ::SendMessage(m_PlayVidWnd->GetSaftHwnd(), WM_CLOSE, NULL, NULL);
		   //��Ϊ�����������������
		   delete m_DispVidWnd;
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-11-3
ʱ  �䣺17:11:32
*******************************************************************************************************/

#include "stdafx.h"
#include "playVideoWnd.h"

//����ͷ�ļ�
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
			TRACE(_T("DrawDibEndʧ��!\n"));
		}
	    if(!::DrawDibClose(m_hdib))
		{
			TRACE(_T("DrawDibCloseʧ��!\n"));
		}
	}

	delete []m_pOut;	
}

BOOL CDisplayWnd::Create(const RECT& rect, CWnd* pParentWnd, DWORD dwStyle, UINT nID, CCreateContext* pContext) 
{
	return CWnd::Create(NULL, _T("��Ƶ��ʾ-���ߣ�����"), dwStyle, rect, pParentWnd, nID, pContext);
}

/////////////////////////////////////////////////////////////////////////////
// CDisplayWnd message handlers
int CDisplayWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
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

void CDisplayWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	m_wndWidth = cx;      
	m_wndHeight = cy;		
}

/*******************************************************************************************************
��������Display
��  �ܣ���ʾ��Ƶ����
��  ����
         LPVOID pData����Ƶ����
         DWORD iSize����Ƶ���ݵĴ�С
����ֵ����
��  �ߣ���  ��
��  ����2.0.0.1
��  �ڣ�2004-11-17
ʱ  �䣺14:40:41
*******************************************************************************************************/
void CDisplayWnd::Display(LPVOID pData, DWORD iSize)
{
	if(!m_Compressor.SeqDecompress(pData, iSize, m_pOut, (DWORD*)&m_dwOutSize))
	{
		TRACE(_T("Display:��ѹ��ʧ��\n"));
	}
	TRACE(_T("��ѹ����Ĵ�СΪ%d\n"), m_dwOutSize);
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
	return CWnd::Create(NULL, _T("��Ƶ��ʾ-���ߣ�����"), dwStyle, rect, pParentWnd, nID, pContext);
}

/*******************************************************************************************************
��������OnCreate
��  �ܣ��ڴ˳�ʼ�������豸
��  ����
         LPCREATESTRUCT lpCreateStruct��
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-17
ʱ  �䣺13:19:36
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
	ע�⣺
    ��Ϊ����û�е���
    CWnd::OnDestroy();
	�����ڴ������е���
	delete m_DispVidWnd;
	ǰ���ȵ��ã�
	::SendMessage(m_PlayVidWnd->GetSaftHwnd(), WM_CLOSE, NULL, NULL);
	�������رմ��ڡ�
    *******************************************************************************************************/

	if(m_VideoCapture)
	{
		m_VideoCapture->Destroy();
	}

	delete m_VideoCapture;
}

/*******************************************************************************************************
��������StartCapture
��  �ܣ���ʼ����
��  ������
����ֵ���ɹ�����TRUE�����򷵻�FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-11
ʱ  �䣺19:11:59
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
��������StopCapture
��  �ܣ�ֹͣ����
��  ������
����ֵ���ɹ�����TRUE�����򷵻�FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-11
ʱ  �䣺19:12:03
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
��������Display
��  �ܣ��ڴ�������ʾ����������,���ڴ˶���Ƶ����ѹ���ͷ���
��  ����
         LPVOID pData����Ƶ����
         DWORD iSize����Ƶ���ݵĴ�С
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-11
ʱ  �䣺19:13:31
*******************************************************************************************************/
void CPlayVideoWnd::Display(LPVOID pData, DWORD iSize)
{
	
	TRACE(_T("�����һ֡���ݴ�СΪ%d\n"), iSize);
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
	
	//TODO:�ڴ˿ɼ��������Բ��������ݲ����Ĵ���(���磺ѹ������)����		
	if(!m_Compressor.SeqCompress(pData, iSize, m_pOut, (DWORD*)&m_dwOutSize))
	{
		TRACE(_T("Displayѹ��ʧ��\n"));
		return ;
	}
	TRACE(_T("�����һ֡����ѹ����Ĵ�СΪ%d\n"), m_dwOutSize);
	
#ifdef _TEST
	//*����:
	((CTestDlg*)AfxGetMainWnd())->m_DisplayWnd->Display(m_pOut, m_dwOutSize);
	//*/
#endif	
}

