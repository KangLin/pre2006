/*******************************************************************************************************
文件名：VideoCapture.cpp
功  能：捕获视频帧的实现文件
使  用；1、先定义：CVideoCapture* m_VideoCapture;
        2、在容器类的OnCreate()函数中,建立对象
	    m_VideoCapture = new CVideoCapture;
		if(m_VideoCapture)
		{
		    3、初始化
			m_VideoCapture->Initialize();
			4、设置父窗口对象
			m_VideoCapture->SetDisplayWindow(this);
			5、把位图结构传给父窗口
			m_bmpInfo = m_VideoCapture->m_bmpInfo;
		}
		6、在函数 LRESULT CALLBACK OnCaptureVideo(HWND hwnd, LPVIDEOHDR lphdr)中
		   加入对视频数据的处理
		7、在开始捕获视频处调用：
		    m_VideoCapture->StartCapture();
		8、在结束视频捕获处调用：
            m_VideoCapture->StopCapture();
		9、在容器类的Destory()中调用：
		    delete m_VideoCapture;
编译器：Visual C++ 6.0
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-2
时  间：16:22:48
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
函数名：Initialize
功  能：视频初始化
参  数：无
返回值：成功返回TRUE，否则返回FALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-2
时  间：15:25:48
*******************************************************************************************************/
BOOL CVideoCapture::Initialize()
{
	TCHAR devname[100],devversion[100];
	TCHAR str[200];
	INT index=0;
	
	//创建一个捕获窗口(实际上就是一个窗口类的实例)
	m_hCapWnd = capCreateCaptureWindow(_T("视频捕获窗口"), 
		WS_POPUP,// | WS_OVERLAPPEDWINDOW  | WS_VISIBLE,//设置这此参数后就和普通的窗口一样
		0, 0, 0, 0, //QCIF_WIDTH, QCIF_HEIGHT,
		0, 0);
	if(m_hCapWnd == NULL)
	{
		TRACE("%s", _T("不能建立捕获窗口。\n"));
		return FALSE;
	}	

	/*******************************************************************************************************
      设置用户数据
      作用是：把用户数据保存到捕获窗口，以便在回调函数中，
	  能用 capGetUserData 得到这个用户数据。
	*******************************************************************************************************/
	if(!capSetUserData(m_hCapWnd, this))
		TRACE("%s", _T("错误,捕获流正在执行。不能设置用户数据。\n"));

	//设置捕获窗口的回调函数，这一步也可放在连接后的设置参数中
    //设置捕获窗口捕获时的视频回调函数
	//注意：在 Destroy 函数中要断开回调函数
    if(!capSetCallbackOnVideoStream(m_hCapWnd, OnCaptureVideo))
		TRACE("%s", _T("视频流回调函数安装失败。\n")); 
	
	/*******************************************************************************************************
	  得到捕获驱动的描述，
	  capGetDriverDescription 先查找即插即用的捕获设备的驱动，
	  再查注册表中的捕获驱动列表，再查文件 SYSTEM。INI 中的设备驱动列表
	  范围[0，9]
	  可以用一个枚举出系统中所有捕获设备驱动程序的列表。
	  例如：
	  for(int i = 0; i < 10; i++)
	  {
	      capGetDriverDescription(i, devname, 100, devversion,100);
		  TRACE(_T("设备驱动程序名 = %s 版本号 = %s \n"), devname, devversion);
	  }
	*******************************************************************************************************/
	if(!capGetDriverDescription(index, devname, 100, devversion, 100))
		TRACE("%s", _T("系统中没有视频捕获设备驱动程序。\n"));
	_stprintf(str, _T("设备驱动程序名 = %s 版本号 = %s \n"), devname, devversion);
	TRACE("%s", str);
	
	//捕捕获窗口和捕获驱动连接
	if(!capDriverConnect(m_hCapWnd, index))
	{
		//设备可能已经找开或者它在最后时没有适当的关闭。
		AfxMessageBox(_T("不能打开视频捕获驱动。"));
		TRACE("%s", _T("不能打开视频捕获驱动。\n"));
		m_hCapWnd = NULL;
		return FALSE;
	}
	
	//设置捕获窗口参数	
	if(SetCapturePara() == FALSE)
	{
		TRACE("%s", _T("捕获驱动参数设置失败。\n"));
		capDriverDisconnect(m_hCapWnd);  //断开与捕获设备的连接
		return FALSE;
	}

	return TRUE;
}

