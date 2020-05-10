/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：CSyntax.h
描  述：
版  本：2005.6.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年7月12日
时  间：19:06:08
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/
#pragma once

//#ifndef __AFXWIN_H__
//#error include 'stdafx.h' before including this file for PCH
//#endif

const int TAB = 9;    //制表符
const int CR = 13;    //回车符
const int LF = 10;    //换行符

extern "C" LONG _stdcall TrimString(BSTR lpIn, BSTR* lpOut);
extern "C" LONG _stdcall MatchSplitSymbol(LPTSTR lpszSource, 
										  LPCTSTR lpStr1,
										  LPCTSTR lpStr2, 
										  LPTSTR lpszBefor = NULL,
										  LPTSTR lpszBack = NULL);
extern "C" LONG _stdcall MatchSplitSymbolB(CComBSTR* lpszSource,
										   CComBSTR* lpStr1,
										   CComBSTR* lpStr2, 
										   CComBSTR* lpszBefor = NULL,
										   CComBSTR* lpszBack = NULL,
										   BOOL bQutation = TRUE,
										   BOOL bReversionQutation = FALSE);
extern "C" LONG _stdcall MatchSplitSymbolC(LPTSTR lpszSource, 
										   LPCTSTR lpStr1,
										   LPCTSTR lpStr2, 
										   LPTSTR lpszBefor = NULL,
										   LPTSTR lpszBack = NULL,
										   BOOL bQutation = TRUE,
										   BOOL bReversionQutation = FALSE);
extern "C" LONG _stdcall ReversionMatchSplitSymbolB(LPTSTR lpszSource,
													LONG * nSource = NULL,
													LPCTSTR lpStr1 = NULL,
													LPCTSTR lpStr2 = NULL,
													LPTSTR lpszBefor = NULL,
													LONG * nBefor = NULL,
													LPTSTR lpszBack = NULL,
													LONG * nBack = NULL,
													BOOL bQutation = FALSE
													);
extern "C" LONG _stdcall ReversionMatchSplitSymbol(LPTSTR lpszSource, 
												   LPCTSTR lpStr1,
												   LPCTSTR lpStr2, 
												   LPTSTR lpszBefor = NULL,
												   LPTSTR lpszBack = NULL,
												   BOOL bQutation = FALSE);

BOOL IsInclude(LPTSTR lpszOutCode, LPTSTR lpOut);

extern "C" BOOL WINAPI  Quotation(LPTSTR* lppIn, LPTSTR* lppOut, LPTSTR* lppStack);
BOOL SpaceFormat(LPTSTR* lppIn, LPTSTR* lppOut, LPTSTR* lppStack, BOOL* bFlag, LPTSTR lpOutCode);
extern "C" BOOL BigBracket(LPTSTR* lppIn, LPTSTR* lppOut, LPTSTR* lppStack, LPTSTR lpOutCode);
extern "C" BOOL Comma(LPTSTR* lppIn, LPTSTR* lppOut, LPTSTR* lppStack);
extern "C" BOOL LitterBracket(LPTSTR* lppIn, LPTSTR* lppOut, LPTSTR* lppStack);
BOOL Division(LPTSTR * lppIn, LPTSTR * lppOut, LPTSTR * lppStack, BOOL bFlag, LPTSTR lpOutCode, BOOL bComment = FALSE);
BOOL AddFormat(LPTSTR* lppIn, LPTSTR* lppOut, LPTSTR* lppStack);
BOOL BigSign(LPTSTR * lppIn, LPTSTR * lppOut, LPTSTR * lppStack, LPTSTR lpOutCode);
extern "C" void WINAPI Show(LPCTSTR szInput);

extern "C" long WINAPI FormatVCCodeA( /*in*/LPCTSTR szInCode, /*out*/LPTSTR szOutCode);
extern "C" long WINAPI FormatVCCodeW( /*in*/BSTR bszInCode, /*out*/BSTR* lpbszOutCode);
extern "C" long WINAPI ValidCCodeA(LPCTSTR lpszCode, LPTSTR lpszOut, BOOL bQutation = TRUE, BOOL bComment = FALSE);
extern "C" long WINAPI ValidCCodeW(BSTR bszCode, BSTR* lpbszOut, BOOL bQutation = TRUE, BOOL bComment = FALSE);
void SpaceC(LPTSTR* lppIn, LPTSTR* lppOut, LPTSTR lppCode);
void QuotationC(LPTSTR * lppIn, LPTSTR * lppOut, BOOL bQutation = TRUE);
void CommentC(LPTSTR * lppIn, LPTSTR * lppOut, BOOL bComment = FALSE);