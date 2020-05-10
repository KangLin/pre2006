/*******************************************************************************************************
�ļ�����VideoCapture.cpp
��  �ܣ�������Ƶ֡��ʵ���ļ�
ʹ  �ã�1���ȶ��壺CVideoCapture* m_VideoCapture;
        2�����������OnCreate()������,��������
	    m_VideoCapture = new CVideoCapture;
		if(m_VideoCapture)
		{
		    3����ʼ��
			m_VideoCapture->Initialize();
			4�����ø����ڶ���
			m_VideoCapture->SetDisplayWindow(this);
			5����λͼ�ṹ����������
			m_bmpInfo = m_VideoCapture->m_bmpInfo;
		}
		6���ں��� LRESULT CALLBACK OnCaptureVideo(HWND hwnd, LPVIDEOHDR lphdr)��
		   �������Ƶ���ݵĴ���
		7���ڿ�ʼ������Ƶ�����ã�
		    m_VideoCapture->StartCapture();
		8���ڽ�����Ƶ���񴦵��ã�
            m_VideoCapture->StopCapture();
		9�����������Destory()�е��ã�
		    delete m_VideoCapture;
��������Visual C++ 6.0
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-2
ʱ  �䣺16:22:48
*******************************************************************************************************/

#include "Stdafx.h"
#include "VideoCapture.h"
#include "playVideoWnd.h"

#ifndef _TEST
#include "..\VideoCtrl\VideoCtl.h"
#endif

#include <afxmt.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVideoCapture::CVideoCapture()
{
	m_hCapWnd = NULL;
	isOver = FALSE;
	
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

}

CVideoCapture::~CVideoCapture()
{
	if(m_hCapWnd)
		Destroy();
}

void CVideoCapture::SetDisplayWindow(CWnd *pwnd)
{
	m_wndDisplay = pwnd;
}

/*******************************************************************************************************
��������Initialize
��  �ܣ���Ƶ��ʼ��
��  ������
����ֵ���ɹ�����TRUE�����򷵻�FALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-2
ʱ  �䣺15:25:48
*******************************************************************************************************/
BOOL CVideoCapture::Initialize()
{
	TCHAR devname[100],devversion[100];
	TCHAR str[200];
	INT index=0;
	
	//����һ�����񴰿�(ʵ���Ͼ���һ���������ʵ��)
	m_hCapWnd = capCreateCaptureWindow(_T("��Ƶ���񴰿�"), 
		WS_POPUP,// | WS_OVERLAPPEDWINDOW  | WS_VISIBLE,//������˲�����ͺ���ͨ�Ĵ���һ��
		0, 0, 0, 0, //QCIF_WIDTH, QCIF_HEIGHT,
		0, 0);
	if(m_hCapWnd == NULL)
	{
		TRACE("%s", _T("���ܽ������񴰿ڡ�\n"));
		return FALSE;
	}	

	/*******************************************************************************************************
      �����û�����
      �����ǣ����û����ݱ��浽���񴰿ڣ��Ա��ڻص������У�
	  ���� capGetUserData �õ�����û����ݡ�
	*******************************************************************************************************/
	if(!capSetUserData(m_hCapWnd, this))
		TRACE("%s", _T("����,����������ִ�С����������û����ݡ�\n"));

	//���ò��񴰿ڵĻص���������һ��Ҳ�ɷ������Ӻ�����ò�����
    //���ò��񴰿ڲ���ʱ����Ƶ�ص�����
	//ע�⣺�� Destroy ������Ҫ�Ͽ��ص�����
    if(!capSetCallbackOnVideoStream(m_hCapWnd, OnCaptureVideo))
		TRACE("%s", _T("��Ƶ���ص�������װʧ�ܡ�\n")); 
	
	/*******************************************************************************************************
	  �õ�����������������
	  capGetDriverDescription �Ȳ��Ҽ��弴�õĲ����豸��������
	  �ٲ�ע����еĲ��������б��ٲ��ļ� SYSTEM��INI �е��豸�����б�
	  ��Χ[0��9]
	  ������һ��ö�ٳ�ϵͳ�����в����豸����������б�
	  ���磺
	  for(int i = 0; i < 10; i++)
	  {
	      capGetDriverDescription(i, devname, 100, devversion,100);
		  TRACE(_T("�豸���������� = %s �汾�� = %s \n"), devname, devversion);
	  }
	*******************************************************************************************************/
	if(!capGetDriverDescription(index, devname, 100, devversion, 100))
		TRACE("%s", _T("ϵͳ��û����Ƶ�����豸��������\n"));
	_stprintf(str, _T("�豸���������� = %s �汾�� = %s \n"), devname, devversion);
	TRACE("%s", str);
	
	//�����񴰿ںͲ�����������
	if(!capDriverConnect(m_hCapWnd, index))
	{
		//�豸�����Ѿ��ҿ������������ʱû���ʵ��Ĺرա�
		AfxMessageBox(_T("���ܴ���Ƶ����������"));
		TRACE("%s", _T("���ܴ���Ƶ����������\n"));
		m_hCapWnd = NULL;
		return FALSE;
	}
	
	//���ò��񴰿ڲ���	
	if(SetCapturePara() == FALSE)
	{
		TRACE("%s", _T("����������������ʧ�ܡ�\n"));
		capDriverDisconnect(m_hCapWnd);  //�Ͽ��벶���豸������
		return FALSE;
	}

	return TRUE;
}

