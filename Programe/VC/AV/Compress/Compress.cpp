/*******************************************************************************************************
文件名：Compress.cpp
功  能：压缩/解压缩器实现文件
        //用默认的压缩/解压缩器 Divx MPEG-4(Fast-Motion)
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-11-11
时  间：10:47:30
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
	//以下是完成 ===设置压缩器的默认参数=== 功能的语句块
	//

	ZeroMemory(&m_Compvars, sizeof(COMPVARS));
	m_Compvars.cbSize = sizeof(COMPVARS);
	m_Compvars.dwFlags = ICMF_COMPVARS_VALID ;
	m_Compvars.hic = m_hIC;
	m_Compvars.fccType = ICTYPE_VIDEO ;
	m_Compvars.fccHandler = 880175460;  //Divx MPEG-4(Fast-Motion);   859189837; //微软H.263;   
	m_Compvars.lpbiOut = 0;
	m_Compvars.lKey = 10;
	m_Compvars.lDataRate = 6;
	m_Compvars.lQ = 10000;

	//
	//以上是完成 ===设置压缩器的默认参数=== 功能的语句块
	//------------------------------------------------------------------------
	

	//------------------------------------------------------------------------
	//以下是完成 ===设置输入格式=== 功能的语句块
	//

	ZeroMemory(&m_bmpIn, sizeof(BITMAPINFO));
	m_bmpIn.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_bmpIn.bmiHeader.biWidth = QCIF_WIDTH;   //图像的宽度
	m_bmpIn.bmiHeader.biHeight = QCIF_HEIGHT; //图像的高度
	m_bmpIn.bmiHeader.biPlanes = 1;	
	m_bmpIn.bmiHeader.biBitCount = 24;	
	m_bmpIn.bmiHeader.biSizeImage = 76032;

	//
	//以上是完成 ===设置输入格式=== 功能的语句块
	//------------------------------------------------------------------------

	if(!Initialize())//用默认的压缩/解压缩器 Divx MPEG-4(Fast-Motion)
	{
		Destory();
		InstallDevice();
		if(!Initialize())
		{
			Destory();
			CompressorChoose(NULL);
			Initialize();
		}//if(!Initialize())
	}//if(!Initialize())//用默认的压缩/解压缩器 Divx MPEG-4(Fast-Motion)

}

CCompressor::~CCompressor()
{
	Destory();
}

/*******************************************************************************************************
函数名：InstallDevice
功  能：安装压缩器驱动程序,
        默认安装为 Divx MPEG-4(Fast-Motion),
		其动态链接库 divxc32f.dll 应与执行文件在同一目录
参  数：无
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-11
时  间：13:23:06
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
	TRACE(_T("压缩器安装返回值为:%d.\n"), result);
	return TRUE;
}

/*******************************************************************************************************
函数名：CompressorChoose
功  能：显示选择压缩器对话框
参  数：
         HWND ParentWnd：对话框父窗口的句柄
返回值：成功返回 TRUE, 否则返回FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-10
时  间：10:48:40
*******************************************************************************************************/
BOOL CCompressor::CompressorChoose(HWND ParentWnd, LPCSTR szWndTitle)
{
	CString str;
	if(!szWndTitle)
		str = _T("请选择压缩器 - 康林工作室");
	else
		str = szWndTitle;

	return ICCompressorChoose(ParentWnd, 
		ICMF_CHOOSE_ALLCOMPRESSORS | ICMF_CHOOSE_KEYFRAME | ICMF_CHOOSE_DATARATE | ICMF_CHOOSE_PREVIEW,
		NULL, NULL, &m_Compvars, (LPSTR)(LPCTSTR)str);
	 
}

