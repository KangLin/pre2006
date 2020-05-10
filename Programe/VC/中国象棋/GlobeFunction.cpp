/*******************************************************************************************************
文件名：GlobeFunction.cpp
功  能：完成全局函数的实现。
        此文件用于 中国象棋 和 中国象棋服务器 两个工程
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-12-23
时  间：19:24:54

FileName：GlobeFunction.cpp
Compiler：Visual C++ 6.0
Author：  KangLin
          Copyright 2004 KangLin
Date：    2004-12-23
Time：    19:24:54
*******************************************************************************************************/

#include "stdafx.h"
#include "GlobeFunction.h"

/*******************************************************************************************************
函数名：SplitString
功  能：分离以'\0'为分隔符的字符串
参  数：
         LPVOID lpInData：要分离的字符串
         INT* iInLen：要分离的字符串的长度,
                      函数成功执行后,此参数为剩下的字符串的长度(包括终结符'\0')。
         LPVOID lpOutData：分离出的第一个字符串
         INT* iOutLen：输出缓存区的长度。
		               函数执行完后为分离出的第一个字符串的长度(包括终结符'\0')。
					   如果分离出的长度比给定的长度小，则返回实际的需要的长度。
返回值：成功,分离出的字符串的长度,
        失败返回 0 ：输入格式错误，不包含分隔符'\0'
		         -1：输出缓存区的长度小于所需要的长度。
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-12
时  间：12:56:41
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
		ASSERT(FALSE);//输入格式错误
		return 0;
	}
	if(i > *iOutLen)  //给定的输入缓存区比需要的缓存区小
	{
		*iOutLen = i;
		return -1;
	}
	memcpy(lpOutData, lpInData, i);
	memcpy(lpInData, ++lp, *iInLen - i);
    TRACE(_T("%s(%d) : 剩余字符长度:%d\n"), __FILE__, __LINE__,  *iInLen - i);
    *iInLen = *iInLen - i;
	return i;
}

/*******************************************************************************************************
函数名：SplitString
功  能：分离以'\0'为分隔符的字符串
参  数：
         LPVOID lpInData：要分离的字符串
         INT* iInLen：要分离的字符串的长度,
                      函数成功执行后,此参数为剩下的字符串的长度(包括终结符'\0')。
返回值：成功，分离出的字符串。失败，NULL
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-28
时  间：10:38:55
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
		ASSERT(FALSE);//输入格式错误
        CString str;
		return str;
	}
    CString str((LPCTSTR)lpInData);
	memcpy(lpInData, ++lp, *iInLen - i);
    TRACE(_T("%s(%d) : 剩余字符长度:%d\n"), __FILE__, __LINE__,  *iInLen - i);
    *iInLen = *iInLen - i;
    return str;
}

/*******************************************************************************************************
函数名：GetCommandHeadLen
功  能：得到命令头的长度(命令和命令参数长度)
参  数：无
返回值：命令头的长度
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-26
时  间：11:45:02
*******************************************************************************************************/
int GetCommandHeadLen()
{
    return 2 * sizeof(long);
}

/*******************************************************************************************************
函数名：GetPara
功  能：得到参数的长度
参  数：
         int iLen：命令的长度
返回值：参数的长度
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-26
时  间：11:35:18
*******************************************************************************************************/
long GetPara(int iLen)
{
    return iLen - 2 * sizeof(long);
}

/*******************************************************************************************************
函数名：WriteCommandParaLen
功  能：写入命令参数的长度
参  数：
         LPVOID lpBuf：命令串
         int iLen：命令串的长度
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-26
时  间：11:39:55
*******************************************************************************************************/
void WriteCommandParaLen(LPVOID lpBuf, int iLen)
{
    BYTE* p = (BYTE*)lpBuf;
    long cmdlen = GetPara(iLen);
    memcpy(p + sizeof(long), &cmdlen, sizeof(long));
}

/*******************************************************************************************************
函数名：GetCommand
功  能：得到命令
参  数：
         LPVOID lpBuf：接收的数据，函数完成后返回命令的参数
         int* iLen：接收的数据的长度，函数完成后包含命令参数的长度
返回值：命令
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-28
时  间：10:20:48
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
函数名：TransparentBlt2
功  能：画透明图
参  数：
         HDC hdcDest：       目标DC
         int nXOriginDest：目标X偏移
         int nYOriginDest：目标Y偏移
         int nWidthDest：目标宽度
         int nHeightDest：目标高度
         HDC hdcSrc：源DC
         int nXOriginSrc：源X起点
         int nYOriginSrc：源Y起点
         int nWidthSrc：源宽度
         int nHeightSrc：源高度
         UINT crTransparent：透明色,COLORREF类型
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-9-1
时  间：19:50:00
*******************************************************************************************************/
void TransparentBlt2( HDC hdcDest,      // 目标DC
					 int nXOriginDest,   // 目标X偏移
					 int nYOriginDest,   // 目标Y偏移
					 int nWidthDest,     // 目标宽度
					 int nHeightDest,    // 目标高度
					 HDC hdcSrc,         // 源DC
					 int nXOriginSrc,    // 源X起点
					 int nYOriginSrc,    // 源Y起点
					 int nWidthSrc,      // 源宽度
					 int nHeightSrc,     // 源高度
					 UINT crTransparent  // 透明色,COLORREF类型
					 )
{

	HBITMAP hOldImageBMP, hImageBMP = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);	// 创建兼容位图
	HBITMAP hOldMaskBMP, hMaskBMP = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);			// 创建单色掩码位图
	HDC		hImageDC = CreateCompatibleDC(hdcDest);
	HDC		hMaskDC = CreateCompatibleDC(hdcDest);
	hOldImageBMP = (HBITMAP)SelectObject(hImageDC, hImageBMP);
	hOldMaskBMP = (HBITMAP)SelectObject(hMaskDC, hMaskBMP);
	
	// 将源DC中的位图拷贝到临时DC中
	if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
		BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, SRCCOPY);
	else
		StretchBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, 
		hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, SRCCOPY);
	
	// 设置透明色
	SetBkColor(hImageDC, crTransparent);

	// 生成透明区域为白色，其它区域为黑色的掩码位图
	BitBlt(hMaskDC, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCCOPY);
	
	// 生成透明区域为黑色，其它区域保持不变的位图
	SetBkColor(hImageDC, RGB(0,0,0));
	SetTextColor(hImageDC, RGB(255,255,255));
	BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

	// 透明部分保持屏幕不变，其它部分变成黑色
	SetBkColor(hdcDest,RGB(0xff,0xff,0xff));
	SetTextColor(hdcDest,RGB(0,0,0));
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);
	
	// "或"运算,生成最终效果
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCPAINT);
	
	SelectObject(hImageDC, hOldImageBMP);
	DeleteDC(hImageDC);
	SelectObject(hMaskDC, hOldMaskBMP);
	DeleteDC(hMaskDC);
	DeleteObject(hImageBMP);
	DeleteObject(hMaskBMP);
	
}