/*******************************************************************************************************
函数名：SetCapturePara
功  能：设置捕流的获参数
参  数：无
返回值：如果成功返回 TRUE，否则，返回 FALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-2
时  间：16:15:01
*******************************************************************************************************/
BOOL  CVideoCapture::SetCapturePara()
{
	//------------------------------------------------------------------------
	//以下是完成 ===设置捕获窗口的工作模式=== 功能的语句块
	//

	/*视频捕获驱动对进入的视频流有两种工作模式: Preview模式和overlay模式, 如果一个捕获驱动能够执行两种方法, 用户可以在其中选择一种.Preview模式把从捕获硬件传来的数据送入系统内存并使用图形设备介面(GDI)将数字化帧显示在捕获窗口内. 应用程序可以在父窗口失去焦点时减缓显示速度, 当重新又得到焦点后加快显示速度, 此种模式要占用大量CPU时间.
	//设置为 Preview 模式,这种模式捕获窗口能直接显示捕获图形
	//在建立捕获窗口时加上窗口类型设为可显示的 WS_OVERLAPPEDWINDOW  | WS_VISIBLE,设置捕获窗口的大小
	capPreview(m_hCapWnd, true);
    capPreviewScale(m_hCapWnd, true);
	//设置为 overlay 模式
    //capOverlay(m_hCapWnd, true);
	//*/

	//
	//以上是完成 ===设置捕获窗口的工作模式=== 功能的语句块
	//------------------------------------------------------------------------


	//------------------------------------------------------------------------
	//以下是完成 ===设置捕获窗口的参数(这一步是必须的)=== 功能的语句块
	//

	CAPTUREPARMS CapParms = {0};	

    //得到捕获流参数
	if(!capCaptureGetSetup(m_hCapWnd, &CapParms, sizeof(CapParms)))
    {
		TRACE("%s", _T("不能得到捕获流参数。\n"));
		return FALSE;
	}

	//设置捕获流参数
	//CapParms.dwRequestMicroSecPerFrame *= 2;   //设置捕获速率,默认为 15帧/秒
	CapParms.vKeyAbort = 0;                    //停止用按键取消
	CapParms.fAbortLeftMouse = FALSE;          //停止用鼠标左键取消
	CapParms.fAbortRightMouse = FALSE;         //停止用鼠标右键取消
	CapParms.fYield = TRUE;                    //允许捕获窗口产生后台线程,默认值为FALSE,
	                                           //捕获开始后,应用程序将不响应其它的
	CapParms.fCaptureAudio = FALSE;            //不捕获音频
	CapParms.wPercentDropForError = 50;        //允许最大丢失多少帧
	
	if(capCaptureSetSetup(m_hCapWnd, &CapParms, sizeof(CapParms)) == FALSE)
	{
		TRACE("%s", _T("设置捕获流参数失败。\n"));
		return FALSE;
	}

	//
	//以上是完成 ===设置捕获窗口的参数(这一步是必须的)=== 功能的语句块
	//------------------------------------------------------------------------


	/*------------------------------------------------------------------------
	//以下是完成 ===用对话设置参数=== 功能的语句块
	//

	CAPDRIVERCAPS capdrivercaps;
	capDriverGetCaps(m_hCapWnd, &capdrivercaps, sizeof(CAPDRIVERCAPS));

	/*1、设置视频源
	if(capdrivercaps.fHasDlgVideoSource)
	{
		capDlgVideoSource(m_hCapWnd);
	}
	else
	{
		TRACE(_T("不支持视频源设置对话框\n"));
		TRACE("%s", _T("不支持视频源设置对话框\n"));
	}
	//*/
	
	/*2、设置视频格式
	if(capdrivercaps.fHasDlgVideoFormat)
	{
		capDlgVideoFormat(m_hCapWnd);
	}
	else
	{
		TRACE(_T("不支持视频格式设置对话框\n"));
		TRACE("%s", _T("不支持视频格式设置对话框\n"));
	}
	//*/

	//3、设置视频压缩程序和压缩质量
	//capDlgVideoCompression(m_hCapWnd);

	/*4、设置视频显示
	if(capdrivercaps.fHasDlgVideoDisplay)
	{
		capDlgVideoDisplay(m_hCapWnd);
	}
	else
	{
		TRACE(_T("不支持视频显示对话框\n"));
	}
	//*/

	//
	//以上是完成 ===用对话设置参数=== 功能的语句块
	//------------------------------------------------------------------------

	//得到视频格式
	capGetVideoFormat(m_hCapWnd, &m_bmpInfo, sizeof(m_bmpInfo));
	
	//------------------------------------------------------------------------
	//以下是完成 ===设置视频格式=== 功能的语句块
	//

	m_bmpInfo.bmiHeader.biWidth = IMAGE_WIDTH;
	m_bmpInfo.bmiHeader.biHeight = IMAGE_HEIGHT;
	m_bmpInfo.bmiHeader.biPlanes = 1;
	m_bmpInfo.bmiHeader.biBitCount = 24;
	m_bmpInfo.bmiHeader.biCompression = 0;

	//设置视频格式
	if(capSetVideoFormat(m_hCapWnd, &m_bmpInfo, sizeof(m_bmpInfo)))
	{
		TRACE("%s", _T("视频参数流设置完成。\n"));
	}
	else
	{
		TRACE("%s", _T("不能设置视频流参数。\n"));
		//断开设备驱动与捕获窗口的连接
		if(!capDriverDisconnect(m_hCapWnd))
		{
			TRACE("%s", _T("不能设置视频流参数且不能把捕获窗口与捕获驱动断开。\n"));
		}
	    return FALSE;
	}

	//
	//以上是完成 ===设置视频格式=== 功能的语句块
	//------------------------------------------------------------------------

	return TRUE;
}

