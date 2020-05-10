/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：CSyntax.cpp
描  述：C语言语法分析
思  路：主要是由FormatVCCodeA函数输入字符串，并根据分隔符分析格式。
函数例表：
    FormatVCCodeW       ;自动格式化 VC 代码（支持UCOIDE）
    FormatVCCodeA       ;自动格式化 VC 代码
    ValidCCode          ;去掉代码中的多余空格、制表符、换行符、注释、连接符（“\”）、前、后导空格
    MatchSplitSymbol    ;匹配指定的分隔符号
    TrimSpace           ;除去字符串中的空格
版  本：2005.6.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年7月12日
时  间：19:05:23
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/
#include "stdafx.h"
#ifdef __LIMIT__
#include "Syntax.h"
#else
#include "CSyntax.h"
#endif

/*******************************************************************************************************
函数名：DeleteSpace
功  能：删除给定字符串中多余的空字符、制表符、回车符、换行符  
参  数：
         LPCTSTR pszIn：输入字符串指针
         LPTSTR pszOut：输出字符串指针
返回值：成功返回非零,失败返回零
版  本：1.0.0.1
作  者：康 林
时  间：2005-5-4 14:32:32
*******************************************************************************************************/
LONG _stdcall DeleteSpace(LPCTSTR pszIn, LPTSTR pszOut)
{ 
    LPTSTR pTmpIn, pTmpOut;
    INT iLen;
    TCHAR ch;

    ASSERT(pszIn != NULL && pszOut != NULL);

    pTmpIn = (LPTSTR)pszIn;
    pTmpOut = pszOut;
    iLen = _tcslen(pszIn);
    ZeroMemory(pszOut, iLen + 1);
    while(*pTmpIn != NULL)
    {
        ch = *pTmpIn;
        if(TAB == ch || CR == ch || LF == ch)
        {
            ch = _T(' ');
		}//结束 if(ch == TAB)
        if(ch == _T(' ') && *(pTmpOut - 1) == _T(' ') && pTmpOut != pszIn)
        {
            pTmpIn++;
            continue;
        }
        else
        {
            *pTmpOut = ch;
            pTmpOut++;
            pTmpIn++;
		}//结束 if(ch == _T(' ') && *(pTmpOut - 1) == _T(' ') && pTmpOut != pszIn)
	}//结束 while(*pTmpOut != NULL) 

    return _tcslen(pszOut);
}

/*******************************************************************************************************
函数名：DeleteSpace
功  能：删除空格
参  数：
         LPTSTR pszCode：字符串
返回值：成功返回字符串的长度，失败，返回0
版  本：1.0.0.1
作  者：康  林
时  间：2005-5-4 19:35:30
*******************************************************************************************************/
LONG _stdcall DeleteSpace(LPTSTR pszCode)
{
    LPTSTR pszTmp, p, pOut;
    int iLen;
    TCHAR ch;

    ASSERT(pszCode != NULL);

    iLen = _tcslen(pszCode);
    pszTmp = new TCHAR[iLen + sizeof(TCHAR)];
    if(!pszTmp)
    {
        TRACE(_T("%s(%d) : 分配内存失败\n"), __FILE__, __LINE__);
        return 0;
    } //结束 if(!pszTmp)
    ::ZeroMemory(pszTmp, iLen);

    pOut = pszTmp;
    p = pszCode;

    while(p < pszCode + iLen + sizeof(TCHAR))
    {
        ch = *p;
        if(TAB == ch || CR == ch || LF == ch)
        {
            ch = ' ';
        }//结束 if(ch == TAB)
        if(ch == ' ' && * (pOut - 1) == ' ')
        {
            p++;
            continue;
        }
        else
        {
            *pOut = ch;
            pOut++;
            p++;
        }//结束 if(*p == ' ' && pOut== ' ')        
    } //结束 while(p < pszCode + iLen)
    _tcscpy(pszCode, pszTmp);
    delete []pszTmp;
    return _tcslen(pszCode);
}

/*******************************************************************************************************
函数名：TrimString
描  述：去掉前导、后导空字符、制表符、回车换行符
参  数：
        BSTR bszIn    ：要去掉空字符的字符串
		BSTR * pbszOut：去掉后的空字符的字符串
返回值：类型为 LONG 。失败，返回0
        成功，返回字符串的长度(以字节为单位)
版  本：2005.6.0.1
作  者：康  林
时  间：2005年7月31日 18:06:58
*******************************************************************************************************/
extern "C" LONG _stdcall TrimString(BSTR bszIn, BSTR * pbszOut)
{
    INT iLen, iR;
   
    ASSERT(pbszOut != NULL);

	LPTSTR lpszOut = new TCHAR[2 * (::SysStringByteLen(bszIn) + sizeof(TCHAR))];
	if(!lpszOut)
	{
		return 0;
	} // 结束 if(!lpszOut)
	__try
	{	USES_CONVERSION;
		iR = DeleteSpace(W2CT(bszIn), lpszOut);
		if(iR == 0)
		{
			__leave;
		} // 结束 if(iR == 0)
		iLen = _tcslen(lpszOut);
		if(*(lpszOut + iLen - 1) == _T(' '))
		{
			*(lpszOut + iLen - 1) = NULL;
			iR -= 1;
		} //结束 if(*(lpszOut + iLen - 1) == _T(' '))
		if(*lpszOut == _T(' '))
		{
			_tcscpy(lpszOut, lpszOut - 1);
			if(iR)
			{
				iR -= 1;
			}
		} //结束 if(*lpszOut == _T(' '))
	}
	__finally
	{
		::SysFreeString(*pbszOut);
		*pbszOut = T2BSTR(lpszOut);
		delete []lpszOut;
		return iR;
	}
}

/*******************************************************************************************************
函数名：ReversionMatchSplitSymbolB
描  述：反向匹配指定的分隔符，作为 API 函数，用于 BASIC 调用。
注  意：两个匹配（但是是这样的情况：分隔符2在分隔符1前。例如: 分隔符1为 "(",分隔符2为")"，可能匹配：“) a (” ）
参  数：
        LPTSTR lpszSource：源代码。成功后，包含为分隔符中间的字符串（不包含分隔符）
		LONG * nSource   ：操作后，包含为分隔符中间的字符串（不包含分隔符）的长度
		LPCTSTR lpStr1   ：分隔符1
		LPCTSTR lpStr2   ：分隔符2
		LPTSTR lpszBefor ：分隔符1前的字符串，（不包含分隔符）
		LONG * nBefor    ：操作后，分隔符1前的字符串，（不包含分隔符）的长度
		LPTSTR lpszBack  ：分隔符2后的字符串，（不包含分隔符）
		LONG * nBack     ：操作后，分隔符2后的字符串，（不包含分隔符）的长度
		BOOL bQutation   ：是否匹配引号中的字符。TRUE，不匹配；FALSE，匹配（默认值）
返回值：类型为 LONG 。
        失败,返回-1,缺少分隔符1；返回-2,缺少分隔符2。
        成功,>0,分离出的字符串的长度(包含分隔符的长度)
        没有分隔符,为0
版  本：2005.6.0.1
作  者：康  林
时  间：2005年7月21日 10:49:04
*******************************************************************************************************/
extern "C" LONG _stdcall ReversionMatchSplitSymbolB(LPTSTR lpszSource,
													LONG * nSource,
													LPCTSTR lpStr1,
													LPCTSTR lpStr2, 
													LPTSTR lpszBefor,
													LONG * nBefor,
													LPTSTR lpszBack,
													LONG * nBack,
													BOOL bQutation
													)
{
	LONG ir = ReversionMatchSplitSymbol(lpszSource, lpStr1, lpStr2, lpszBefor, lpszBack, bQutation);
	if(ir > 0)
	{
		if(nSource)
		{
			_tcslen(lpszSource);
		} // 结束 if(nSource)
		if(nBefor && lpszBefor)
		{
			_tcslen(lpszBefor);
		} // 结束 if(nBefor && lpszBefor)
		if(nBack && lpszBack)
		{
			_tcslen(lpszBack);
		} // 结束 if(nBack && lpszBack)
	} // 结束 if(ir > 0)
	return ir;
}

