/*******************************************************************************************************
�ļ�����PlayVideoWnd.cpp
��  �ܣ���ʾ��Ƶ����ʵ���ļ�
��  ����
        1�������������н�������Ķ���ָ�� m_PlaypVidWnd
        2����������������������� OnCreate ����
		3����������� OnCreate ������ 
		   m_PlayVidWnd = new CPlayVideoWnd��
		   
		   //���ֻ��ʾ��Ƶ���ݣ�������Ҫ������Ƶ,��������һ�䣺
		   //SetOnlyPlay();

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

//�й�����ͷ�ļ�
#ifdef _CCHESS
#include "..\..\�й�����\�й�����view.h"
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

	//�����Լ���λͼ�ṹ		
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

	//������ʾ�����С
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
	return CWnd::Create(NULL, _T("��Ƶ��ʾ-���ߣ�����"), dwStyle, rect, pParentWnd, nID, pContext);
}

void CPlayVideoWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_wndWidth = cx;      
	m_wndHeight = cy;	
}

/*******************************************************************************************************
��������SetOnlyPlay
��  �ܣ����ô˴�����ֻ��ʾ��Ƶ���ݣ���������Ƶ
ע  �⣺�������ֻ������Create֮ǰ�����ã��Ժ�Ͳ��������ˡ�
��  ����
         BOOL bOnlyPlay�����ΪTRUE��ֻ��ʾ���ݣ�
		                     ΪFALSE��ͬʱ��������Ƶ����
����ֵ������ǰ��״̬��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-11
ʱ  �䣺19:14:49
*******************************************************************************************************/
BOOL CPlayVideoWnd::SetOnlyPlay(BOOL bOnlyPlay)
{
	BOOL r = m_bOnlyPlay;
	m_bOnlyPlay = bOnlyPlay;
	return r;
}

/*******************************************************************************************************
��������OnCreate
��  �ܣ���ʼ��
��  ����
         LPCREATESTRUCT lpCreateStruct��
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-11
ʱ  �䣺19:14:18
*******************************************************************************************************/
int CPlayVideoWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if(!m_bOnlyPlay) //��ʼ����Ƶ����
	{
		m_VideoCapture = new CVideoCapture;

		if(m_VideoCapture)
		{
			m_VideoCapture->Initialize();
			m_VideoCapture->SetDisplayWindow(this);
			m_bmpInfo = m_VideoCapture->m_bmpInfo;
		}	
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
		m_VideoCapture->StopCapture();
	}

	delete m_VideoCapture;
	delete []m_pOut;

#ifdef _CCHESS
	m_DSocket.Close();
#endif
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
	if(m_VideoCapture && !m_bOnlyPlay)
	{
		return m_VideoCapture->StartCapture();
	}
	return true;
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
	if(m_VideoCapture && !m_bOnlyPlay)
	{
		retVal = m_VideoCapture->StopCapture();
	}

	return retVal;
}

/*******************************************************************************************************
��������Display
��  �ܣ��ڴ�������ʾ����������,���ڴ˶���Ƶ����ѹ���ͷ���
��  ����
         BYTE *pData����Ƶ����
         DWORD iSize����Ƶ���ݵĴ�С
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-11
ʱ  �䣺19:13:31
*******************************************************************************************************/
void CPlayVideoWnd::Display(BYTE *pData, DWORD iSize)
{
	if(m_bOnlyPlay)
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
	else
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
		((CTestDlg*)AfxGetMainWnd())->m_onlywnd.Display(m_pOut, m_dwOutSize);
		//*/
#endif

#ifdef _CCHESS
		//*�й�����
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
				TRACE(_T("Displayѹ��ʧ��\n"));
				return;
			}
			TRACE(_T("�����һ֡����ѹ����Ĵ�СΪ%d\n"), p->DataLength);

			if(view->m_pSocket->SendTo(p, p->DataLength + sizeof(tagData), view->m_dwRemotePort, view->m_szRemoteIP)
				== SOCKET_ERROR)
			{
				TRACE(_T("�������ݳ���.�����:%d\n"), ::GetLastError());
			}
			
			if(bConnect)
				m_DSocket.SendTo(m_pOut, m_dwOutSize, m_uRemotePort, m_szRemoteName);*/
		}
		catch(...)
		{
			TRACE(_T("������Ƶ�����쳣\n"));
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
		TRACE(_T("��ƵDSocket����ʧ��.\n"));
		return FALSE;
	}
	m_uLocatPort = uPort;
	m_uRemotePort = uRemotePort;
	m_szRemoteName = szRemoteName;
	bConnect = TRUE;
	return TRUE;
}
#endif