/*******************************************************************************************************
函数名：Destroy
功  能：停止捕获程序并且断开设备驱动连接、关闭并销毁捕获窗口
参  数：无
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-2
时  间：16:24:41
*******************************************************************************************************/
void CVideoCapture::Destroy()
{
	if(m_hCapWnd == NULL) 
		return;
    
    StopCapture();

	//取消捕获进程    
	capCaptureAbort(m_hCapWnd);
     
	Sleep(300);		// 延时     

  	//断开视频捕获回调函数
	capSetCallbackOnVideoStream(m_hCapWnd, NULL);  
				
	//最后断开捕获窗口与设备驱动连接
    if(!capDriverDisconnect(m_hCapWnd))
	{
		TRACE("%s", _T("不能把捕获窗口与捕获驱动断开。\n"));
	}

	//注意:关闭并销毁捕获窗口,否则的话调试时结束时出现异常
	::SendMessage(m_hCapWnd, WM_CLOSE, NULL, NULL);
	ASSERT(m_hCapWnd);
	//DestroyWindow(m_hCapWnd);
}

/*******************************************************************************************************
函数名：StartCapture
功  能：开始从 webcam 捕获帧
参  数：
        bToFile:为TRUE捕获流发送到文件,为FALSE捕获流不发送到文件。默认值为FALSE。
返回值：成功返回 TRUE，否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-2
时  间：16:45:31
*******************************************************************************************************/
BOOL CVideoCapture::StartCapture(BOOL bToFile)
{
	//开始捕获……
	if(bToFile)
	{   //捕获到文件中
		if(capCaptureSequence(m_hCapWnd) == FALSE)
		{
			TRACE("%s", _T("顺序捕获失败...\n"));
			return FALSE;
		}
	}
	else
	{	//不捕获到文件
		if(capCaptureSequenceNoFile(m_hCapWnd) == FALSE)
		{
			TRACE("%s", _T("顺序捕获失败...\n"));
			return FALSE;
		}
		
	}
	return TRUE;
}