/*******************************************************************************************************
函数名：ReversionMatchSplitSymbol
描  述：反向匹配指定的分隔符
注  意：两个匹配（但是是这样的情况：分隔符2在分隔符1前。例如: 分隔符1为 "(",分隔符2为")"，可能匹配：“) a (” ）
参  数：
        LPTSTR lpszSource      ：源代码。成功后，包含为分隔符中间的字符串（不包含分隔符）
		LPCTSTR lpStr1         ：分隔符1
		LPCTSTR lpStr2         ：分隔符2
		LPTSTR lpszBefor       ：分隔符1前的字符串，（不包含分隔符）
		LPTSTR lpszBack        ：分隔符2后的字符串，（不包含分隔符）
		BOOL bQutation         ：是否匹配引号中的字符。TRUE，不匹配；FALSE，匹配（默认值）
返回值：
版  本：2005.6.0.1
作  者：康  林
时  间：2005年7月10日 13:51:52
*******************************************************************************************************/
extern "C" LONG _stdcall ReversionMatchSplitSymbol(LPTSTR lpszSource, 
                                         LPCTSTR lpStr1,
                                         LPCTSTR lpStr2, 
                                         LPTSTR lpszBefor,
                                         LPTSTR lpszBack,
										 BOOL bQutation
										 )
{
	LPTSTR lpSur, lpS1, lpS2, lpBefor, lpBack;
	lpSur = new TCHAR[_tcslen(lpszSource) + sizeof(TCHAR)];
	if(!lpSur)
	{
		return 0;
	}
	_tcscpy(lpSur, lpszSource);
	_tcsrev(lpSur);
	lpS1 = new TCHAR[_tcslen(lpStr1) + sizeof(TCHAR)];
	if(!lpS1)
	{
		return 0;
	}
	_tcscpy(lpS1, lpStr1);
	_tcsrev(lpS1);
	lpS2  = new TCHAR[_tcslen(lpStr2) + sizeof(TCHAR)];
	if(!lpS2)
	{
		return 0;
	}
	_tcscpy(lpS2, lpStr2);
	_tcsrev(lpS2);
	lpBefor = NULL;
	lpBack = NULL;
	if(lpszBefor)
	{
		lpBefor = new TCHAR[_tcslen(lpszSource) + sizeof(TCHAR)];
		if(!lpBefor)
		{
			return 0;
		}
	}
	if(lpszBack)
	{
		lpBack  = new TCHAR[_tcslen(lpszSource) + sizeof(TCHAR)];
		if(!lpBack)
		{
			return 0;
		}
	}

	INT ir;
	if(bQutation)
	{
		ir = MatchSplitSymbolC(lpSur, lpS2, lpS1, lpBack, lpBefor, bQutation, TRUE);		
	}
    else
	{
		ir = MatchSplitSymbol(lpSur, lpS2, lpS1, lpBack, lpBefor);		
	} // 结束 if(bQutation)
	
	if(ir > 0)
	{
		if(lpSur)
		{
			_tcsrev(lpSur);
			_tcscpy(lpszSource, lpSur);
		}
		if(lpszBefor)
		{
			_tcsrev(lpBefor);
            _tcscpy(lpszBefor, lpBefor);
		}
		if(lpszBack)
		{
			_tcsrev(lpBack);
			_tcscpy(lpszBack, lpBack);
		}
	}

	delete []lpSur;
	delete []lpBefor;
	delete []lpBack;
	delete []lpS2;
	delete []lpS1;

	return ir;
}

/*******************************************************************************************************
函数名：MatchSplitSymbolB
描  述：匹配指定的分隔符。作为API函数，由BASIC调用
注  意：两个匹配（但是是这样的情况：分隔符2在分隔符1前。例如: 分隔符1为 "(",分隔符2为")"，可能匹配：“) a (” ）
参  数：
        CComBSTR* lpszSource   ：源代码。成功后，包含为分隔符中间的字符串（不包含分隔符）。
		CComBSTR* lpStr1       ：分隔符1
		CComBSTR* lpStr2       ：分隔符2
		CComBSTR* lpszBefor    ：操作后，分隔符1前的字符串，（不包含分隔符）
		CComBSTR* lpszBack     ：操作后，分隔符2后的字符串，（不包含分隔符）
		BOOL bQutation         ：是否匹配引号中的字符。TRUE，不匹配（默认值）；FALSE，匹配
		BOOL bReversionQutation：是否是反向匹配。TRUE，是反向匹配，FALSE，不是反向匹配（默认值）
返回值：类型为 LONG 。
        失败,返回-1,缺少分隔符1；返回-2,缺少分隔符2。
        成功,>0,分离出的字符串的长度(包含分隔符的长度)
        没有分隔符,为0
版  本：2005.6.0.1
作  者：康  林
时  间：2005年7月29日 10:33:24
*******************************************************************************************************/
extern "C" LONG _stdcall MatchSplitSymbolB(CComBSTR* lpszSource,
										   CComBSTR* lpStr1,
										   CComBSTR* lpStr2, 
										   CComBSTR* lpszBefor,
										   CComBSTR* lpszBack,
										   BOOL bQutation,
										   BOOL bReversionQutation)
{
	ASSERT(lpStr1 != NULL && lpStr2 != NULL);
	USES_CONVERSION;
	LPCTSTR lpSor = W2CT(*lpszSource);
	LPTSTR lpSource = NULL, lpBef = NULL, lpBack = NULL;
	LONG ir = 0;
	if(lpszSource != NULL)
	{
		lpSource = new TCHAR[_tcslen(lpSor) + sizeof(TCHAR)];
		_tcscpy(lpSource, lpSor);
	}
	if(lpszBefor != NULL)
	{
		lpBef =  new TCHAR[_tcslen(lpSor) + sizeof(TCHAR)];
	}
	if(lpszBack != NULL)
	{
		lpBack =  new TCHAR[_tcslen(lpSor) + sizeof(TCHAR)];
	}
	if(lpSource)
	{
		ir = MatchSplitSymbolC(lpSource, W2CT(*lpStr1), W2CT(*lpStr2), lpBef, lpBack, bQutation, bReversionQutation);
		if(ir > 0)
		{
			if(lpSource)
			{
				lpszSource->Empty();
				*lpszSource = lpSource;
			}
			if(lpBef)
			{
				lpszBefor->Empty();
				*lpszBefor = lpBef;
			}
			if(lpBack)
			{
				lpszBack->Empty();
				*lpszBack = lpBack;
			}
		} // 结束 if(ir > 0)
	}
	if(lpSource)
	{
		delete []lpSource;
	}
	if(lpBef)
	{
		delete []lpBef;
	}
	if(lpBack)
	{
		delete []lpBack;
	}
	return ir;
}

