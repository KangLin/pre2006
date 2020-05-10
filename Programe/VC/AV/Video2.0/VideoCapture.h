/*******************************************************************************************************
文件名：VideoCapture.h
功  能：视频捕获的头文件
编译器：Visual C++ 6.0
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-2
时  间：21:39:23
*******************************************************************************************************/

#if !defined(VIDEOCAPTURE_H)
#define VIDEOCAPTURE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<vfw.h>
#include<afxmt.h>
#include<afxole.h>

#pragma comment(lib,"vfw32")
#pragma comment(lib,"winmm")

/*******************************************************************************************************
分辨率可选：
160*120
320*240
352*288
640*288
*******************************************************************************************************/
#define QCIF_WIDTH  176
#define QCIF_HEIGHT 144

#define IMAGE_WIDTH       QCIF_WIDTH
#define IMAGE_HEIGHT      QCIF_HEIGHT
    
class CVideoCapture  
{
public:
	
	HWND m_hCapWnd;       //捕获窗口句柄
	CStdioFile log;      //日志文件
	CAPDRIVERCAPS caps;  
	CMutex protectframe;
	int avgaudiosize;
	BOOL isOver;
	CWnd* m_wndDisplay;   //视频数据显示窗口的指针
	BITMAPINFOHEADER m_bmpheader;
	BITMAPINFO m_bmpInfo;  //位图格式，用于显示时画图

	CVideoCapture();
	virtual ~CVideoCapture();

	//主要操作
	BOOL Initialize();
	void SetDisplayWindow(CWnd *pwnd);	
	void Destroy();

private:
	BOOL  SetCapturePara();

public:
	
	void GetDriverCaps();
	void SetAudioFormat();
	int AllocateMemory(PBITMAPINFO &bmpinfo);
	int getFormatSize(BITMAPINFO bmp);
    int getImageSize(BITMAPINFO bmp);

	//控制操作
	BOOL StartCapture(BOOL bToFile = FALSE);
	BOOL StopCapture();

	//Callback functions
    //friend LRESULT CALLBACK OnCaptureError(HWND hwnd, int errid, LPSTR errtext);
    friend LRESULT CALLBACK OnCaptureVideo(HWND hWnd, LPVIDEOHDR lpheader) ;
    //friend LRESULT CALLBACK OnCaptureFrame(HWND hWnd, LPVIDEOHDR lpheader);
    //friend LRESULT CALLBACK OnCaptureWave(HWND hWnd, LPWAVEHDR lpheader);

};


#endif // !defined(VIDEOCAPTURE_H)
