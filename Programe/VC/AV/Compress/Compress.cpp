/*******************************************************************************************************
�ļ�����Compress.cpp
��  �ܣ�ѹ��/��ѹ����ʵ���ļ�
        //��Ĭ�ϵ�ѹ��/��ѹ���� Divx MPEG-4(Fast-Motion)
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-11-11
ʱ  �䣺10:47:30
*******************************************************************************************************/

#include "stdafx.h"
#include "Compress.h"
#include <string>

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCompressor::CCompressor()
{

	//------------------------------------------------------------------------
	//��������� ===����ѹ������Ĭ�ϲ���=== ���ܵ�����
	//

	ZeroMemory(&m_Compvars, sizeof(COMPVARS));
	m_Compvars.cbSize = sizeof(COMPVARS);
	m_Compvars.dwFlags = ICMF_COMPVARS_VALID ;
	m_Compvars.hic = m_hIC;
	m_Compvars.fccType = ICTYPE_VIDEO ;
	m_Compvars.fccHandler = 880175460;  //Divx MPEG-4(Fast-Motion);   859189837; //΢��H.263;   
	m_Compvars.lpbiOut = 0;
	m_Compvars.lKey = 10;
	m_Compvars.lDataRate = 6;
	m_Compvars.lQ = 10000;

	//
	//��������� ===����ѹ������Ĭ�ϲ���=== ���ܵ�����
	//------------------------------------------------------------------------
	

	//------------------------------------------------------------------------
	//��������� ===���������ʽ=== ���ܵ�����
	//

	ZeroMemory(&m_bmpIn, sizeof(BITMAPINFO));
	m_bmpIn.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_bmpIn.bmiHeader.biWidth = QCIF_WIDTH;   //ͼ��Ŀ��
	m_bmpIn.bmiHeader.biHeight = QCIF_HEIGHT; //ͼ��ĸ߶�
	m_bmpIn.bmiHeader.biPlanes = 1;	
	m_bmpIn.bmiHeader.biBitCount = 24;	
	m_bmpIn.bmiHeader.biSizeImage = 76032;

	//
	//��������� ===���������ʽ=== ���ܵ�����
	//------------------------------------------------------------------------

	if(!Initialize())//��Ĭ�ϵ�ѹ��/��ѹ���� Divx MPEG-4(Fast-Motion)
	{
		Destory();
		InstallDevice();
		if(!Initialize())
		{
			Destory();
			CompressorChoose(NULL);
			Initialize();
		}//if(!Initialize())
	}//if(!Initialize())//��Ĭ�ϵ�ѹ��/��ѹ���� Divx MPEG-4(Fast-Motion)

}

CCompressor::~CCompressor()
{
	Destory();
}

/*******************************************************************************************************
��������InstallDevice
��  �ܣ���װѹ������������,
        Ĭ�ϰ�װΪ Divx MPEG-4(Fast-Motion),
		�䶯̬���ӿ� divxc32f.dll Ӧ��ִ���ļ���ͬһĿ¼
��  ������
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-11
ʱ  �䣺13:23:06
*******************************************************************************************************/
BOOL CCompressor::InstallDevice()
{
	CFileEx fex;
	TCHAR szFileName[1024];
	fex.GetModuleFileName(szFileName, 1024);
	fex.GetFilePath(szFileName, 1024);
	_tcscat(szFileName, _T("\\DivXc32f.dll"));

	INT result = ICInstall ( ICTYPE_VIDEO, 
		mmioFOURCC('D','I','V','4'), 
		(LPARAM)szFileName, NULL, 
		ICINSTALL_DRIVER); 
	TRACE(_T("ѹ������װ����ֵΪ:%d.\n"), result);
	return TRUE;
}

/*******************************************************************************************************
��������CompressorChoose
��  �ܣ���ʾѡ��ѹ�����Ի���
��  ����
         HWND ParentWnd���Ի��򸸴��ڵľ��
����ֵ���ɹ����� TRUE, ���򷵻�FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-10
ʱ  �䣺10:48:40
*******************************************************************************************************/
BOOL CCompressor::CompressorChoose(HWND ParentWnd, LPCSTR szWndTitle)
{
	CString str;
	if(!szWndTitle)
		str = _T("��ѡ��ѹ���� - ���ֹ�����");
	else
		str = szWndTitle;

	return ICCompressorChoose(ParentWnd, 
		ICMF_CHOOSE_ALLCOMPRESSORS | ICMF_CHOOSE_KEYFRAME | ICMF_CHOOSE_DATARATE | ICMF_CHOOSE_PREVIEW,
		NULL, NULL, &m_Compvars, (LPSTR)(LPCTSTR)str);
	 
}