/*******************************************************************************************************
函数名：MatchSplitSymbolC
描  述：匹配指定的分隔符
注  意：两个匹配（但是是这样的情况：分隔符2在分隔符1前。例如: 分隔符1为 "(",分隔符2为")"，可能匹配：“) a (” ）
参  数：
        LPTSTR lpszSource      ：源代码。成功后，包含为分隔符中间的字符串（不包含分隔符）。
		LPCTSTR lpStr1         ：分隔符1
        LPCTSTR lpStr2         ：分隔符2
        LPTSTR lpszBefor       ：分隔符1前的字符串，（不包含分隔符）。
        LPTSTR lpszBack        ：分隔符2后的字符串，（不包含分隔符）。
		BOOL bQutation         ：是否匹配引号中的字符。TRUE，不匹配（默认值）；FALSE，匹配
		BOOL bReversionQutation：是否是反向匹配。TRUE，是反向匹配，FALSE，不是反向匹配（默认值）
返回值：失败,返回-1,缺少分隔符1；返回-2,缺少分隔符2。
        成功,>0,分离出的字符串的长度(包含分隔符的长度)
        没有分隔符,为0
版  本：2005.6.0.1
作  者：康  林
时  间：2005年7月10日 13:56:17
*******************************************************************************************************/
extern "C" LONG _stdcall MatchSplitSymbolC(LPTSTR lpszSource, 
                                         LPCTSTR lpStr1,
                                         LPCTSTR lpStr2, 
                                         LPTSTR lpszBefor,
                                         LPTSTR lpszBack,
										 BOOL bQutation,
										 BOOL bReversionQutation)
{
    LPTSTR lpSou, p, lpS, lpE;
    INT iStack, iR /*返回值*/;
    INT iMS /*第一个分隔符匹配的字符数*/, iME /*第二个分隔符匹配的字符数*/;
    INT iLen1, iLen2; //分隔符的长度
    INT iLen; //源字符串的长度
	BOOL bMatch;//两个匹配（但是是这样的情况：分隔符2在分隔符1前。例如: 分隔符1为 "(",分隔符2为")"，可能匹配：“) a (” ）

    ASSERT(lpszSource != NULL || lpStr1 != NULL || lpStr2 != NULL);

    lpSou = lpszSource;
    p = lpSou;
    lpS = NULL;
    lpE = NULL;
    iStack = 0;
    iR = 0;
    iMS = 0;
    iME = 0;    
    iLen1 = _tcslen(lpStr1);
    iLen2 = _tcslen(lpStr2);
    iLen = _tcslen(lpszSource);
    bMatch = FALSE;

    while(lpSou < lpszSource + iLen)
    {
		//考虑引号
        if(bQutation) // <a name = "bQutation"></a>
		{
			if(*lpSou == _T('\\') && (*(lpSou + 1) == _T('\'') || *(lpSou + 1)== _T('\\') || *lpSou == _T('\"')) && !bReversionQutation)
			{
				lpSou += 2;				
			}
			if(*(lpSou + 1)== _T('\\') && (*lpSou == _T('\'') || *lpSou == _T('\\') || *lpSou == _T('\"')) && bReversionQutation)
			{
				lpSou += 2;				
			}
			
			if(lpSou >= lpszSource + iLen)
			{
				TRACE(_T("%s(%d) : 出错.遇到 \' 后结束。\n"), __FILE__, __LINE__);
				break;
			}
			if(*lpSou == _T('\'') || *lpSou == _T('\"'))
			{
				TCHAR ch = *lpSou;
				lpSou++;
				while(lpSou < lpszSource + iLen)
				{
					if(*lpSou == _T('\\') && (*(lpSou + 1) == _T('\'') || *(lpSou + 1) == _T('\"') || *(lpSou + 1) == _T('\\')) && !bReversionQutation)
					{
						lpSou += 2;
						continue;
					} // 结束 if(*lpSou == _T('\\') && (*(lpSou + 1) == _T('\'') || *(lpSou + 1) == _T('\"') || *(lpSou + 1) == _T('\\')))
					if(*(1 + lpSou) == _T('\\') && (*lpSou == _T('\'') || *lpSou == _T('\"') || *lpSou == _T('\\')) && bReversionQutation)
					{
						lpSou += 2;
						continue;
					} // 结束 if(*lpSou == _T('\\') && (*(lpSou + 1) == _T('\'') || *(lpSou + 1) == _T('\"') || *(lpSou + 1) == _T('\\')))
					
					if(*lpSou == ch)
					{
						lpSou++;
						break;
					} // 结束 if(*lpSou = ch && *(lpSou - 1) != _T('\\') || (*(lpSou - 2) == _T('\\') && *(lpSou - 1) == _T('\\') && *lpSou == ch)					
					lpSou++;
				} // 结束 while(lpSou < lpszSource + iLen)
				if(lpSou >= lpszSource + iLen)
				{
					TRACE(_T("%s(%d) : 出错.没有遇到右边引号\n"), __FILE__, __LINE__);
					break;
				}
			} // 结束 if((*lpSou == _T('\'') || *lpSou == _T('\"'))&& *(lpSou - 1) != _T('\\') || (*(lpSou - 2) == _T('\\') && *(lpSou - 1) == _T('\\') && (*lpSou == _T('\'') || *lpSou == _T('\"'))))
		} // 结束 if(bQutation)
		if(lpSou >= lpszSource + iLen)
		{
			TRACE(_T("%s(%d) : 出错.遇到右边引号,但这是最后一个字符。\n"), __FILE__, __LINE__);
			break;
		} // 结束 if(lpSou < lpszSource + iLen)

        p = lpSou;
        while(p != NULL && (p - lpSou <= iLen1 || p - lpSou <= iLen2))
        {
            if(*p == *(lpStr1 + iMS))
            {
                iMS++;
            }
            else
            {
                iMS = 0;
            } //结束 if(*lpszSource == *(lpS + iMS))
            if(iMS == iLen1) //与第一个分隔符匹配成功
            {
                iStack++;
				if(iStack == 0)
				{
					bMatch = TRUE;
				}
                lpSou = p + 1;
                if(iStack == 1)
                {
                    lpS = p + 1; //记录第一次遇到分隔符1的位置(指向分隔符后面的第一个字符)
                } //结束 if(iStack == 1)
                break;
            } //结束 if(iMS == iLen1 - 1)
           
            if(*p == *(lpStr2 + iME))
            {
                iME++;
            }
            else
            {
                iME = 0;
            } //结束 if(*p == *(lpStr2 + iME))
            if(iME == iLen2) //与第二个分隔符匹配成功
            {
                iStack--;
                lpSou = p + 1;
                if(iStack == 0)
                {
                    //正确匹配,返回
                    int iL;
                    p++;
                    iL = lpS - iLen1 - lpszSource;
					if(lpszBefor)
					{
						memcpy(lpszBefor, lpszSource, iL);
						*(lpszBefor + iL) = (TCHAR)NULL;  //设置终结符
					}
                    iL = lpszSource + iLen - p;
					if(lpszBack)
					{
						memcpy(lpszBack, p, iL);
						*(lpszBack + iL) = (TCHAR)NULL;   //设置终结符
					}
                    iL = p - iLen2 - lpS;
                    memcpy(lpszSource, lpS, iL);
                    *(lpszSource + iL) = (TCHAR)NULL;     //设置终结符
                    return iLen1 + iL + iLen2;
                } //结束 if(iStack == 0)
                break;
            } //结束 if(iME == iLen2 - 1)
            p++;
        } //结束 while(p != NULL)
        
        if(iMS == iLen1 || iME == iLen2)
        {
            iMS = 0;
            iME = 0;
        } 
        else
        {
            lpSou++;
        } //结束 if(iMS == iLen1 || iME == iLen2)        
    } //结束 while(lpszSource != NULL)
    if(iStack == 0) //无分隔符或者两个匹配（但是是这样的情况：分隔符2在分隔符1前。例如: 分隔符1为 "(",分隔符2为")"，可能匹配：“) a (” ）
    {
		if(bMatch)
		{
			return 0;
		}
		else
		{
			return 0;
		}
    }
    else //分隔符不匹配
    {
        if(iStack > 0)
		{
			return -2; //缺少分隔符2
		}
		else
		{
			return -1; //缺少分隔符1
		}
    } //结束 if(iStack == 0)

}