/*******************************************************************************************************
��������SetCapturePara
��  �ܣ����ò����Ļ����
��  ������
����ֵ������ɹ����� TRUE�����򣬷��� FALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-2
ʱ  �䣺16:15:01
*******************************************************************************************************/
BOOL  CVideoCapture::SetCapturePara()
{
	//------------------------------------------------------------------------
	//��������� ===���ò��񴰿ڵĹ���ģʽ=== ���ܵ�����
	//

	/*��Ƶ���������Խ������Ƶ�������ֹ���ģʽ: Previewģʽ��overlayģʽ, ���һ�����������ܹ�ִ�����ַ���, �û�����������ѡ��һ��.Previewģʽ�ѴӲ���Ӳ����������������ϵͳ�ڴ沢ʹ��ͼ���豸����(GDI)�����ֻ�֡��ʾ�ڲ��񴰿���. Ӧ�ó�������ڸ�����ʧȥ����ʱ������ʾ�ٶ�, �������ֵõ������ӿ���ʾ�ٶ�, ����ģʽҪռ�ô���CPUʱ��.
	//����Ϊ Preview ģʽ,����ģʽ���񴰿���ֱ����ʾ����ͼ��
	//�ڽ������񴰿�ʱ���ϴ���������Ϊ����ʾ�� WS_OVERLAPPEDWINDOW  | WS_VISIBLE,���ò��񴰿ڵĴ�С
	capPreview(m_hCapWnd, true);
    capPreviewScale(m_hCapWnd, true);
	//����Ϊ overlay ģʽ
    //capOverlay(m_hCapWnd, true);
	//*/

	//
	//��������� ===���ò��񴰿ڵĹ���ģʽ=== ���ܵ�����
	//------------------------------------------------------------------------


	//------------------------------------------------------------------------
	//��������� ===���ò��񴰿ڵĲ���(��һ���Ǳ����)=== ���ܵ�����
	//

	CAPTUREPARMS CapParms = {0};	

    //�õ�����������
	if(!capCaptureGetSetup(m_hCapWnd, &CapParms, sizeof(CapParms)))
    {
		TRACE("%s", _T("���ܵõ�������������\n"));
		return FALSE;
	}

	//���ò���������
	//CapParms.dwRequestMicroSecPerFrame *= 2;   //���ò�������,Ĭ��Ϊ 15֡/��
	CapParms.vKeyAbort = 0;                    //ֹͣ�ð���ȡ��
	CapParms.fAbortLeftMouse = FALSE;          //ֹͣ��������ȡ��
	CapParms.fAbortRightMouse = FALSE;         //ֹͣ������Ҽ�ȡ��
	CapParms.fYield = TRUE;                    //�����񴰿ڲ�����̨�߳�,Ĭ��ֵΪFALSE,
	                                           //����ʼ��,Ӧ�ó��򽫲���Ӧ������
	CapParms.fCaptureAudio = FALSE;            //��������Ƶ
	CapParms.wPercentDropForError = 50;        //�������ʧ����֡
	
	if(capCaptureSetSetup(m_hCapWnd, &CapParms, sizeof(CapParms)) == FALSE)
	{
		TRACE("%s", _T("���ò���������ʧ�ܡ�\n"));
		return FALSE;
	}

	//
	//��������� ===���ò��񴰿ڵĲ���(��һ���Ǳ����)=== ���ܵ�����
	//------------------------------------------------------------------------


	/*------------------------------------------------------------------------
	//��������� ===�öԻ����ò���=== ���ܵ�����
	//

	CAPDRIVERCAPS capdrivercaps;
	capDriverGetCaps(m_hCapWnd, &capdrivercaps, sizeof(CAPDRIVERCAPS));

	/*1��������ƵԴ
	if(capdrivercaps.fHasDlgVideoSource)
	{
		capDlgVideoSource(m_hCapWnd);
	}
	else
	{
		TRACE(_T("��֧����ƵԴ���öԻ���\n"));
		TRACE("%s", _T("��֧����ƵԴ���öԻ���\n"));
	}
	//*/
	
	/*2��������Ƶ��ʽ
	if(capdrivercaps.fHasDlgVideoFormat)
	{
		capDlgVideoFormat(m_hCapWnd);
	}
	else
	{
		TRACE(_T("��֧����Ƶ��ʽ���öԻ���\n"));
		TRACE("%s", _T("��֧����Ƶ��ʽ���öԻ���\n"));
	}
	//*/

	//3��������Ƶѹ�������ѹ������
	//capDlgVideoCompression(m_hCapWnd);

	/*4��������Ƶ��ʾ
	if(capdrivercaps.fHasDlgVideoDisplay)
	{
		capDlgVideoDisplay(m_hCapWnd);
	}
	else
	{
		TRACE(_T("��֧����Ƶ��ʾ�Ի���\n"));
	}
	//*/

	//
	//��������� ===�öԻ����ò���=== ���ܵ�����
	//------------------------------------------------------------------------

	//�õ���Ƶ��ʽ
	capGetVideoFormat(m_hCapWnd, &m_bmpInfo, sizeof(m_bmpInfo));
	
	//------------------------------------------------------------------------
	//��������� ===������Ƶ��ʽ=== ���ܵ�����
	//

	m_bmpInfo.bmiHeader.biWidth = IMAGE_WIDTH;
	m_bmpInfo.bmiHeader.biHeight = IMAGE_HEIGHT;
	m_bmpInfo.bmiHeader.biPlanes = 1;
	m_bmpInfo.bmiHeader.biBitCount = 24;
	m_bmpInfo.bmiHeader.biCompression = 0;

	//������Ƶ��ʽ
	if(capSetVideoFormat(m_hCapWnd, &m_bmpInfo, sizeof(m_bmpInfo)))
	{
		TRACE("%s", _T("��Ƶ������������ɡ�\n"));
	}
	else
	{
		TRACE("%s", _T("����������Ƶ��������\n"));
		//�Ͽ��豸�����벶�񴰿ڵ�����
		if(!capDriverDisconnect(m_hCapWnd))
		{
			TRACE("%s", _T("����������Ƶ�������Ҳ��ܰѲ��񴰿��벶�������Ͽ���\n"));
		}
	    return FALSE;
	}

	//
	//��������� ===������Ƶ��ʽ=== ���ܵ�����
	//------------------------------------------------------------------------

	return TRUE;
}

