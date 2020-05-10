/*******************************************************************************************************
�ļ�����GlobeFunction.cpp
��  �ܣ����ȫ�ֺ�����ʵ�֡�
        ���ļ����� �й����� �� �й���������� ��������
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-12-23
ʱ  �䣺19:24:54

FileName��GlobeFunction.cpp
Compiler��Visual C++ 6.0
Author��  KangLin
          Copyright 2004 KangLin
Date��    2004-12-23
Time��    19:24:54
*******************************************************************************************************/

#include "stdafx.h"
#include "GlobeFunction.h"

/*******************************************************************************************************
��������SplitString
��  �ܣ�������'\0'Ϊ�ָ������ַ���
��  ����
         LPVOID lpInData��Ҫ������ַ���
         INT* iInLen��Ҫ������ַ����ĳ���,
                      �����ɹ�ִ�к�,�˲���Ϊʣ�µ��ַ����ĳ���(�����ս��'\0')��
         LPVOID lpOutData��������ĵ�һ���ַ���
         INT* iOutLen������������ĳ��ȡ�
		               ����ִ�����Ϊ������ĵ�һ���ַ����ĳ���(�����ս��'\0')��
					   ���������ĳ��ȱȸ����ĳ���С���򷵻�ʵ�ʵ���Ҫ�ĳ��ȡ�
����ֵ���ɹ�,��������ַ����ĳ���,
        ʧ�ܷ��� 0 �������ʽ���󣬲������ָ���'\0'
		         -1������������ĳ���С������Ҫ�ĳ��ȡ�
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-12
ʱ  �䣺12:56:41
*******************************************************************************************************/
int SplitString(LPVOID lpInData, INT* iInLen, LPVOID lpOutData, INT* iOutLen)
{
	ASSERT(lpInData && iInLen && (*iInLen > 0) && lpOutData && iOutLen && (*iOutLen > 0));
	int i = 1;
	BYTE* lp = (BYTE*)lpInData;
    while(i <= *iInLen && *lp != 0)
	{
		lp++;
		i++;
	}
	if(i > *iInLen)
	{
		ASSERT(FALSE);//�����ʽ����
		return 0;
	}
	if(i > *iOutLen)  //���������뻺��������Ҫ�Ļ�����С
	{
		*iOutLen = i;
		return -1;
	}
	memcpy(lpOutData, lpInData, i);
	memcpy(lpInData, ++lp, *iInLen - i);
    TRACE(_T("%s(%d) : ʣ���ַ�����:%d\n"), __FILE__, __LINE__,  *iInLen - i);
    *iInLen = *iInLen - i;
	return i;
}

/*******************************************************************************************************
��������SplitString
��  �ܣ�������'\0'Ϊ�ָ������ַ���
��  ����
         LPVOID lpInData��Ҫ������ַ���
         INT* iInLen��Ҫ������ַ����ĳ���,
                      �����ɹ�ִ�к�,�˲���Ϊʣ�µ��ַ����ĳ���(�����ս��'\0')��
����ֵ���ɹ�����������ַ�����ʧ�ܣ�NULL
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-28
ʱ  �䣺10:38:55
*******************************************************************************************************/
CString SplitString(LPVOID lpInData, INT *iInLen)
{
    ASSERT(lpInData && iInLen && (*iInLen > 0));
	int i = 1;
	BYTE* lp = (BYTE*)lpInData;
    while(i <= *iInLen && *lp != 0)
	{
		lp++;
		i++;
	}
	if(i > *iInLen)
	{
		ASSERT(FALSE);//�����ʽ����
        CString str;
		return str;
	}
    CString str((LPCTSTR)lpInData);
	memcpy(lpInData, ++lp, *iInLen - i);
    TRACE(_T("%s(%d) : ʣ���ַ�����:%d\n"), __FILE__, __LINE__,  *iInLen - i);
    *iInLen = *iInLen - i;
    return str;
}

/*******************************************************************************************************
��������GetCommandHeadLen
��  �ܣ��õ�����ͷ�ĳ���(����������������)
��  ������
����ֵ������ͷ�ĳ���
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-26
ʱ  �䣺11:45:02
*******************************************************************************************************/
int GetCommandHeadLen()
{
    return 2 * sizeof(long);
}

/*******************************************************************************************************
��������GetPara
��  �ܣ��õ������ĳ���
��  ����
         int iLen������ĳ���
����ֵ�������ĳ���
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-26
ʱ  �䣺11:35:18
*******************************************************************************************************/
long GetPara(int iLen)
{
    return iLen - 2 * sizeof(long);
}