/*******************************************************************************************************
函数名：MatchSplitSymbol
功  能：匹配指定的分隔符
注  意：两个匹配（但是是这样的情况：分隔符2在分隔符1前。例如: 分隔符1为 "(",分隔符2为")"，可能匹配：“) a (” ）
参  数：
         LPTSTR lpszSource：源代码。成功后，包含为分隔符中间的字符串（不包含分隔符）。
         LPCTSTR lpStr1：   分隔符1
         LPCTSTR lpStr2：   分隔符2
         LPTSTR lpszBefor： 分隔符1前的字符串，（不包含分隔符）。
         LPTSTR lpszBack：  分隔符2后的字符串，（不包含分隔符）。
返回值：失败,返回-1,却少分隔符1；返回-2,却少分隔符2。
        成功,>0,分离出的字符串的长度(包含分隔符的长度)
        没有分隔符,为0
版  本：1.0
作  者：康  林
时  间：2005-5-4 19:13:06
*******************************************************************************************************/
extern "C" LONG _stdcall MatchSplitSymbol(LPTSTR lpszSource, 
                                         LPCTSTR lpStr1,
                                         LPCTSTR lpStr2, 
                                         LPTSTR lpszBefor,
                                         LPTSTR lpszBack)
{
    LPTSTR lpSou, p, lpS, lpE;
    INT iStack, iR /*返回值*/;
    INT iMS /*第一个分隔符匹配的字符数*/, iME /*第二个分隔符匹配的字符数*/;
    INT iLen1, iLen2; //分隔符的长度
    INT iLen; //源字符串的长度
	BOOL bMatch;//两个匹配（但是是这样的情况：分隔符2在分隔符1前。例如: 分隔符1为 "(",分隔符2为")"，可能匹配：“) a (” ）

    ASSERT(lpszSource != NULL || lpStr1 != NULL || lpStr2 != NULL);

    lpSou = lpszSource;
    p = lpSou;
    lpS = NULL;
    lpE = NULL;
    iStack = 0;
    iR = 0;
    iMS = 0;
    iME = 0;    
    iLen1 = _tcslen(lpStr1);
    iLen2 = _tcslen(lpStr2);
    iLen = _tcslen(lpszSource);
    bMatch = FALSE;

    while(lpSou < lpszSource + iLen)
    {
        p = lpSou;
        while(p != NULL && (p - lpSou <= iLen1 || p - lpSou <= iLen2))
        {
            if(*p == *(lpStr1 + iMS))
            {
                iMS++;
            }
            else
            {
                iMS = 0;
            } //结束 if(*lpszSource == *(lpS + iMS))
            if(iMS == iLen1) //与第一个分隔符匹配成功
            {
                iStack++;
				if(iStack == 0)
				{
					bMatch = TRUE;
				}
                lpSou = p + 1;
                if(iStack == 1)
                {
                    lpS = p + 1; //记录第一次遇到分隔符1的位置(指向分隔符后面的第一个字符)
                } //结束 if(iStack == 1)
                break;
            } //结束 if(iMS == iLen1 - 1)
           
            if(*p == *(lpStr2 + iME))
            {
                iME++;
            }
            else
            {
                iME = 0;
            } //结束 if(*p == *(lpStr2 + iME))
            if(iME == iLen2) //与第二个分隔符匹配成功
            {
                iStack--;
                lpSou = p + 1;
                if(iStack == 0)
                {
                    //正确匹配,返回
                    int iL;
                    p++;
                    iL = lpS - iLen1 - lpszSource;
					if(lpszBefor)
					{
						::CopyMemory(lpszBefor, lpszSource, iL);
						*(lpszBefor + iL) = (TCHAR)NULL;   //设置终结符
					}
                    iL = lpszSource + iLen - p;
					if(lpszBack)
					{
						::CopyMemory(lpszBack, p, iL);
						*(lpszBack + iL) = (TCHAR)NULL;    //设置终结符
					}
                    iL = p - iLen2 - lpS;
                    ::CopyMemory(lpszSource, lpS, iL);
                    *(lpszSource + iL) = (TCHAR)NULL;  //设置终结符
                    return iLen1 + iL + iLen2;
                } //结束 if(iStack == 0)
                break;
            } //结束 if(iME == iLen2 - 1)
            p++;
        } //结束 while(p != NULL)
        
        if(iMS == iLen1 || iME == iLen2)
        {
            iMS = 0;
            iME = 0;
        } 
        else
        {
            lpSou++;
        } //结束 if(iMS == iLen1 || iME == iLen2)        
    } //结束 while(lpszSource != NULL)
    if(iStack == 0) //无分隔符或者两个匹配（但是是这样的情况：分隔符2在分隔符1前。例如: 分隔符1为 "(",分隔符2为")"，可能匹配：“) a (” ）
    {
		if(bMatch)
		{
			return 0;
		}
		else
		{
			return 0;
		}
    }
    else //分隔符不匹配
    {
		if(iStack > 0)
		{
			return -2; //却少分隔符2
		}
		else
		{
			return -1; //却少分隔符1
		}
    } //结束 if(iStack == 0)
}

/*******************************************************************************************************
函数名：Quotation
功  能：引号
参  数：
         LPTSTR* lppIn：输入点
         LPTSTR* lppOut：输出点
         LPTSTR* lppStack：堆栈点
返回值：成功返回TRUE,否则返回FALSE.
版  本：1.0.0.1
作  者：康  林
时  间：2005-4-30 22:23:51
*******************************************************************************************************/
extern "C" BOOL WINAPI Quotation(LPTSTR* lppIn, LPTSTR* lppOut, LPTSTR* lppStack)
{
    LPTSTR lpIn, lpOut, lpStack;
    lpIn = *lppIn;
    lpOut = *lppOut;
    lpStack = *lppStack;

    TCHAR ch;
    ch = *lpIn;
    *lpOut = *lpIn;
    lpOut++;
    lpIn++;
    while(*lpIn != NULL)
    {
        if(*lpIn == '\\' && (*(lpIn + 1) == '\'' || *(lpIn + 1) == '\"' || *(lpIn+1) == '\\'))
        {
            *lpOut = *lpIn;
            *(lpOut + 1) = *(lpIn + 1);
            lpOut += 2;
            lpIn += 2;
            continue;
        } // 结束 if(*lpIn == '\\' && (*(lpIn + 1) == '\'' || *(lpIn + 1) == '\"' || *(lpIn+1) == '\\'))
        if(*lpIn == ch)
        {
            *lpOut = *lpIn;
            lpOut++;
            *lppOut = lpOut;
            *lppStack = lpIn;
            lpIn++;
            *lppIn = lpIn;
            return TRUE;
        }
        *lpOut = *lpIn;
        lpOut++;
        lpIn++;
    }
    *lppOut = lpOut;
    *lppIn = lpIn;
    *lppStack = lpIn;
    TRACE(_T("%s(%d) : 错误,缺少右引号\n"), __FILE__, __LINE__);
    return FALSE;
}

/*******************************************************************************************************
函数名：SpaceFormat
功  能：空格和制表符
参  数：
         LPTSTR* lppIn：输入点
         LPTSTR* lppOut：输出点
         LPTSTR* lppStack：堆栈点
         BOOL* bFlag：是否是行开始标志
返回值：成功返回TRUE,否则返回FALSE
版  本：1.0.0.1
作  者：康  林
时  间：2005-5-1 7:45:42
*******************************************************************************************************/
BOOL SpaceFormat(LPTSTR* lppIn, LPTSTR* lppOut, LPTSTR* lppStack, BOOL* bFlag, LPTSTR lpOutCode)
{
    LPTSTR lpIn, lpOut, lpStack;
    lpIn = *lppIn;
    lpOut = *lppOut;
    lpStack = *lppStack;
    

    if(*bFlag) //行开始时
    {
        *lpOut = *lpIn;
        lpStack = lpIn;
        lpOut++;
        lpIn++;
    }
    else //不是行开始时
    {
        if(*(lpOut - 1) != ' ' //输出字符串的顶不是空格              
           && *(lpOut - 1) != '('
           && *(lpOut - 1) != ')' && *(lpOut - 1) != TAB) 
        {
            *lpOut = ' ';
            lpStack = lpIn;
            lpOut++;
            lpIn++;
        }
        else
        {
            lpStack = lpIn;
        }
    }    
    
    *lppStack = lpStack;
    while(*lpIn != NULL)
    {
        if(*lpIn != ' ' && * lpIn != TAB)
        {   
            //if(*bFlag && (*lpIn == '{' || *lpIn == '}'))
            //{
            //    //BigBracket(&lpIn, &lpOut, &lpStack, lpOutCode);
            //    return TRUE;
            //}
            if((!*bFlag) && *lpIn == '/' 
                && (*(lpIn + 1) == '/' 
                || *(lpIn + 1) == '*'))
            {
                if(*(lpOut - 1) == ' ' || *(lpOut - 1) == TAB)
                {
                    lpOut--;
                }
                //空格后是注释时，保留所有空格
                while(lpStack != lpIn)
                {
                    *lpOut = *lpStack;
                    lpOut++;
                    lpStack++;
                }
                *lppOut = lpOut;
                *lppIn = lpIn;
                *bFlag = FALSE;
                return TRUE;
            }
            if(*bFlag 
                && (*lpIn == _T(';') || *lpIn == _T(',')
                || *lpIn == _T('(') || *lpIn == _T(')')
                || *lpIn == _T('[') || *lpIn == _T(']')
                || (*lpIn == _T('*') && *(lpIn + 1) != _T('/')) /*不是注释结束符时*/
				|| *lpIn == _T('&')))
			{
                *lpOut = *lpIn;
                lpStack = lpIn;
                lpIn++;
                lpOut++;	
			} // 结束 if(*bFlag && (*lpIn == _T(';') || *lpIn == _T(',') || *lpIn == _T('(') || *lpIn == _T(')') || *lpIn == _T('[') || *lpIn == _T(']') || (*lpIn == _T('*')&& *(lpIn + 1) != _T('/')) || *lpIn == _T('&')))
            *lppStack = lpStack;
            *lppOut = lpOut;
            *lppIn = lpIn;
            *bFlag = FALSE;
            return TRUE;
        } //结束 if(*lpIn != ' ' && * lpIn != TAB)

        if(*bFlag) //行开始时，保留空格
        {
            *lpOut = *lpIn;
            lpOut++;            
        }
        lpIn++;
    }
    if(*(lpOut - 1) == ' ')
    {
        //空格是行最后的
        lpOut--;
    }
    *lppStack = lpIn;
    *lppOut = lpOut;
    *lppIn = lpIn;
    return FALSE;
}