/*******************************************************************************************************
��������Destroy
��  �ܣ�ֹͣ��������ҶϿ��豸�������ӡ��رղ����ٲ��񴰿�
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-2
ʱ  �䣺16:24:41
*******************************************************************************************************/
void CVideoCapture::Destroy()
{
	if(m_hCapWnd == NULL) 
		return;
    
    StopCapture();

	//ȡ���������    
	capCaptureAbort(m_hCapWnd);
     
	Sleep(300);		// ��ʱ     

  	//�Ͽ���Ƶ����ص�����
	capSetCallbackOnVideoStream(m_hCapWnd, NULL);  
				
	//���Ͽ����񴰿����豸��������
    if(!capDriverDisconnect(m_hCapWnd))
	{
		TRACE("%s", _T("���ܰѲ��񴰿��벶�������Ͽ���\n"));
	}

	//ע��:�رղ����ٲ��񴰿�,����Ļ�����ʱ����ʱ�����쳣
	::SendMessage(m_hCapWnd, WM_CLOSE, NULL, NULL);
	ASSERT(m_hCapWnd);
	//DestroyWindow(m_hCapWnd);
}

/*******************************************************************************************************
��������StartCapture
��  �ܣ���ʼ�� webcam ����֡
��  ����
        bToFile:ΪTRUE���������͵��ļ�,ΪFALSE�����������͵��ļ���Ĭ��ֵΪFALSE��
����ֵ���ɹ����� TRUE�����򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-2
ʱ  �䣺16:45:31
*******************************************************************************************************/
BOOL CVideoCapture::StartCapture(BOOL bToFile)
{
	//��ʼ���񡭡�
	if(bToFile)
	{   //�����ļ���
		if(capCaptureSequence(m_hCapWnd) == FALSE)
		{
			TRACE("%s", _T("˳�򲶻�ʧ��...\n"));
			return FALSE;
		}
	}
	else
	{	//�������ļ�
		if(capCaptureSequenceNoFile(m_hCapWnd) == FALSE)
		{
			TRACE("%s", _T("˳�򲶻�ʧ��...\n"));
			return FALSE;
		}
		
	}
	return TRUE;
}

