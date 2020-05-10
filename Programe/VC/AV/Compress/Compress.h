/*******************************************************************************************************
文件名：Compress.h
功  能：压缩/解压缩器头文件
        //用默认的压缩/解压缩器 Divx MPEG-4(Fast-Motion)
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-11-11
时  间：10:47:46
*******************************************************************************************************/

#if !defined(AFX_COMPRESS_H__EB38CA4B_4106_4C4C_9AEF_09D8CE760CBA__INCLUDED_)
#define AFX_COMPRESS_H__EB38CA4B_4106_4C4C_9AEF_09D8CE760CBA__INCLUDED_

#include "..\..\File\fileex.h"
#include <vfw.h>
#include <msacm.h>
#include <mmsystem.h>
#include <mmreg.h>

#pragma comment(lib, "vfw32")
#pragma comment(lib, "msacm32")

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*******************************************************************************************************
分辨率可选：
160*120
320*240
352*288
640*288
*******************************************************************************************************/
#define QCIF_WIDTH  176
#define QCIF_HEIGHT 144

class CCompressor  
{
public:
	BOOL DispConfigureDialog();
	CCompressor();
	virtual ~CCompressor();
	BOOL CompressorChoose(HWND ParentWnd, LPCSTR szWndTitle = NULL);
	BOOL SeqCompress(void* pIn, DWORD uInSize, void* pOut, DWORD* uOutSize);
	BOOL SeqDecompress(void * pIn, DWORD dwSize, void* pOut, DWORD* pdwOutSize);
	
private:
	BOOL Initialize();
	BOOL Destory();
	BOOL InstallDevice();

    HIC m_hIC;            //压缩器的句柄
    COMPVARS m_Compvars;  //压缩器设置
    BITMAPINFO m_bmpIn;   //视频输入格式
    BITMAPINFO m_bmpOut;  //视频输出格式

};


class CACM  
{
public:
	void aaa();
	
	CACM();
	virtual ~CACM();

};

#endif // !defined(AFX_COMPRESS_H__EB38CA4B_4106_4C4C_9AEF_09D8CE760CBA__INCLUDED_)