/*******************************************************************************************************
函数名：Comma
功  能：分号、逗号
参  数：
         LPTSTR* lppIn：输入点
         LPTSTR* lppOut：输出点
         LPTSTR* lppStack：堆栈点
返回值：成功返回TRUE,否则返回FALSE.
版  本：1.0.0.1
作  者：康  林
时  间：2005-5-1 11:22:00
*******************************************************************************************************/
extern "C" BOOL Comma(LPTSTR* lppIn, LPTSTR* lppOut, LPTSTR* lppStack)
{
    LPTSTR lpIn, lpOut, lpStack;
    lpIn = *lppIn;
    lpOut = *lppOut;
    lpStack = *lppStack;

    if(*(lpOut - 1) == ' ')
    {
        lpOut--;
    }

    *lpOut = *lpIn;
    lpOut++;
    if(*(lpIn + 1) != NULL && *(lpIn + 1) != ' ' && *(lpIn + 1) != TAB)
    {
        *lpOut = ' ';
        lpOut++;
    }
    lpStack = lpIn;
    *lppStack = lpStack;
    *lppIn = lpIn + 1;
    *lppOut = lpOut;
    return TRUE;
}

/*******************************************************************************************************
函数名：LitterBracket
功  能：小括号、中括号
参  数：
         LPTSTR* lppIn：输入点
         LPTSTR* lppOut：输出点
         LPTSTR* lppStack：堆栈点
返回值：成功返回TRUE,否则返回FALSE.
版  本：1.0.0.1
作  者：康  林
时  间：2005-5-1 11:28:55
*******************************************************************************************************/
extern "C" BOOL LitterBracket(LPTSTR* lppIn, LPTSTR* lppOut, LPTSTR* lppStack)
{
    LPTSTR lpIn, lpOut, lpStack;
    lpIn = *lppIn;
    lpOut = *lppOut;
    lpStack = *lppStack;

    if(*lpIn == _T('[')
		&& (*(lpOut - 1) == _T('e') && *(lpOut - 2) == _T('t') && *(lpOut - 3) == _T('e') && *(lpOut - 4) == _T('l')
		&& *(lpOut - 5) == _T('e') && *(lpOut - 6) == _T('d')))
    {
        //处理 delete []p;
        *lpOut = _T(' ');
        lpOut++;
    }
    if(*(lpOut - 1) == _T(' '))
    {
        switch (*(lpOut - 2))
        {
        case _T('+'):
        case _T('-'):
        case _T('*'):
        case _T('/'):
        case _T('%'):
        case _T('='):
        case _T('&'):
        case _T('|'):
        case _T('^'):
        case _T('>'):
        case _T('<'):
        case _T(';'):
        case _T(','):
            break;
        case _T('e'):
            //处理 delete []p;
			if(*lpIn == _T('[')
				&& (*(lpOut - 2) == _T('e') && *(lpOut - 3) == _T('t') && *(lpOut - 4) == _T('e') && *(lpOut - 5) == _T('l')
				&& *(lpOut - 6) == _T('e') && *(lpOut - 7) == _T('d')))
            {
                break;
            } // 结束 if(*lpIn == _T('[') && (*(lpOut - 2) == _T('e') && *(lpOut - 3) == _T('t') && *(lpOut - 4) == _T('e') && *(lpOut - 5) == _T('l') && *(lpOut - 6) == _T('e') && *(lpOut - 7) == _T('d')))
        default:
            lpOut--;
        }
    }
    *lpOut = *lpIn;
    *lppStack = lpIn;
    *lppIn = lpIn + 1;
    *lppOut = lpOut + 1;
    return TRUE;
}

/*******************************************************************************************************
函数名：BigBracket
功  能：大括号
参  数：
         LPTSTR* lppIn：输入点
         LPTSTR* lppOut：输出点
         LPTSTR* lppStack：堆栈点
		 LPTSTR lpOutCode：已格式化的代码
返回值：成功返回TRUE,否则返回FALSE.
版  本：1.0.0.1
作  者：康  林
时  间：2005-5-1 12:00:02
*******************************************************************************************************/
extern "C" BOOL BigBracket(LPTSTR* lppIn, LPTSTR* lppOut, LPTSTR* lppStack, LPTSTR lpOutCode)
{
    LPTSTR lpIn, lpOut, lpStack, lp;
    BOOL bFace, bAfter;
    lpIn = *lppIn;
    lpOut = *lppOut;
    lpStack = *lppStack;

    bFace = FALSE;
    bAfter = FALSE;
    lpStack = lpIn;
    
    lp = lpOut;
    while(lpOutCode < lp && *(lp - 1) != CR && *lp != LF)
    {
        lp--;
        if(*lp != ' ' && *lp != TAB)
        {
            bFace = TRUE;
            break;
        }
    }    
    //含有换行符
    if(*(lp - 1) == CR && *lp == LF)
    {
        bFace = FALSE;
    }

    if(bFace)
    {
        *lpOut = CR;
        *(lpOut + 1) = LF;
        lpOut += 2;
    }//结束 if(bFace)
   
    *lpOut = *lpIn;
    lpOut ++;
    lpIn++;

    while(*lpIn != NULL)
    {        
        if(*lpIn != ' ' && *lpIn != TAB)
        {
            if(*lpIn == '/')
            {
				int iR = Division(&lpIn, &lpOut, &lpStack, TRUE, lpOutCode);
				if(2 == iR)
                {
                    continue;
                }
				else if(4 == iR)
                {
                    //形如: {/a  //注释...
                    bAfter = TRUE;
                    break;
                }
                else
                {
                    bAfter = FALSE;
                    break;
				}
            } //结束 if(2 == iR)

            if(*lpIn == ';')
            {
                bAfter = FALSE;
                break;
            }//结束 if(*lpIn == ';')

            bAfter = TRUE;
            break;
        }
        lpIn++;
    } //结束 while(*lpIn != NULL)
  
    if(bAfter)
    {
        *lpOut = CR;
        *(lpOut + 1) = LF;
        lpOut += 2;
    }

    *lppOut = lpOut;
    *lppIn = lpIn;
    *lppStack = lpStack;
    return TRUE;
}

/*******************************************************************************************************
函数名：Division
功  能：除号
参  数：
         LPTSTR* lppIn：输入点
         LPTSTR* lppOut：输出点
         LPTSTR* lppStack：堆栈点
         BOOL bFlag：行开始是否是空格
		 LPTSTR lpOutCode：格式化的代码输出指针
         BOOL bComment：只考虑注释情况，为TRUE，还考虑其它情况，为FALSE。默认为FALSE
返回值：是注释//，返回1
        是注释 /*, 返回2
        是除号 / ，返回3
        不是注释，返回4
版  本：1.0.0.1
作  者：康  林
时  间：2005-5-1 16:24:34
*******************************************************************************************************/
INT Division(LPTSTR * lppIn, LPTSTR * lppOut, LPTSTR * lppStack, BOOL bFlag, LPTSTR lpOutCode, BOOL bComment)
{
    LPTSTR lpIn, lpOut, lpStack;
    lpIn = *lppIn;
    lpOut = *lppOut;
    lpStack = *lppStack;

    *lppStack = lpIn;
	if(*(lpIn + 1) == '/') //注释// 
    {
        if((*(lpOut - 1) != TAB && *(lpOut - 1) != ' ') && !bFlag)
        {
            *lpOut = ' ';
            lpOut++;
        }
        while(*lpIn != NULL)
        {
            if(*lpIn == CR && *(lpIn + 1) == LF)
            {
                *lpOut = *lpIn;
                lpOut++;
                lpIn++;
                *lpOut = *lpIn;
                lpOut++;
                lpIn++;
                break;
            }
            *lpOut = *lpIn;
            lpOut++;
            lpIn++;
        }
        *lppOut = lpOut;
        *lppIn = lpIn;
		return 1; //注释// 
    } // 结束 if(*(lpIn + 1) == '/')
    if(*(lpIn + 1) == '*') //注释/*...*/
    {
        if((*(lpOut - 1) != TAB && *(lpOut - 1) != ' ') && !bFlag)
        {
            *lpOut = ' ';
            lpOut++;
        }
        while(*lpIn != NULL) 
        {
            if(*lpIn == '*' && '/' == *(lpIn + 1))
            {
                *lpOut = '*';
                *(lpOut + 1) = '/';
                lpOut = lpOut + 2;
                *lppOut = lpOut;
                *lppIn = lpIn + 2;
                return 2;
            }
            *lpOut = *lpIn;
            lpOut++;
            lpIn++;
        }
        *lppOut = lpOut;
        *lppIn = lpIn;
		return 2; //注释/*...*/
    } //if(*(lpIn + 1) == '*') //注释/*...*/
    
    if(bComment)
    {
        //详见函数 BigBracket 中的本函数的返回值为 4 的情况
        return 4; //不是注释
	}

	//考虑#include <sys/net.h>情况
	if(IsInclude(lpOutCode, lpOut))
	{
		*lpOut =* lpIn;
		lpOut++;
		lpIn++;
		*lppOut = lpOut;
		*lppIn = lpIn;
		return 5;
	} // 结束 if(IsInclude(lpOutCode, lpOut))

    if(*(lpOut - 1) != ' ')
    {
        *lpOut = ' ';
        lpOut++;
    }
    *lpOut = *lpIn;
    lpOut++;
    if('=' == *(lpIn + 1))
    {
        *lpOut = '=';
        lpOut++;
        lpIn++;
    }
    if(' ' != *(lpIn + 1))
    {
        *lpOut = ' ';
        lpOut++;
    }    
    *lppIn = lpIn + 1;
    *lppOut = lpOut;

    return 3;
}