/*******************************************************************************************************
��������StopCapture
��  �ܣ�ֹͣ�������
��  ������
����ֵ���ɹ����� TRUE�����򷵻أ�FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-2
ʱ  �䣺17:18:35
*******************************************************************************************************/
BOOL CVideoCapture::StopCapture()
{	
	//capCaptureStop��capCaptureAbort��֮ͬ��
	//���ں�������Ϣ������ǰ��ֹͣ��Ƶ����
	capCaptureStop(m_hCapWnd);
	capCaptureAbort(m_hCapWnd);
	Sleep(300);	
	return TRUE;
}

/*******************************************************************************************************
��������OnCaptureVideo
��  �ܣ�����Ƶ֡���������򲶻�ʱ���ô˺�����
��  ����
         HWND hwnd�����񴰿ڵľ��
         LPVIDEOHDR lphdr���ش���һ�� VIDEDHDR �ṹ
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-2
ʱ  �䣺17:50:22
*******************************************************************************************************/
LRESULT CALLBACK OnCaptureVideo(HWND hwnd, LPVIDEOHDR lphdr)
{
	CVideoCapture *vidcap = (CVideoCapture *)capGetUserData(hwnd);
	if(vidcap != NULL )
	{
#ifdef _PLAYVIDEOWND
		//TODO:������������Ƶ֡Ƶ�Ĵ������
        ((CPlayVideoWnd*)vidcap->m_wndDisplay)->Display(lphdr->lpData, lphdr->dwBytesUsed);
#endif
#ifdef _PLAYVIDEOCTROL
        ((CVideoCtrl*)vidcap->m_wndDisplay)->Display(lphdr->lpData, lphdr->dwBytesUsed);
#endif
	}
	return TRUE;
}

/*******************************************************************************************************
��������AllocateMemory
��  �ܣ�ΪDIB ͼ������ڴ�
��  ����
         PBITMAPINFO &bmpinfo��
����ֵ���ɹ������ط������ڵĴ�С��ʧ�ܷ���-1
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-2
ʱ  �䣺17:44:11
*******************************************************************************************************/
int CVideoCapture::AllocateMemory(PBITMAPINFO &bmpinfo)
{
    INT size1, size2, size;
	BITMAPINFO tbmp;
	TCHAR  str[200];

	capGetVideoFormat(m_hCapWnd, &tbmp, sizeof(tbmp));

	size1 = getFormatSize (tbmp);
	size2 = getImageSize (tbmp);
	size = size1 + size2;


	_stprintf(str, _T("��ʽ�ĳߴ� = %d, ͼ��ĳߴ� = %d , fun_size = %d "),
			 size1,size2, capGetVideoFormatSize(m_hCapWnd));
	TRACE("%s", str);

	bmpinfo=(BITMAPINFO *) new BYTE[size];
	
	if(bmpinfo == NULL)
	{
		AfxMessageBox(_T("���ܷ����ڴ档"));
		return -1;
	}

	memset(bmpinfo, 0, sizeof(*bmpinfo));

	capGetVideoFormat(m_hCapWnd, bmpinfo, sizeof(*bmpinfo));

	return size1;
}

/*******************************************************************************************************
��������getFormatSize
��  �ܣ����� DIB ͼ���ʽ�ĳߴ�
��  ����
         BITMAPINFO bmp��
����ֵ��DIB ͼ���ʽ�ĳߴ�
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-2
ʱ  �䣺17:47:46
*******************************************************************************************************/
int CVideoCapture::getFormatSize(BITMAPINFO bmp)
{
	INT size;

	size = (bmp.bmiHeader.biSize != 0) ? bmp.bmiHeader.biSize : sizeof(BITMAPINFOHEADER);

	//return (size+ bmp.bmiHeader.biClrUsed *sizeof(RGBQUAD));

	return size; //RGBQUAD is absent for 24 bit bmp image.
}

/*******************************************************************************************************
��������getImageSize
��  �ܣ��õ�ͼ��ĳߴ�
��  ����
         BITMAPINFO bmp��
����ֵ��ͼ��ĳߴ�
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-2
ʱ  �䣺17:49:25
*******************************************************************************************************/
int CVideoCapture::getImageSize(BITMAPINFO bmp)
{
	INT size;
	
	BITMAPINFOHEADER head=bmp.bmiHeader;

	if( head.biSizeImage == 0)
	{
		size=( head.biWidth * head.biHeight * head.biBitCount)/8;
	}
	else
		size = head.biSizeImage;
	
	return size;
}