/*******************************************************************************************************
�ļ�����VideoCapture.h
��  �ܣ���Ƶ�����ͷ�ļ�
��������Visual C++ 6.0
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-2
ʱ  �䣺21:39:23
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
�ֱ��ʿ�ѡ��
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
	
	HWND m_hCapWnd;       //���񴰿ھ��
	CStdioFile log;      //��־�ļ�
	CAPDRIVERCAPS caps;  
	CMutex protectframe;
	int avgaudiosize;
	BOOL isOver;
	CWnd* m_wndDisplay;   //��Ƶ������ʾ���ڵ�ָ��
	BITMAPINFOHEADER m_bmpheader;
	BITMAPINFO m_bmpInfo;  //λͼ��ʽ��������ʾʱ��ͼ

	CVideoCapture();
	virtual ~CVideoCapture();

	//��Ҫ����
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

	//���Ʋ���
	BOOL StartCapture(BOOL bToFile = FALSE);
	BOOL StopCapture();

	//Callback functions
    //friend LRESULT CALLBACK OnCaptureError(HWND hwnd, int errid, LPSTR errtext);
    friend LRESULT CALLBACK OnCaptureVideo(HWND hWnd, LPVIDEOHDR lpheader) ;
    //friend LRESULT CALLBACK OnCaptureFrame(HWND hWnd, LPVIDEOHDR lpheader);
    //friend LRESULT CALLBACK OnCaptureWave(HWND hWnd, LPWAVEHDR lpheader);

};


#endif // !defined(VIDEOCAPTURE_H)