/*******************************************************************************************************
函数名：AddFormat
功  能：加号、减号
参  数：
         LPTSTR* lppIn：
         LPTSTR* lppOut：
         LPTSTR* lppStack：
返回值：
版  本：1.0.0.1
作  者：康  林
时  间：2005-5-1 16:56:03
*******************************************************************************************************/
BOOL AddFormat(LPTSTR* lppIn, LPTSTR* lppOut, LPTSTR* lppStack)
{
    LPTSTR lpIn, lpOut, lpStack;
    TCHAR ch;
    lpIn = *lppIn;
    lpOut = *lppOut;
    lpStack = *lppStack;
   
    *lppStack = lpIn;
    
    if(*(lpIn + 1) == '>' && *lpIn == '-')
    {
        *lpOut = *lpIn;
        lpOut++;
        lpIn++;
        *lpOut = *lpIn;
        *lppOut = lpOut + 1;
        *lppIn = lpIn + 1;
        return TRUE;
    }
    if(*(lpOut - 1) == ' ')
    {
        ch = *(lpOut - 2);
    }
    else
    {
        ch = *(lpOut - 1);
    }

    //判断正号
    if('=' == ch || ',' == ch /*|| ')' == ch */
        || '(' == ch || '>' == ch || '<' == ch
        || '&' == ch || '|' == ch || '^' == ch)
    {
        *lpOut = *lpIn;
        lpStack = lpIn;
        lpOut++;
        lpIn++;
        *lppIn = lpIn;
        *lppOut = lpOut;
        return TRUE;
    }
   
    if(*(lpIn + 1) == *lpIn)
    {
        *lpOut = *lpIn;
        lpOut++;
        lpIn++;
        *lpOut = *lpIn;        
        lpOut++;
    }
    else 
    {
        if(*(lpOut - 1) != ' ')
        {
            *lpOut = ' ';
            lpOut++;
        }
        *lpOut = *lpIn;
        lpOut++;

        if(*(lpIn + 1) == '=')
        {
            *lpOut = '=';
            if(*(lpIn + 2) != ' ')
            {
                *(lpOut + 1)= ' ';
                lpOut = lpOut + 2;
            }
            else
            {
                lpOut++;
            }
            lpIn ++; //注意：不要加2，在后面赋值时还要加1的
        }
        else
        {        
            if(*(lpIn + 1) != ' ')
            {
                *lpOut = ' ';
                lpOut++;
            }
        }
    }
    
    *lppIn = lpIn + 1;
    *lppOut = lpOut;

    return TRUE;
}

BOOL IsInclude(LPTSTR lpszOutCode, LPTSTR lpOut)
{
	TCHAR szINCLUDE[] = _T("#include");
	int nLen = sizeof(szINCLUDE) - 1;
	if(lpOut - lpszOutCode >= nLen)
	{
		if(!_tcsncmp(lpszOutCode, szINCLUDE, nLen))
		{
			return TRUE;
		} // 结束 if(!_tcsncmp(lpszOutCode, szINCLUDE, nLen))
	}
	return FALSE;
}

/*******************************************************************************************************
函数名：BigSign
功  能：大于、小于号
参  数：
         LPTSTR* lppIn：输入点
         LPTSTR* lppOut：输出点
         LPTSTR* lppStack：堆栈点
		 LPTSTR lpszOutCode：已格式化的代码
返回值：成功返回TRUE,否则返回FALSE.
版  本：1.0.0.1
作  者：康  林
时  间：2005-5-1 16:23:54
*******************************************************************************************************/
BOOL BigSign(LPTSTR * lppIn, LPTSTR * lppOut, LPTSTR * lppStack, LPTSTR lpszOutCode)
{
    LPTSTR lpIn, lpOut, lpStack;
    lpIn = *lppIn;
    lpOut = *lppOut;
    lpStack = *lppStack;
	TCHAR szINCLUDE[] = _T("#include");

	int nLen = sizeof(szINCLUDE) - 1;
	//考虑#include <stdio.h>情况。情BUG-13
	if(IsInclude(lpszOutCode, lpOut))
	{
		//考虑#include<stdio.h>情况
		if(lpOut - lpszOutCode == nLen && *(lpOut - 1) == _T('e') && *lpIn == _T('<'))
		{
			*lpOut = _T(' ');
			lpOut++;
		} // 结束 if(lpOut - lpszOutCode == nLen && *(lpOut - 1) == _T('e') && *lpIn == _T('<'))
		*lpOut = *lpIn;
		lpOut++;
		lpIn++;
		*lppIn = lpIn;
		*lppOut = lpOut;
		return TRUE;
	} // 结束 if(IsInclude(lpszOutCode, lpOut))

    *lppStack = lpIn;
    if(*(lpOut - 1) != ' ')
    {
        *lpOut = ' ';
        lpOut++;
    }
    *lpOut = *lpIn;
    lpOut++;
    if(*(lpIn + 1) == *lpIn)//>>
    {        
        lpIn++;
        *lpOut = *lpIn;
        lpOut++;
        if(*(lpIn + 1) == '=')//>>=
        {
            lpIn++;
            *lpOut = *lpIn;
            lpOut++;
        }
    }
    else if(*(lpIn + 1) == '=')//>=
    {
        lpIn++;
        *lpOut = *lpIn;
        lpOut++;
    }
    *lpOut = ' ';
    lpOut++;
    *lppOut = lpOut;
    *lppIn = lpIn + 1;
    return TRUE;
}

/*******************************************************************************************************
函数名：FormatVCCodeW
描  述：格式化VC代码
参  数：
        BSTR lpbszInCode ：要格式化的代码
		BSTR* lpbszOutCode：已格式化的代码
返回值：类型为 long 。失败,=0
        格式化后代码的长度(包括终结符),>0  
版  本：2005.6.0.1
作  者：康  林
时  间：2005年7月29日 10:35:37
*******************************************************************************************************/
extern "C" long WINAPI FormatVCCodeW( /*in*/BSTR bszInCode, /*out*/BSTR* lpbszOutCode)
{
	USES_CONVERSION;
	LPCTSTR lpszIn = W2CT(bszInCode);
	LPTSTR lpszOut = new TCHAR[8 * (_tcslen(lpszIn) + sizeof(lpszIn))];
	FormatVCCodeA(lpszIn, lpszOut);
	::SysFreeString(*lpbszOutCode);
	*lpbszOutCode = T2BSTR(lpszOut);
	delete []lpszOut;
	return ::SysStringByteLen(*lpbszOutCode);//lpbszOutCode->Length();
}

/*******************************************************************************************************
函数名：FormatVCCodeA
功  能：格式化VC代码
问  题：可能会输出溢出
参  数：
         LPCTSTR lpszInCode：要格式化的代码
         LPTSTR lpszOutCode：已格式化的代码
返回值：失败,=0
        格式化后代码的长度(包括终结符),>0        
版  本：1.0.0.1
作  者：康  林
时  间：2005-4-30 15:42:49
*******************************************************************************************************/
extern "C" long WINAPI FormatVCCodeA(/*in*/LPCTSTR lpszInCode, /*out*/LPTSTR lpszOutCode)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    LPTSTR lpIn/*正输入的字符*/, lpStack/*上一个输入的字符*/, lpOut/*输出的字符*/, lpCode;
    int iLen;
    TCHAR ch;
    BOOL bSpaceFlag;