/*******************************************************************************************************
��������DispConfigureDialog
��  �ܣ���ʾָ��ѹ���������öԻ���
��  ������
����ֵ���ɹ�����TRUE,���򷵻�FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-13
ʱ  �䣺11:42:55
*******************************************************************************************************/
BOOL CCompressor::DispConfigureDialog()
{
	if(ICQueryConfigure(m_hIC) == ICERR_OK)
	{
		if(ICConfigure(m_hIC, this) == ICERR_OK)
			return TRUE;
	}
	return FALSE;
}

/*******************************************************************************************************
��������Initialize
��  �ܣ���Ĭ�ϵ�ѹ��/��ѹ���� Divx MPEG-4(Fast-Motion)
��  ������
����ֵ���ɹ�����TRUE�����򷵻�FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-10
ʱ  �䣺12:10:39
*******************************************************************************************************/
BOOL CCompressor::Initialize()
{
	//��ѹ��/��ѹ����  Divx MPEG-4(Fast-Motion)ΪĬ�ϵ�ѹ��/��ѹ����
	m_hIC = ICOpen(ICTYPE_VIDEO, m_Compvars.fccHandler, ICMODE_COMPRESS | ICMODE_DECOMPRESS);
	if(!m_hIC)
	{
		TRACE(_T("��ѹ����ʧ��.\n"));
	}
	
	//*�õ�ѹ�����������ʽ
	if(ICERR_OK != ICCompressGetFormat(m_hIC, &m_bmpIn, &m_bmpOut))
	{
		TRACE(_T("�õ�ѹ������ʽʧ��.\n"));
		return FALSE;
	}
	//*/
	//*΢���H.263 codec��Ҫ��Ϣȷ�ϣ�
	//ICSendMessage(m_hIC,0x60c9,0xf7329ace,0xacdeaea2);

	m_Compvars.hic = m_hIC;
	m_Compvars.dwFlags = ICMF_COMPVARS_VALID;

	//ѹ����ʼ��
	if(!ICSeqCompressFrameStart(&m_Compvars, &m_bmpIn))
	{
		TRACE(_T("˳��ѹ����ʼ��ʧ��.\n"));
		return FALSE;
	}

	//��ѹ����ʼ��
	if(ICDecompressBegin(m_hIC, &m_bmpOut, &m_bmpIn) != ICERR_OK)
	{
	    TRACE(_T("˳���ѹ����ʼ��ʧ��.\n"));
		return FALSE;
	}
	return TRUE;
}

/*******************************************************************************************************
��������SeqCompress
��  �ܣ�˳��ѹ��
��  ����
         char *pIn��Ҫѹ��������
         UINT uInSize��Ҫѹ�������ݴ�С
         char *pOut��ѹ���������
         UINT uOutSize��ѹ��������ݴ�С
����ֵ������ɹ�����TRUE,���򷵻�FALSE.
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-10
ʱ  �䣺12:10:50
*******************************************************************************************************/
BOOL CCompressor::SeqCompress(void* pIn, DWORD dwInSize, void* pOut, DWORD* dwOutSize)
{
	if((pIn == NULL) || (pOut == NULL) || (m_hIC == NULL)
		|| (dwInSize != m_bmpIn.bmiHeader.biSizeImage))
		return FALSE;
			
	BOOL bKey;
	LONG uOutLen = 3000;
	void* p = ICSeqCompressFrame(&m_Compvars, 0, pIn, &bKey, &uOutLen);
	if(!p)
		return FALSE;
	if(!uOutLen)
		return FALSE;
	if(uOutLen > 3000)
		return FALSE;
	memcpy(pOut, p, uOutLen);
	*dwOutSize = uOutLen;
	return TRUE;
}

