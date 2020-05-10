/*******************************************************************************************************
�ļ�����Compress.h
��  �ܣ�ѹ��/��ѹ����ͷ�ļ�
        //��Ĭ�ϵ�ѹ��/��ѹ���� Divx MPEG-4(Fast-Motion)
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-11-11
ʱ  �䣺10:47:46
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
�ֱ��ʿ�ѡ��
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

    HIC m_hIC;            //ѹ�����ľ��
    COMPVARS m_Compvars;  //ѹ��������
    BITMAPINFO m_bmpIn;   //��Ƶ�����ʽ
    BITMAPINFO m_bmpOut;  //��Ƶ�����ʽ

};


class CACM  
{
public:
	void aaa();
	
	CACM();
	virtual ~CACM();

};

#endif // !defined(AFX_COMPRESS_H__EB38CA4B_4106_4C4C_9AEF_09D8CE760CBA__INCLUDED_)