#ifdef __LIMIT__
#pragma message ("定义 __LIMIT__")
     if(!Regist(FALSE, _T("微软开发环境工具集")))
     {
         _tcscpy(lpszOutCode, lpszInCode);
         return _tcslen(lpszOutCode);
     } // 结束 if(!Regist(FALSE, _T("微软开发环境工具集")))
#endif // 结束 #ifdef __LIMIT__

    bSpaceFlag = TRUE; //行开始空格 
    iLen = _tcslen(lpszInCode);
    lpCode = new TCHAR[iLen + sizeof(TCHAR)];
    _tcscpy(lpCode, lpszInCode);
    lpIn = lpCode;
    lpStack = lpIn;
    lpOut = lpszOutCode;

    while(*lpIn != NULL)
    {
        //TRACE(_T("%s(%d) : %s\n"), __FILE__, __LINE__, lpIn);
        
        switch(*lpIn)
        {            
        case _T('!'):
            lpStack = lpIn;
            if('=' == *(lpIn + 1))
            {
                if(' ' != *(lpOut - 1))
                {
                    *lpOut = ' ';
                    lpOut++;
                }
                *lpOut = *lpIn;
                lpOut++;
                lpIn++;
                *lpOut = *lpIn;
                lpIn++;
                lpOut++;
                *lpOut = ' ';
                lpOut++;
            }
            else
            {
                *lpOut = *lpIn;
                lpOut++;
                lpIn++;
            }
            break;
        case _T('/'):
			Division(&lpIn, &lpOut, &lpStack, bSpaceFlag, lpszOutCode);
            break;
        case _T('\\'):
            if(*(lpIn + 1) == '\'' || *(lpIn + 1) == '\"' || *(lpIn + 1) == '\\')
            {
                *lpOut = *lpIn;
                *(lpOut + 1) = *(lpIn + 1);
                lpOut += 2;
                lpIn += 2;
                break;
            } // 结束 if(*(lpIn + 1) == '\'' || *(lpIn + 1) == '\"' || *(lpIn + 1) == '\\')
            bSpaceFlag = FALSE;
            *lpOut = *lpIn;
            lpStack = lpIn;
            lpIn++;
            lpOut++;      
            break;
        case _T('\''):
        case _T('"'): //引号
            bSpaceFlag = FALSE;
            Quotation(&lpIn, &lpOut, &lpStack);
            break;
        case TAB: //制表符 Tab
            /*if(!bSpaceFlag)
            {
                *lpIn = ' ';
            }*/
        case _T(' '): //空格
            SpaceFormat(&lpIn, &lpOut, &lpStack, &bSpaceFlag, lpszOutCode);
            break;
        case _T(';'): //分号           
        case _T(','): //逗号
            bSpaceFlag = FALSE;
            Comma(&lpIn, &lpOut, &lpStack);
            break;
        case _T('-'):
        case _T('+'):
            AddFormat(&lpIn, &lpOut, &lpStack);
            break;
        case _T('>'):
        case _T('<'):
			BigSign(&lpIn, &lpOut, &lpStack, lpszOutCode);
            break;
		case _T('('):
        case _T(')'):
        case _T('['):
        case _T(']'):
            LitterBracket(&lpIn, &lpOut, &lpStack);
            break;
        case _T('{'):
        case _T('}'):
            BigBracket(&lpIn, &lpOut, &lpStack, lpszOutCode);
            break;
        case _T('*'):
            //增加:判断是否是指针  
            if(*(lpIn + 1) == '/')
            {
                //是注释 */
				*lpOut = *lpIn; 
                lpOut++;
                lpIn++;
                *lpOut = *lpIn ;
                lpStack = lpIn;
                lpOut++;
                lpIn++;                
                break;
            }
        case _T('&'):
            //增加:判断是否是取地址
            if(bSpaceFlag)//第一个字符为*
            {
                *lpOut = *lpIn;
                lpStack = lpIn;
                lpOut++;
                lpIn++;
                break;
			}
			if(*(lpOut - 1) == ' ')
            {
                ch = *(lpOut - 2);
            }
            else
            {
                ch = *(lpOut - 1);
            }
            if(('=' == ch || ',' == ch || ')' == ch || '(' == ch
                || '+' == ch || '-' == ch || '/' == ch || '*' == ch
                || '|' == ch || '&' == ch || '!' == ch || '^' == ch
                || '>' == ch || '<' == ch || '%' == ch
                || * lpStack == '{' || * lpStack == '}' /*形如: {&a=b;*/)
                && (*lpIn != *(lpIn + 1)) /*用于控制形如 a=(b||c)&&m 的。但它在形如 ************************* 时引起错误（已解决，是下面没加*判断）*/
                )
            {
                *lpOut = *lpIn;
                lpStack = lpIn;
                lpOut++;
                lpIn++;
                break;
            }
        //case _T('):'):
        //    if(*(lpIn + 1) == '):')
        //    {
        //        *lpOut = *lpIn;
        //        *(lpOut + 1) = *(lpIn + 1);
        //        lpOut += 2;
        //        lpIn += 2;
        //        break;
        //    } // 结束 if(*(lpIn + 1) == '):')
        case _T('^'):
        case _T('|'):             
        case _T('?'):
        case _T('%'):
        case _T('='):
            lpStack = lpIn;
            if(*(lpOut - 1) != ' ')
            {
                *lpOut = ' ';
                lpOut++;
            }
            *lpOut = *lpIn;
			lpOut++;
			//形如：== && || **
            if(('=' == *(lpIn + 1))
                || (*lpIn == '&' && *(lpIn + 1) == '&') 
				|| (*lpIn == '|' && *(lpIn + 1) == '|')
				|| (*lpIn = '*' && *(lpIn + 1) == '*'))
            {
                *lpOut = *(lpIn + 1);
                lpOut++;
                lpIn++;
            }            
            *lpOut = ' ';
            lpOut++;
            lpIn++;
            break;
        default:
            bSpaceFlag = FALSE;
            *lpOut = *lpIn;
            lpStack = lpIn;
            lpIn++;
            lpOut++;            
        }
    }
    *lpOut = (TCHAR)NULL;
	//TRACE(_T("%s(%d) : %s\n"), __FILE__, __LINE__, lpszOutCode);
    delete []lpCode;
    return _tcslen(lpszOutCode);
}

/*******************************************************************************************************
函数名：ValidCCodeW
描  述：去掉代码中的多余空格、制表符、换行符、注释、连接符（“\”）、前、后导空格。
注  意：代码中不含零字符。此代码以终结符结束。
参  数：
        BSTR* lpbszCode：输入代码
		CComBSTR* lpbszOut ：有效化后的代码
		BOOL bQutation     ：是否保留引号和引号之间的内容，默认为 TRUE，保留；FALSE，不保留
		BOOL bComment      ：当没有结束的注释符号时，是否保留注释
返回值：long
版  本：2005.6.0.1
作  者：康  林
时  间：2005年7月29日 10:36:48
*******************************************************************************************************/
extern "C" long WINAPI ValidCCodeW(BSTR bszCode, BSTR* lpbszOut, BOOL bQutation, BOOL bComment)
{
	ASSERT(bszCode != NULL);
	USES_CONVERSION;
	LPCTSTR lpszIn = W2CT(bszCode);
	LPTSTR lpszOut = new TCHAR[2 * (_tcslen(lpszIn) + sizeof(TCHAR))];
	ValidCCodeA(lpszIn, lpszOut, bQutation, bComment);
	::SysFreeString(*lpbszOut);
	*lpbszOut = T2BSTR(lpszOut);
	delete []lpszOut;
	return ::SysStringByteLen(*lpbszOut); 
}