/*******************************************************************************************************
��������SeqDecompress
��  �ܣ�˳���ѹ��
��  ����
         void *pIn��ѹ������
         DWORD dwSize��ѹ�����ݵĳ���
         void *pOut����ѹ������
         DWORD* pdwOutSize����ѹ�����ݵĳ���
����ֵ���ɹ����� TRUE�����򷵻� FALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-10
ʱ  �䣺23:13:43
*******************************************************************************************************/
BOOL CCompressor::SeqDecompress(void *pIn, DWORD dwSize, void *pOut, DWORD* pdwOutSize)
{
	if((pIn == NULL) || (pOut == NULL) 
		|| (m_hIC == NULL) || (NULL == pdwOutSize))
		return FALSE;
	
	if(ICDecompress(m_hIC, ICDECOMPRESS_HURRYUP, 
		&m_bmpOut.bmiHeader, pIn, &m_bmpIn.bmiHeader, 
		pOut) != ICERR_OK)
	{
        TRACE(_T("��ѹ��ʧ��.\n"));
		return FALSE;
	}

	*pdwOutSize = m_bmpIn.bmiHeader.biSizeImage;

	return TRUE;
}

/*******************************************************************************************************
��������Destory
��  �ܣ��ر�ѹ����,�ͷ���Դ
��  ������
����ֵ���ɹ����� TRUE,���򷵻� FALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-11
ʱ  �䣺11:29:16
*******************************************************************************************************/
BOOL CCompressor::Destory()
{
	ICDecompressEnd(m_hIC);
	ICSeqCompressFrameEnd(&m_Compvars);
	ICCompressorFree(&m_Compvars); 
	int ierr = ICClose(m_hIC);
	TRACE(_T("�ر�ѹ����������ֵ:%d\n"), ierr);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// CACM Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CACM::CACM()
{

}

CACM::~CACM()
{

}

BOOL CALLBACK FormatEnumProc(HACMDRIVERID hadid, LPACMFORMATDETAILS pafd, DWORD dwInstance, DWORD fdwSupport) 
{
	TRACE("%4.4lXH; %s\n", pafd->dwFormatTag, pafd->szFormat);
	return TRUE; 
}

BOOL CALLBACK CodecsEnumProc(HACMDRIVERID hadid, DWORD dwInstance, DWORD fdwSupport)
{
	static int i;
	i ++;
	DWORD dwSize = 0;
	if (fdwSupport & ACMDRIVERDETAILS_SUPPORTF_CODEC)
	{
		TRACE("���ʽת��, %d\n", i);
		
		ACMDRIVERDETAILS acmdd;
		acmdd.cbStruct = sizeof(acmdd);
		MMRESULT mmr = acmDriverDetails(hadid, &acmdd, 0);
		if (mmr)
		{
			TRACE("����\n");
		}
		else {
			TRACE(" ȫ��:  %s\n", acmdd.szLongName);
			TRACE(" ����:   %s\n", acmdd.szFeatures);
			TRACE("%d\n", hadid);
		}
		
		HACMDRIVER had = NULL;
		mmr = acmDriverOpen(&had, hadid, 0);	//����������
		if (mmr)
		{
			TRACE("����\n");
		}
		else
		{
			mmr = acmMetrics((HACMOBJ)had, ACM_METRIC_MAX_SIZE_FORMAT, &dwSize);
			WAVEFORMATEX* pwf = (WAVEFORMATEX*) new BYTE[dwSize];
			memset(pwf, 0, dwSize);			
			pwf->cbSize = LOWORD(dwSize) - sizeof(WAVEFORMATEX);//��չ���ݵĴ�С		
			pwf->wFormatTag = WAVE_FORMAT_UNKNOWN;			
			ACMFORMATDETAILS fd;			
			memset(&fd, 0, sizeof(fd));			
			//���� acmFormatEnum ǰ,�����ĸ�������������
			fd.cbStruct = sizeof(fd); 
			fd.pwfx = pwf;
			fd.cbwfx = dwSize;			
			//��ѯ���и�ʽ
			fd.dwFormatTag = WAVE_FORMAT_UNKNOWN;			
			mmr = acmFormatEnum(had, &fd, FormatEnumProc, 0, 0);  			
			if (mmr)
			{
				TRACE("����\n");
			}
			delete []pwf;
		}		
	}
	return TRUE; 
}



void CACM::aaa()
{
	DWORD dwCodecs;
	acmMetrics(NULL, ACM_METRIC_COUNT_CODECS, &dwCodecs); 
	TRACE(_T(" �õ�����������:%d\n"), dwCodecs);
	acmDriverEnum(CodecsEnumProc, 0, 0); 

}