/*******************************************************************************************************
函数名：DispConfigureDialog
功  能：显示指定压缩器的配置对话框
参  数：无
返回值：成功返回TRUE,否则返回FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-13
时  间：11:42:55
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
函数名：Initialize
功  能：用默认的压缩/解压缩器 Divx MPEG-4(Fast-Motion)
参  数：无
返回值：成功返回TRUE，否则返回FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-10
时  间：12:10:39
*******************************************************************************************************/
BOOL CCompressor::Initialize()
{
	//打开压缩/解压缩器  Divx MPEG-4(Fast-Motion)为默认的压缩/解压缩器
	m_hIC = ICOpen(ICTYPE_VIDEO, m_Compvars.fccHandler, ICMODE_COMPRESS | ICMODE_DECOMPRESS);
	if(!m_hIC)
	{
		TRACE(_T("打开压缩器失败.\n"));
	}
	
	//*得到压缩器的输出格式
	if(ICERR_OK != ICCompressGetFormat(m_hIC, &m_bmpIn, &m_bmpOut))
	{
		TRACE(_T("得到压缩器格式失败.\n"));
		return FALSE;
	}
	//*/
	//*微软的H.263 codec需要消息确认，
	//ICSendMessage(m_hIC,0x60c9,0xf7329ace,0xacdeaea2);

	m_Compvars.hic = m_hIC;
	m_Compvars.dwFlags = ICMF_COMPVARS_VALID;

	//压缩初始化
	if(!ICSeqCompressFrameStart(&m_Compvars, &m_bmpIn))
	{
		TRACE(_T("顺序压缩初始化失败.\n"));
		return FALSE;
	}

	//解压缩初始化
	if(ICDecompressBegin(m_hIC, &m_bmpOut, &m_bmpIn) != ICERR_OK)
	{
	    TRACE(_T("顺序解压缩初始化失败.\n"));
		return FALSE;
	}
	return TRUE;
}

/*******************************************************************************************************
函数名：SeqCompress
功  能：顺序压缩
参  数：
         char *pIn：要压缩的数据
         UINT uInSize：要压缩的数据大小
         char *pOut：压缩后的数据
         UINT uOutSize：压缩后的数据大小
返回值：如果成功返回TRUE,否则返回FALSE.
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-10
时  间：12:10:50
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
函数名：SeqDecompress
功  能：顺序解压缩
参  数：
         void *pIn：压缩数据
         DWORD dwSize：压缩数据的长度
         void *pOut：解压缩数据
         DWORD* pdwOutSize：解压缩数据的长度
返回值：成功返回 TRUE，否则返回 FALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-10
时  间：23:13:43
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
        TRACE(_T("解压缩失败.\n"));
		return FALSE;
	}

	*pdwOutSize = m_bmpIn.bmiHeader.biSizeImage;

	return TRUE;
}

/*******************************************************************************************************
函数名：Destory
功  能：关闭压缩器,释放资源
参  数：无
返回值：成功返回 TRUE,否则返回 FALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-11
时  间：11:29:16
*******************************************************************************************************/
BOOL CCompressor::Destory()
{
	ICDecompressEnd(m_hIC);
	ICSeqCompressFrameEnd(&m_Compvars);
	ICCompressorFree(&m_Compvars); 
	int ierr = ICClose(m_hIC);
	TRACE(_T("关闭压缩器。错误值:%d\n"), ierr);

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
		TRACE("多格式转换, %d\n", i);
		
		ACMDRIVERDETAILS acmdd;
		acmdd.cbStruct = sizeof(acmdd);
		MMRESULT mmr = acmDriverDetails(hadid, &acmdd, 0);
		if (mmr)
		{
			TRACE("出错\n");
		}
		else {
			TRACE(" 全称:  %s\n", acmdd.szLongName);
			TRACE(" 描述:   %s\n", acmdd.szFeatures);
			TRACE("%d\n", hadid);
		}
		
		HACMDRIVER had = NULL;
		mmr = acmDriverOpen(&had, hadid, 0);	//打开驱动程序
		if (mmr)
		{
			TRACE("出错\n");
		}
		else
		{
			mmr = acmMetrics((HACMOBJ)had, ACM_METRIC_MAX_SIZE_FORMAT, &dwSize);
			WAVEFORMATEX* pwf = (WAVEFORMATEX*) new BYTE[dwSize];
			memset(pwf, 0, dwSize);			
			pwf->cbSize = LOWORD(dwSize) - sizeof(WAVEFORMATEX);//扩展数据的大小		
			pwf->wFormatTag = WAVE_FORMAT_UNKNOWN;			
			ACMFORMATDETAILS fd;			
			memset(&fd, 0, sizeof(fd));			
			//调用 acmFormatEnum 前,以下四个参数必须设置
			fd.cbStruct = sizeof(fd); 
			fd.pwfx = pwf;
			fd.cbwfx = dwSize;			
			//查询所有格式
			fd.dwFormatTag = WAVE_FORMAT_UNKNOWN;			
			mmr = acmFormatEnum(had, &fd, FormatEnumProc, 0, 0);  			
			if (mmr)
			{
				TRACE("出错\n");
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
	TRACE(_T(" 得到驱动程序数:%d\n"), dwCodecs);
	acmDriverEnum(CodecsEnumProc, 0, 0); 

}