/*******************************************************************************************************
函数名：ValidCCodeA
功  能：去掉代码中的多余空格、制表符、换行符、注释、连接符（“\”）、前、后导空格。
注  意：代码中不含零字符。此代码以终结符结束。
参  数：
         LPCTSTR lpszCode：输入代码
         LPTSTR lpszOut  ：有效化后的代码
         BOOL bQutation  ：是否保留引号和引号之间的内容，默认为 TRUE，保留；FALSE，不保留
		 BOOL bComment      ：当没有结束的注释符号时，是否保留注释
返回值：有效化后代码的长度
作  者：康  林
版  本：4.0.0.0
日  期：2005-7-9
时  间：6:03:00
*******************************************************************************************************/
extern "C" long WINAPI ValidCCodeA(LPCTSTR lpszCode, LPTSTR lpszOut, BOOL bQutation, BOOL bComment)
{
    LPTSTR lpOut, lpIn;
    LONG Len;
    Len = _tcslen(lpszCode) + sizeof(TCHAR);
    TCHAR *lppIn = new TCHAR[Len];
    _tcscpy(lppIn, lpszCode); 
    lpIn = lppIn;
    lpOut = lpszOut;
    while(*lpIn != NULL)
    {        
        switch(*lpIn)
        {
        case TAB:
            *lpIn = ' ';
        case _T(' '):
            SpaceC(&lpIn, &lpOut, lpszOut);
            break;
        case _T('\''):
        case _T('\"'):
            QuotationC(&lpIn, &lpOut, bQutation);
            break;
        case _T('/'):
            CommentC(&lpIn, &lpOut, bComment);
            break;
		case _T('\\'):
			//是连接符时
            if(*(lpIn + 1) == CR && *(lpIn + 2) == LF)
            {
                if(*(lpOut - 1) != _T(' '))
                {
                    *lpOut = _T(' ');
                    lpOut++;
                } // 结束 if(*(lpOut - 1) != _T(' '))
                lpIn += 3;
                break;
            } // 结束 if(*(lpIn + 1) == CR && *(lpIn + 2) == LF)
            if(*(lpIn + 1) == _T('\'') || *(lpIn + 1) == _T('\"') || *(lpIn + 1) == _T('\\'))
            {
               *lpOut = *lpIn;
               *(lpOut + 1) = *(lpIn + 1);
               lpOut += 2;
               lpIn += 2;
               break;
            } // 结束 if(*(lpIn + 1) == _T('\'') || *(lpIn + 1) == _T('\"') || *(lpIn + 1) == _T('\\'))
            *lpOut = *lpIn;
            lpOut++;
            lpIn++;
            break;
        case CR:
            if(*(lpIn + 1) == LF)
            {
                if(*(lpOut - 1) == _T('\\'))
                {
                    lpOut--;
                } // 结束 if(*(lpOut - 1) == _T('\\'))
                if(*(lpOut - 1) == _T(' ') && *(lpOut - 2) == _T('\\'))
                {
                    lpOut -= 2;
                } // 结束 if(*(lpOut - 1) == _T(' ') && *(lpOut - 2) == _T('\\'))
                if(*(lpOut-1) != _T(' '))
                {
                    *lpOut = _T(' ');
                    lpOut++;
                } // 结束 if(*lpOut != _T(' '))
                lpIn += 2;
                break;
            } // 结束 if(*(lpIn + 1) == LF)
			lpIn++;
            *lpOut = *lpIn;
            lpOut++;
            lpIn++;
            TRACE(_T("%s(%d) : 语法错误，CR 后面没有 LF。可能是linux下格式。\n"), __FILE__, __LINE__);
            break;
		case LF:
			*lpOut=_T(' ');
			lpIn++;
			lpOut++;
			break;
        default:           
            *lpOut = *lpIn;
            lpOut++;
            lpIn++;
            break;
        } // 结束 switch(*lpIn)
    } // 结束 while(lpIn != NULL)
    if(*(lpOut - 1) == ' ')
    {
        lpOut--;
    } // 结束 if(*(lpOut - 1) == ' ')
    *lpOut =(TCHAR) NULL;
	
    delete []lppIn;
    return _tcslen(lpszOut);
}

/*******************************************************************************************************
函数名：SpaceC
描  述：去掉多余的空格
参  数：
         LPTSTR* lppIn ：输入字符串指针
         LPTSTR* lppOut：输出字符串指针
         LPTSTR lppCode：输出字符串指针
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-21 13:33:47
*******************************************************************************************************/
void SpaceC(LPTSTR* lppIn, LPTSTR* lppOut, LPTSTR lppCode)
{
    LPTSTR lpIn = *lppIn;
    LPTSTR lpOut = *lppOut;
    if(*(lpOut - 1) != ' ' && lppCode != (lpOut - 1))
    {
        *lpOut = *lpIn;
        lpOut++;
    } // 结束 if(*(lpOut - 1) != ' ' && lppCode != (lpOut - 1))
    lpIn++;
    *lppIn = lpIn;
    *lppOut = lpOut;
    return;
}

/*******************************************************************************************************
函数名：QuotationC
描  述：保留引号中的字符
参  数：
         LPTSTR* lppIn ：输入字符串指针
         LPTSTR* lppOut：输出字符串指针
		 BOOL bQutation：是否保留引号和引号之间的内容，默认为 TRUE，保留；FALSE，不保留
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-21 13:35:14
*******************************************************************************************************/
void QuotationC(LPTSTR* lppIn, LPTSTR* lppOut, BOOL bQutation)
{
    LPTSTR lpIn = *lppIn;
    LPTSTR lpOut = *lppOut;
    TCHAR ch = *lpIn;
	if(bQutation)
	{
		*lpOut = ch;
		lpOut++;
	}
	lpIn++;
    while(*lpIn != NULL)
    {
        if(*lpIn == _T('\\') && (*(lpIn + 1) == _T('\'') || *(lpIn + 1) == _T('\"') || *(lpIn + 1) == _T('\\')))
        {
			if(bQutation)
			{
				*lpOut = *lpIn;
				*(lpOut + 1) = *(lpIn + 1);
				lpOut += 2;
			} // 结束 if(bQutation)			
            lpIn += 2;
            continue;
        } // 结束 if(*lpIn == _T('\\') && (*(lpIn + 1) == _T('\'') || *(lpIn + 1) == _T('\"') || *(lpIn + 1) == _T('\\')))
        if(*lpIn == ch)
        {
			if(bQutation)
			{
				*lpOut = *lpIn;
			}
			else
			{
				*lpOut = _T(' ');
			}
			lpOut++;
			lpIn++;
            *lppIn = lpIn;
            *lppOut = lpOut;
            return;
        } // 结束 if(*lpIn == ch)
		if(bQutation)
		{
			*lpOut = *lpIn;
			lpOut++;
		}
        lpIn++;
    } // 结束 while(*lpIn != NULL)
    *lppIn = lpIn;
    *lppOut = lpOut;
    TRACE(_T("%s(%d) : 语法错误，缺少右引号\n"), __FILE__, __LINE__);
}

/*******************************************************************************************************
函数名：CommentC
描  述：去掉字符串中的注释
参  数：
         LPTSTR* lppIn ：输入字符串指针
         LPTSTR* lppOut：输出字符串指针
		 BOOL bComment ：当没有注释结束符号时，是否保留注释。TRUE：保留；FALSE：不保留（默认）。
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-21 13:35:40
*******************************************************************************************************/
void CommentC(LPTSTR* lppIn, LPTSTR* lppOut, BOOL bComment)
{
    LPTSTR lpIn, lpOut, p;
    TCHAR end[2];
    lpIn = *lppIn; 
	p = lpIn;
    lpOut = *lppOut;
    if(*(lpIn + 1) == _T('*'))
    {
        end[0] = _T('*');
        end[1] = _T('/');
    }
    else if(*(lpIn + 1) == _T('/'))
    {
        end[0] = CR;
        end[1] = LF;
    }
    else
    {
        *lpOut = *lpIn;
        *lppOut = lpOut + 1;
        *lppIn = lpIn + 1;
        return;
    } // 结束 if(*(lpIn + 1) == _T('*'))

    lpIn += 2;
    while(*lpIn != NULL)
    {
		//考虑WINDOWS(CRLF)与LINUX(LF)下的换行符不同。
        if(((*lpIn == end[0] && *(lpIn + 1) == end[1]) && end[0] == _T('*'))
			|| (*(lpIn + 1) == end[1] && end[1] == LF))
        {
            *lppIn = lpIn + 2;
            return;
        } // 结束 if(*lpIn == end[0] && *(lpIn + 1) == end[1])
        lpIn++;
    } // 结束 while(*lpIn != NULL)
	if(bComment)
	{
		TRACE(_T("%s(%d) : 错误,缺少注释结束符：%c%c。保留注释。\n"), __FILE__, __LINE__, end[0], end[1]);
		while(*p != NULL)
		{
			*lpOut = *p;
			p++;
			lpOut++;
		}
	}
	else
	{
		TRACE(_T("%s(%d) : 错误,缺少注释结束符：%c%c。不保留注释。\n"), __FILE__, __LINE__, end[0], end[1]);
	}
    *lppIn = lpIn;
    *lppOut = lpOut;    
}