/*******************************************************************************************************
函数名：StopCapture
功  能：停止捕获操作
参  数：无
返回值：成功返回 TRUE，否则返回，FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-2
时  间：17:18:35
*******************************************************************************************************/
BOOL CVideoCapture::StopCapture()
{	
	//capCaptureStop与capCaptureAbort不同之处
	//在于后者在消息被发送前，停止音频捕获。
	capCaptureStop(m_hCapWnd);
	capCaptureAbort(m_hCapWnd);
	Sleep(300);	
	return TRUE;
}

/*******************************************************************************************************
函数名：OnCaptureVideo
功  能：当视频帧被驱动程序捕获时调用此函数。
参  数：
         HWND hwnd：捕获窗口的句柄
         LPVIDEOHDR lphdr：回传的一个 VIDEDHDR 结构
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-2
时  间：17:50:22
*******************************************************************************************************/
LRESULT CALLBACK OnCaptureVideo(HWND hwnd, LPVIDEOHDR lphdr)
{
	CVideoCapture *vidcap = (CVideoCapture *)capGetUserData(hwnd);
	if(vidcap != NULL )
	{
#ifdef _PLAYVIDEOWND
		//TODO:在这里加入对视频帧频的处理代码
        ((CPlayVideoWnd*)vidcap->m_wndDisplay)->Display(lphdr->lpData, lphdr->dwBytesUsed);
#endif
#ifdef _PLAYVIDEOCTROL
        ((CVideoCtrl*)vidcap->m_wndDisplay)->Display(lphdr->lpData, lphdr->dwBytesUsed);
#endif
	}
	return TRUE;
}

/*******************************************************************************************************
函数名：AllocateMemory
功  能：为DIB 图像分配内存
参  数：
         PBITMAPINFO &bmpinfo：
返回值：成功，返回分配内在的大小，失败返回-1
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-2
时  间：17:44:11
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


	_stprintf(str, _T("格式的尺寸 = %d, 图象的尺寸 = %d , fun_size = %d "),
			 size1,size2, capGetVideoFormatSize(m_hCapWnd));
	TRACE("%s", str);

	bmpinfo=(BITMAPINFO *) new BYTE[size];
	
	if(bmpinfo == NULL)
	{
		AfxMessageBox(_T("不能分配内存。"));
		return -1;
	}

	memset(bmpinfo, 0, sizeof(*bmpinfo));

	capGetVideoFormat(m_hCapWnd, bmpinfo, sizeof(*bmpinfo));

	return size1;
}

/*******************************************************************************************************
函数名：getFormatSize
功  能：计算 DIB 图像格式的尺寸
参  数：
         BITMAPINFO bmp：
返回值：DIB 图像格式的尺寸
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-2
时  间：17:47:46
*******************************************************************************************************/
int CVideoCapture::getFormatSize(BITMAPINFO bmp)
{
	INT size;

	size = (bmp.bmiHeader.biSize != 0) ? bmp.bmiHeader.biSize : sizeof(BITMAPINFOHEADER);

	//return (size+ bmp.bmiHeader.biClrUsed *sizeof(RGBQUAD));

	return size; //RGBQUAD is absent for 24 bit bmp image.
}

/*******************************************************************************************************
函数名：getImageSize
功  能：得到图像的尺寸
参  数：
         BITMAPINFO bmp：
返回值：图像的尺寸
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-2
时  间：17:49:25
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