/*******************************************************************************************************
��������WriteCommandParaLen
��  �ܣ�д����������ĳ���
��  ����
         LPVOID lpBuf�����
         int iLen������ĳ���
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-26
ʱ  �䣺11:39:55
*******************************************************************************************************/
void WriteCommandParaLen(LPVOID lpBuf, int iLen)
{
    BYTE* p = (BYTE*)lpBuf;
    long cmdlen = GetPara(iLen);
    memcpy(p + sizeof(long), &cmdlen, sizeof(long));
}

/*******************************************************************************************************
��������GetCommand
��  �ܣ��õ�����
��  ����
         LPVOID lpBuf�����յ����ݣ�������ɺ󷵻�����Ĳ���
         int* iLen�����յ����ݵĳ��ȣ�������ɺ������������ĳ���
����ֵ������
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-28
ʱ  �䣺10:20:48
*******************************************************************************************************/
long GetCommand(LPVOID lpBuf, int* iLen)
{
    long cmd;
    BYTE* p = (BYTE*) lpBuf;
    ASSERT(lpBuf && *(p + *iLen - 1) == 0);
    memcpy(&cmd, lpBuf, sizeof(long));
    *iLen -= GetCommandHeadLen();
    memcpy(lpBuf, p + GetCommandHeadLen(), *iLen);
    return cmd;
}

/*******************************************************************************************************
��������TransparentBlt2
��  �ܣ���͸��ͼ
��  ����
         HDC hdcDest��       Ŀ��DC
         int nXOriginDest��Ŀ��Xƫ��
         int nYOriginDest��Ŀ��Yƫ��
         int nWidthDest��Ŀ����
         int nHeightDest��Ŀ��߶�
         HDC hdcSrc��ԴDC
         int nXOriginSrc��ԴX���
         int nYOriginSrc��ԴY���
         int nWidthSrc��Դ���
         int nHeightSrc��Դ�߶�
         UINT crTransparent��͸��ɫ,COLORREF����
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-9-1
ʱ  �䣺19:50:00
*******************************************************************************************************/
void TransparentBlt2( HDC hdcDest,      // Ŀ��DC
					 int nXOriginDest,   // Ŀ��Xƫ��
					 int nYOriginDest,   // Ŀ��Yƫ��
					 int nWidthDest,     // Ŀ����
					 int nHeightDest,    // Ŀ��߶�
					 HDC hdcSrc,         // ԴDC
					 int nXOriginSrc,    // ԴX���
					 int nYOriginSrc,    // ԴY���
					 int nWidthSrc,      // Դ���
					 int nHeightSrc,     // Դ�߶�
					 UINT crTransparent  // ͸��ɫ,COLORREF����
					 )
{

	HBITMAP hOldImageBMP, hImageBMP = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);	// ��������λͼ
	HBITMAP hOldMaskBMP, hMaskBMP = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);			// ������ɫ����λͼ
	HDC		hImageDC = CreateCompatibleDC(hdcDest);
	HDC		hMaskDC = CreateCompatibleDC(hdcDest);
	hOldImageBMP = (HBITMAP)SelectObject(hImageDC, hImageBMP);
	hOldMaskBMP = (HBITMAP)SelectObject(hMaskDC, hMaskBMP);
	
	// ��ԴDC�е�λͼ��������ʱDC��
	if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
		BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, SRCCOPY);
	else
		StretchBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, 
		hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, SRCCOPY);
	
	// ����͸��ɫ
	SetBkColor(hImageDC, crTransparent);

	// ����͸������Ϊ��ɫ����������Ϊ��ɫ������λͼ
	BitBlt(hMaskDC, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCCOPY);
	
	// ����͸������Ϊ��ɫ���������򱣳ֲ����λͼ
	SetBkColor(hImageDC, RGB(0,0,0));
	SetTextColor(hImageDC, RGB(255,255,255));
	BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

	// ͸�����ֱ�����Ļ���䣬�������ֱ�ɺ�ɫ
	SetBkColor(hdcDest,RGB(0xff,0xff,0xff));
	SetTextColor(hdcDest,RGB(0,0,0));
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);
	
	// "��"����,��������Ч��
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCPAINT);
	
	SelectObject(hImageDC, hOldImageBMP);
	DeleteDC(hImageDC);
	SelectObject(hMaskDC, hOldMaskBMP);
	DeleteDC(hMaskDC);
	DeleteObject(hImageBMP);
	DeleteObject(hMaskBMP);
	
}
