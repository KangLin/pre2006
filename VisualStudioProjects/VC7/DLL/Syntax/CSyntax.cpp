/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����CSyntax.cpp
��  ����C�����﷨����
˼  ·����Ҫ����FormatVCCodeA���������ַ����������ݷָ���������ʽ��
��������
    FormatVCCodeW       ;�Զ���ʽ�� VC ���루֧��UCOIDE��
    FormatVCCodeA       ;�Զ���ʽ�� VC ����
    ValidCCode          ;ȥ�������еĶ���ո��Ʊ�������з���ע�͡����ӷ�����\������ǰ���󵼿ո�
    MatchSplitSymbol    ;ƥ��ָ���ķָ�����
    TrimSpace           ;��ȥ�ַ����еĿո�
��  ����2005.6.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��7��12��
ʱ  �䣺19:05:23
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
*******************************************************************************************************/
#include "stdafx.h"
#ifdef __LIMIT__
#include "Syntax.h"
#else
#include "CSyntax.h"
#endif

/*******************************************************************************************************
��������DeleteSpace
��  �ܣ�ɾ�������ַ����ж���Ŀ��ַ����Ʊ�����س��������з�  
��  ����
         LPCTSTR pszIn�������ַ���ָ��
         LPTSTR pszOut������ַ���ָ��
����ֵ���ɹ����ط���,ʧ�ܷ�����
��  ����1.0.0.1
��  �ߣ��� ��
ʱ  �䣺2005-5-4 14:32:32
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
		}//���� if(ch == TAB)
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
		}//���� if(ch == _T(' ') && *(pTmpOut - 1) == _T(' ') && pTmpOut != pszIn)
	}//���� while(*pTmpOut != NULL) 

    return _tcslen(pszOut);
}

/*******************************************************************************************************
��������DeleteSpace
��  �ܣ�ɾ���ո�
��  ����
         LPTSTR pszCode���ַ���
����ֵ���ɹ������ַ����ĳ��ȣ�ʧ�ܣ�����0
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-5-4 19:35:30
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
        TRACE(_T("%s(%d) : �����ڴ�ʧ��\n"), __FILE__, __LINE__);
        return 0;
    } //���� if(!pszTmp)
    ::ZeroMemory(pszTmp, iLen);

    pOut = pszTmp;
    p = pszCode;

    while(p < pszCode + iLen + sizeof(TCHAR))
    {
        ch = *p;
        if(TAB == ch || CR == ch || LF == ch)
        {
            ch = ' ';
        }//���� if(ch == TAB)
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
        }//���� if(*p == ' ' && pOut== ' ')        
    } //���� while(p < pszCode + iLen)
    _tcscpy(pszCode, pszTmp);
    delete []pszTmp;
    return _tcslen(pszCode);
}

/*******************************************************************************************************
��������TrimString
��  ����ȥ��ǰ�����󵼿��ַ����Ʊ�����س����з�
��  ����
        BSTR bszIn    ��Ҫȥ�����ַ����ַ���
		BSTR * pbszOut��ȥ����Ŀ��ַ����ַ���
����ֵ������Ϊ LONG ��ʧ�ܣ�����0
        �ɹ��������ַ����ĳ���(���ֽ�Ϊ��λ)
��  ����2005.6.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��31�� 18:06:58
*******************************************************************************************************/
extern "C" LONG _stdcall TrimString(BSTR bszIn, BSTR * pbszOut)
{
    INT iLen, iR;
   
    ASSERT(pbszOut != NULL);

	LPTSTR lpszOut = new TCHAR[2 * (::SysStringByteLen(bszIn) + sizeof(TCHAR))];
	if(!lpszOut)
	{
		return 0;
	} // ���� if(!lpszOut)
	__try
	{	USES_CONVERSION;
		iR = DeleteSpace(W2CT(bszIn), lpszOut);
		if(iR == 0)
		{
			__leave;
		} // ���� if(iR == 0)
		iLen = _tcslen(lpszOut);
		if(*(lpszOut + iLen - 1) == _T(' '))
		{
			*(lpszOut + iLen - 1) = NULL;
			iR -= 1;
		} //���� if(*(lpszOut + iLen - 1) == _T(' '))
		if(*lpszOut == _T(' '))
		{
			_tcscpy(lpszOut, lpszOut - 1);
			if(iR)
			{
				iR -= 1;
			}
		} //���� if(*lpszOut == _T(' '))
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
��������ReversionMatchSplitSymbolB
��  ��������ƥ��ָ���ķָ�������Ϊ API ���������� BASIC ���á�
ע  �⣺����ƥ�䣨������������������ָ���2�ڷָ���1ǰ������: �ָ���1Ϊ "(",�ָ���2Ϊ")"������ƥ�䣺��) a (�� ��
��  ����
        LPTSTR lpszSource��Դ���롣�ɹ��󣬰���Ϊ�ָ����м���ַ������������ָ�����
		LONG * nSource   �������󣬰���Ϊ�ָ����м���ַ������������ָ������ĳ���
		LPCTSTR lpStr1   ���ָ���1
		LPCTSTR lpStr2   ���ָ���2
		LPTSTR lpszBefor ���ָ���1ǰ���ַ��������������ָ�����
		LONG * nBefor    �������󣬷ָ���1ǰ���ַ��������������ָ������ĳ���
		LPTSTR lpszBack  ���ָ���2����ַ��������������ָ�����
		LONG * nBack     �������󣬷ָ���2����ַ��������������ָ������ĳ���
		BOOL bQutation   ���Ƿ�ƥ�������е��ַ���TRUE����ƥ�䣻FALSE��ƥ�䣨Ĭ��ֵ��
����ֵ������Ϊ LONG ��
        ʧ��,����-1,ȱ�ٷָ���1������-2,ȱ�ٷָ���2��
        �ɹ�,>0,��������ַ����ĳ���(�����ָ����ĳ���)
        û�зָ���,Ϊ0
��  ����2005.6.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��21�� 10:49:04
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
		} // ���� if(nSource)
		if(nBefor && lpszBefor)
		{
			_tcslen(lpszBefor);
		} // ���� if(nBefor && lpszBefor)
		if(nBack && lpszBack)
		{
			_tcslen(lpszBack);
		} // ���� if(nBack && lpszBack)
	} // ���� if(ir > 0)
	return ir;
}

/*******************************************************************************************************
��������ReversionMatchSplitSymbol
��  ��������ƥ��ָ���ķָ���
ע  �⣺����ƥ�䣨������������������ָ���2�ڷָ���1ǰ������: �ָ���1Ϊ "(",�ָ���2Ϊ")"������ƥ�䣺��) a (�� ��
��  ����
        LPTSTR lpszSource      ��Դ���롣�ɹ��󣬰���Ϊ�ָ����м���ַ������������ָ�����
		LPCTSTR lpStr1         ���ָ���1
		LPCTSTR lpStr2         ���ָ���2
		LPTSTR lpszBefor       ���ָ���1ǰ���ַ��������������ָ�����
		LPTSTR lpszBack        ���ָ���2����ַ��������������ָ�����
		BOOL bQutation         ���Ƿ�ƥ�������е��ַ���TRUE����ƥ�䣻FALSE��ƥ�䣨Ĭ��ֵ��
����ֵ��
��  ����2005.6.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��10�� 13:51:52
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
	} // ���� if(bQutation)
	
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
��������MatchSplitSymbolB
��  ����ƥ��ָ���ķָ�������ΪAPI��������BASIC����
ע  �⣺����ƥ�䣨������������������ָ���2�ڷָ���1ǰ������: �ָ���1Ϊ "(",�ָ���2Ϊ")"������ƥ�䣺��) a (�� ��
��  ����
        CComBSTR* lpszSource   ��Դ���롣�ɹ��󣬰���Ϊ�ָ����м���ַ������������ָ�������
		CComBSTR* lpStr1       ���ָ���1
		CComBSTR* lpStr2       ���ָ���2
		CComBSTR* lpszBefor    �������󣬷ָ���1ǰ���ַ��������������ָ�����
		CComBSTR* lpszBack     �������󣬷ָ���2����ַ��������������ָ�����
		BOOL bQutation         ���Ƿ�ƥ�������е��ַ���TRUE����ƥ�䣨Ĭ��ֵ����FALSE��ƥ��
		BOOL bReversionQutation���Ƿ��Ƿ���ƥ�䡣TRUE���Ƿ���ƥ�䣬FALSE�����Ƿ���ƥ�䣨Ĭ��ֵ��
����ֵ������Ϊ LONG ��
        ʧ��,����-1,ȱ�ٷָ���1������-2,ȱ�ٷָ���2��
        �ɹ�,>0,��������ַ����ĳ���(�����ָ����ĳ���)
        û�зָ���,Ϊ0
��  ����2005.6.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��29�� 10:33:24
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
		} // ���� if(ir > 0)
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
��������MatchSplitSymbolC
��  ����ƥ��ָ���ķָ���
ע  �⣺����ƥ�䣨������������������ָ���2�ڷָ���1ǰ������: �ָ���1Ϊ "(",�ָ���2Ϊ")"������ƥ�䣺��) a (�� ��
��  ����
        LPTSTR lpszSource      ��Դ���롣�ɹ��󣬰���Ϊ�ָ����м���ַ������������ָ�������
		LPCTSTR lpStr1         ���ָ���1
        LPCTSTR lpStr2         ���ָ���2
        LPTSTR lpszBefor       ���ָ���1ǰ���ַ��������������ָ�������
        LPTSTR lpszBack        ���ָ���2����ַ��������������ָ�������
		BOOL bQutation         ���Ƿ�ƥ�������е��ַ���TRUE����ƥ�䣨Ĭ��ֵ����FALSE��ƥ��
		BOOL bReversionQutation���Ƿ��Ƿ���ƥ�䡣TRUE���Ƿ���ƥ�䣬FALSE�����Ƿ���ƥ�䣨Ĭ��ֵ��
����ֵ��ʧ��,����-1,ȱ�ٷָ���1������-2,ȱ�ٷָ���2��
        �ɹ�,>0,��������ַ����ĳ���(�����ָ����ĳ���)
        û�зָ���,Ϊ0
��  ����2005.6.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��10�� 13:56:17
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
    INT iStack, iR /*����ֵ*/;
    INT iMS /*��һ���ָ���ƥ����ַ���*/, iME /*�ڶ����ָ���ƥ����ַ���*/;
    INT iLen1, iLen2; //�ָ����ĳ���
    INT iLen; //Դ�ַ����ĳ���
	BOOL bMatch;//����ƥ�䣨������������������ָ���2�ڷָ���1ǰ������: �ָ���1Ϊ "(",�ָ���2Ϊ")"������ƥ�䣺��) a (�� ��

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
		//��������
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
				TRACE(_T("%s(%d) : ����.���� \' �������\n"), __FILE__, __LINE__);
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
					} // ���� if(*lpSou == _T('\\') && (*(lpSou + 1) == _T('\'') || *(lpSou + 1) == _T('\"') || *(lpSou + 1) == _T('\\')))
					if(*(1 + lpSou) == _T('\\') && (*lpSou == _T('\'') || *lpSou == _T('\"') || *lpSou == _T('\\')) && bReversionQutation)
					{
						lpSou += 2;
						continue;
					} // ���� if(*lpSou == _T('\\') && (*(lpSou + 1) == _T('\'') || *(lpSou + 1) == _T('\"') || *(lpSou + 1) == _T('\\')))
					
					if(*lpSou == ch)
					{
						lpSou++;
						break;
					} // ���� if(*lpSou = ch && *(lpSou - 1) != _T('\\') || (*(lpSou - 2) == _T('\\') && *(lpSou - 1) == _T('\\') && *lpSou == ch)					
					lpSou++;
				} // ���� while(lpSou < lpszSource + iLen)
				if(lpSou >= lpszSource + iLen)
				{
					TRACE(_T("%s(%d) : ����.û�������ұ�����\n"), __FILE__, __LINE__);
					break;
				}
			} // ���� if((*lpSou == _T('\'') || *lpSou == _T('\"'))&& *(lpSou - 1) != _T('\\') || (*(lpSou - 2) == _T('\\') && *(lpSou - 1) == _T('\\') && (*lpSou == _T('\'') || *lpSou == _T('\"'))))
		} // ���� if(bQutation)
		if(lpSou >= lpszSource + iLen)
		{
			TRACE(_T("%s(%d) : ����.�����ұ�����,���������һ���ַ���\n"), __FILE__, __LINE__);
			break;
		} // ���� if(lpSou < lpszSource + iLen)

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
            } //���� if(*lpszSource == *(lpS + iMS))
            if(iMS == iLen1) //���һ���ָ���ƥ��ɹ�
            {
                iStack++;
				if(iStack == 0)
				{
					bMatch = TRUE;
				}
                lpSou = p + 1;
                if(iStack == 1)
                {
                    lpS = p + 1; //��¼��һ�������ָ���1��λ��(ָ��ָ�������ĵ�һ���ַ�)
                } //���� if(iStack == 1)
                break;
            } //���� if(iMS == iLen1 - 1)
           
            if(*p == *(lpStr2 + iME))
            {
                iME++;
            }
            else
            {
                iME = 0;
            } //���� if(*p == *(lpStr2 + iME))
            if(iME == iLen2) //��ڶ����ָ���ƥ��ɹ�
            {
                iStack--;
                lpSou = p + 1;
                if(iStack == 0)
                {
                    //��ȷƥ��,����
                    int iL;
                    p++;
                    iL = lpS - iLen1 - lpszSource;
					if(lpszBefor)
					{
						memcpy(lpszBefor, lpszSource, iL);
						*(lpszBefor + iL) = (TCHAR)NULL;  //�����ս��
					}
                    iL = lpszSource + iLen - p;
					if(lpszBack)
					{
						memcpy(lpszBack, p, iL);
						*(lpszBack + iL) = (TCHAR)NULL;   //�����ս��
					}
                    iL = p - iLen2 - lpS;
                    memcpy(lpszSource, lpS, iL);
                    *(lpszSource + iL) = (TCHAR)NULL;     //�����ս��
                    return iLen1 + iL + iLen2;
                } //���� if(iStack == 0)
                break;
            } //���� if(iME == iLen2 - 1)
            p++;
        } //���� while(p != NULL)
        
        if(iMS == iLen1 || iME == iLen2)
        {
            iMS = 0;
            iME = 0;
        } 
        else
        {
            lpSou++;
        } //���� if(iMS == iLen1 || iME == iLen2)        
    } //���� while(lpszSource != NULL)
    if(iStack == 0) //�޷ָ�����������ƥ�䣨������������������ָ���2�ڷָ���1ǰ������: �ָ���1Ϊ "(",�ָ���2Ϊ")"������ƥ�䣺��) a (�� ��
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
    else //�ָ�����ƥ��
    {
        if(iStack > 0)
		{
			return -2; //ȱ�ٷָ���2
		}
		else
		{
			return -1; //ȱ�ٷָ���1
		}
    } //���� if(iStack == 0)

}

/*******************************************************************************************************
��������MatchSplitSymbol
��  �ܣ�ƥ��ָ���ķָ���
ע  �⣺����ƥ�䣨������������������ָ���2�ڷָ���1ǰ������: �ָ���1Ϊ "(",�ָ���2Ϊ")"������ƥ�䣺��) a (�� ��
��  ����
         LPTSTR lpszSource��Դ���롣�ɹ��󣬰���Ϊ�ָ����м���ַ������������ָ�������
         LPCTSTR lpStr1��   �ָ���1
         LPCTSTR lpStr2��   �ָ���2
         LPTSTR lpszBefor�� �ָ���1ǰ���ַ��������������ָ�������
         LPTSTR lpszBack��  �ָ���2����ַ��������������ָ�������
����ֵ��ʧ��,����-1,ȴ�ٷָ���1������-2,ȴ�ٷָ���2��
        �ɹ�,>0,��������ַ����ĳ���(�����ָ����ĳ���)
        û�зָ���,Ϊ0
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005-5-4 19:13:06
*******************************************************************************************************/
extern "C" LONG _stdcall MatchSplitSymbol(LPTSTR lpszSource, 
                                         LPCTSTR lpStr1,
                                         LPCTSTR lpStr2, 
                                         LPTSTR lpszBefor,
                                         LPTSTR lpszBack)
{
    LPTSTR lpSou, p, lpS, lpE;
    INT iStack, iR /*����ֵ*/;
    INT iMS /*��һ���ָ���ƥ����ַ���*/, iME /*�ڶ����ָ���ƥ����ַ���*/;
    INT iLen1, iLen2; //�ָ����ĳ���
    INT iLen; //Դ�ַ����ĳ���
	BOOL bMatch;//����ƥ�䣨������������������ָ���2�ڷָ���1ǰ������: �ָ���1Ϊ "(",�ָ���2Ϊ")"������ƥ�䣺��) a (�� ��

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
            } //���� if(*lpszSource == *(lpS + iMS))
            if(iMS == iLen1) //���һ���ָ���ƥ��ɹ�
            {
                iStack++;
				if(iStack == 0)
				{
					bMatch = TRUE;
				}
                lpSou = p + 1;
                if(iStack == 1)
                {
                    lpS = p + 1; //��¼��һ�������ָ���1��λ��(ָ��ָ�������ĵ�һ���ַ�)
                } //���� if(iStack == 1)
                break;
            } //���� if(iMS == iLen1 - 1)
           
            if(*p == *(lpStr2 + iME))
            {
                iME++;
            }
            else
            {
                iME = 0;
            } //���� if(*p == *(lpStr2 + iME))
            if(iME == iLen2) //��ڶ����ָ���ƥ��ɹ�
            {
                iStack--;
                lpSou = p + 1;
                if(iStack == 0)
                {
                    //��ȷƥ��,����
                    int iL;
                    p++;
                    iL = lpS - iLen1 - lpszSource;
					if(lpszBefor)
					{
						::CopyMemory(lpszBefor, lpszSource, iL);
						*(lpszBefor + iL) = (TCHAR)NULL;   //�����ս��
					}
                    iL = lpszSource + iLen - p;
					if(lpszBack)
					{
						::CopyMemory(lpszBack, p, iL);
						*(lpszBack + iL) = (TCHAR)NULL;    //�����ս��
					}
                    iL = p - iLen2 - lpS;
                    ::CopyMemory(lpszSource, lpS, iL);
                    *(lpszSource + iL) = (TCHAR)NULL;  //�����ս��
                    return iLen1 + iL + iLen2;
                } //���� if(iStack == 0)
                break;
            } //���� if(iME == iLen2 - 1)
            p++;
        } //���� while(p != NULL)
        
        if(iMS == iLen1 || iME == iLen2)
        {
            iMS = 0;
            iME = 0;
        } 
        else
        {
            lpSou++;
        } //���� if(iMS == iLen1 || iME == iLen2)        
    } //���� while(lpszSource != NULL)
    if(iStack == 0) //�޷ָ�����������ƥ�䣨������������������ָ���2�ڷָ���1ǰ������: �ָ���1Ϊ "(",�ָ���2Ϊ")"������ƥ�䣺��) a (�� ��
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
    else //�ָ�����ƥ��
    {
		if(iStack > 0)
		{
			return -2; //ȴ�ٷָ���2
		}
		else
		{
			return -1; //ȴ�ٷָ���1
		}
    } //���� if(iStack == 0)
}

/*******************************************************************************************************
��������Quotation
��  �ܣ�����
��  ����
         LPTSTR* lppIn�������
         LPTSTR* lppOut�������
         LPTSTR* lppStack����ջ��
����ֵ���ɹ�����TRUE,���򷵻�FALSE.
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-4-30 22:23:51
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
        } // ���� if(*lpIn == '\\' && (*(lpIn + 1) == '\'' || *(lpIn + 1) == '\"' || *(lpIn+1) == '\\'))
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
    TRACE(_T("%s(%d) : ����,ȱ��������\n"), __FILE__, __LINE__);
    return FALSE;
}

/*******************************************************************************************************
��������SpaceFormat
��  �ܣ��ո���Ʊ��
��  ����
         LPTSTR* lppIn�������
         LPTSTR* lppOut�������
         LPTSTR* lppStack����ջ��
         BOOL* bFlag���Ƿ����п�ʼ��־
����ֵ���ɹ�����TRUE,���򷵻�FALSE
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-5-1 7:45:42
*******************************************************************************************************/
BOOL SpaceFormat(LPTSTR* lppIn, LPTSTR* lppOut, LPTSTR* lppStack, BOOL* bFlag, LPTSTR lpOutCode)
{
    LPTSTR lpIn, lpOut, lpStack;
    lpIn = *lppIn;
    lpOut = *lppOut;
    lpStack = *lppStack;
    

    if(*bFlag) //�п�ʼʱ
    {
        *lpOut = *lpIn;
        lpStack = lpIn;
        lpOut++;
        lpIn++;
    }
    else //�����п�ʼʱ
    {
        if(*(lpOut - 1) != ' ' //����ַ����Ķ����ǿո�              
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
                //�ո����ע��ʱ���������пո�
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
                || (*lpIn == _T('*') && *(lpIn + 1) != _T('/')) /*����ע�ͽ�����ʱ*/
				|| *lpIn == _T('&')))
			{
                *lpOut = *lpIn;
                lpStack = lpIn;
                lpIn++;
                lpOut++;	
			} // ���� if(*bFlag && (*lpIn == _T(';') || *lpIn == _T(',') || *lpIn == _T('(') || *lpIn == _T(')') || *lpIn == _T('[') || *lpIn == _T(']') || (*lpIn == _T('*')&& *(lpIn + 1) != _T('/')) || *lpIn == _T('&')))
            *lppStack = lpStack;
            *lppOut = lpOut;
            *lppIn = lpIn;
            *bFlag = FALSE;
            return TRUE;
        } //���� if(*lpIn != ' ' && * lpIn != TAB)

        if(*bFlag) //�п�ʼʱ�������ո�
        {
            *lpOut = *lpIn;
            lpOut++;            
        }
        lpIn++;
    }
    if(*(lpOut - 1) == ' ')
    {
        //�ո���������
        lpOut--;
    }
    *lppStack = lpIn;
    *lppOut = lpOut;
    *lppIn = lpIn;
    return FALSE;
}

/*******************************************************************************************************
��������Comma
��  �ܣ��ֺš�����
��  ����
         LPTSTR* lppIn�������
         LPTSTR* lppOut�������
         LPTSTR* lppStack����ջ��
����ֵ���ɹ�����TRUE,���򷵻�FALSE.
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-5-1 11:22:00
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
��������LitterBracket
��  �ܣ�С���š�������
��  ����
         LPTSTR* lppIn�������
         LPTSTR* lppOut�������
         LPTSTR* lppStack����ջ��
����ֵ���ɹ�����TRUE,���򷵻�FALSE.
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-5-1 11:28:55
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
        //���� delete []p;
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
            //���� delete []p;
			if(*lpIn == _T('[')
				&& (*(lpOut - 2) == _T('e') && *(lpOut - 3) == _T('t') && *(lpOut - 4) == _T('e') && *(lpOut - 5) == _T('l')
				&& *(lpOut - 6) == _T('e') && *(lpOut - 7) == _T('d')))
            {
                break;
            } // ���� if(*lpIn == _T('[') && (*(lpOut - 2) == _T('e') && *(lpOut - 3) == _T('t') && *(lpOut - 4) == _T('e') && *(lpOut - 5) == _T('l') && *(lpOut - 6) == _T('e') && *(lpOut - 7) == _T('d')))
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
��������BigBracket
��  �ܣ�������
��  ����
         LPTSTR* lppIn�������
         LPTSTR* lppOut�������
         LPTSTR* lppStack����ջ��
		 LPTSTR lpOutCode���Ѹ�ʽ���Ĵ���
����ֵ���ɹ�����TRUE,���򷵻�FALSE.
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-5-1 12:00:02
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
    //���л��з�
    if(*(lp - 1) == CR && *lp == LF)
    {
        bFace = FALSE;
    }

    if(bFace)
    {
        *lpOut = CR;
        *(lpOut + 1) = LF;
        lpOut += 2;
    }//���� if(bFace)
   
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
                    //����: {/a  //ע��...
                    bAfter = TRUE;
                    break;
                }
                else
                {
                    bAfter = FALSE;
                    break;
				}
            } //���� if(2 == iR)

            if(*lpIn == ';')
            {
                bAfter = FALSE;
                break;
            }//���� if(*lpIn == ';')

            bAfter = TRUE;
            break;
        }
        lpIn++;
    } //���� while(*lpIn != NULL)
  
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
��������Division
��  �ܣ�����
��  ����
         LPTSTR* lppIn�������
         LPTSTR* lppOut�������
         LPTSTR* lppStack����ջ��
         BOOL bFlag���п�ʼ�Ƿ��ǿո�
		 LPTSTR lpOutCode����ʽ���Ĵ������ָ��
         BOOL bComment��ֻ����ע�������ΪTRUE�����������������ΪFALSE��Ĭ��ΪFALSE
����ֵ����ע��//������1
        ��ע�� /*, ����2
        �ǳ��� / ������3
        ����ע�ͣ�����4
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-5-1 16:24:34
*******************************************************************************************************/
INT Division(LPTSTR * lppIn, LPTSTR * lppOut, LPTSTR * lppStack, BOOL bFlag, LPTSTR lpOutCode, BOOL bComment)
{
    LPTSTR lpIn, lpOut, lpStack;
    lpIn = *lppIn;
    lpOut = *lppOut;
    lpStack = *lppStack;

    *lppStack = lpIn;
	if(*(lpIn + 1) == '/') //ע��// 
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
		return 1; //ע��// 
    } // ���� if(*(lpIn + 1) == '/')
    if(*(lpIn + 1) == '*') //ע��/*...*/
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
		return 2; //ע��/*...*/
    } //if(*(lpIn + 1) == '*') //ע��/*...*/
    
    if(bComment)
    {
        //������� BigBracket �еı������ķ���ֵΪ 4 �����
        return 4; //����ע��
	}

	//����#include <sys/net.h>���
	if(IsInclude(lpOutCode, lpOut))
	{
		*lpOut =* lpIn;
		lpOut++;
		lpIn++;
		*lppOut = lpOut;
		*lppIn = lpIn;
		return 5;
	} // ���� if(IsInclude(lpOutCode, lpOut))

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
��������AddFormat
��  �ܣ��Ӻš�����
��  ����
         LPTSTR* lppIn��
         LPTSTR* lppOut��
         LPTSTR* lppStack��
����ֵ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-5-1 16:56:03
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

    //�ж�����
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
            lpIn ++; //ע�⣺��Ҫ��2���ں��渳ֵʱ��Ҫ��1��
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
		} // ���� if(!_tcsncmp(lpszOutCode, szINCLUDE, nLen))
	}
	return FALSE;
}

/*******************************************************************************************************
��������BigSign
��  �ܣ����ڡ�С�ں�
��  ����
         LPTSTR* lppIn�������
         LPTSTR* lppOut�������
         LPTSTR* lppStack����ջ��
		 LPTSTR lpszOutCode���Ѹ�ʽ���Ĵ���
����ֵ���ɹ�����TRUE,���򷵻�FALSE.
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-5-1 16:23:54
*******************************************************************************************************/
BOOL BigSign(LPTSTR * lppIn, LPTSTR * lppOut, LPTSTR * lppStack, LPTSTR lpszOutCode)
{
    LPTSTR lpIn, lpOut, lpStack;
    lpIn = *lppIn;
    lpOut = *lppOut;
    lpStack = *lppStack;
	TCHAR szINCLUDE[] = _T("#include");

	int nLen = sizeof(szINCLUDE) - 1;
	//����#include <stdio.h>�������BUG-13
	if(IsInclude(lpszOutCode, lpOut))
	{
		//����#include<stdio.h>���
		if(lpOut - lpszOutCode == nLen && *(lpOut - 1) == _T('e') && *lpIn == _T('<'))
		{
			*lpOut = _T(' ');
			lpOut++;
		} // ���� if(lpOut - lpszOutCode == nLen && *(lpOut - 1) == _T('e') && *lpIn == _T('<'))
		*lpOut = *lpIn;
		lpOut++;
		lpIn++;
		*lppIn = lpIn;
		*lppOut = lpOut;
		return TRUE;
	} // ���� if(IsInclude(lpszOutCode, lpOut))

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
��������FormatVCCodeW
��  ������ʽ��VC����
��  ����
        BSTR lpbszInCode ��Ҫ��ʽ���Ĵ���
		BSTR* lpbszOutCode���Ѹ�ʽ���Ĵ���
����ֵ������Ϊ long ��ʧ��,=0
        ��ʽ�������ĳ���(�����ս��),>0  
��  ����2005.6.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��29�� 10:35:37
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
��������FormatVCCodeA
��  �ܣ���ʽ��VC����
��  �⣺���ܻ�������
��  ����
         LPCTSTR lpszInCode��Ҫ��ʽ���Ĵ���
         LPTSTR lpszOutCode���Ѹ�ʽ���Ĵ���
����ֵ��ʧ��,=0
        ��ʽ�������ĳ���(�����ս��),>0        
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-4-30 15:42:49
*******************************************************************************************************/
extern "C" long WINAPI FormatVCCodeA(/*in*/LPCTSTR lpszInCode, /*out*/LPTSTR lpszOutCode)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    LPTSTR lpIn/*��������ַ�*/, lpStack/*��һ��������ַ�*/, lpOut/*������ַ�*/, lpCode;
    int iLen;
    TCHAR ch;
    BOOL bSpaceFlag;

#ifdef __LIMIT__
#pragma message ("���� __LIMIT__")
     if(!Regist(FALSE, _T("΢�����������߼�")))
     {
         _tcscpy(lpszOutCode, lpszInCode);
         return _tcslen(lpszOutCode);
     } // ���� if(!Regist(FALSE, _T("΢�����������߼�")))
#endif // ���� #ifdef __LIMIT__

    bSpaceFlag = TRUE; //�п�ʼ�ո� 
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
            } // ���� if(*(lpIn + 1) == '\'' || *(lpIn + 1) == '\"' || *(lpIn + 1) == '\\')
            bSpaceFlag = FALSE;
            *lpOut = *lpIn;
            lpStack = lpIn;
            lpIn++;
            lpOut++;      
            break;
        case _T('\''):
        case _T('"'): //����
            bSpaceFlag = FALSE;
            Quotation(&lpIn, &lpOut, &lpStack);
            break;
        case TAB: //�Ʊ�� Tab
            /*if(!bSpaceFlag)
            {
                *lpIn = ' ';
            }*/
        case _T(' '): //�ո�
            SpaceFormat(&lpIn, &lpOut, &lpStack, &bSpaceFlag, lpszOutCode);
            break;
        case _T(';'): //�ֺ�           
        case _T(','): //����
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
            //����:�ж��Ƿ���ָ��  
            if(*(lpIn + 1) == '/')
            {
                //��ע�� */
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
            //����:�ж��Ƿ���ȡ��ַ
            if(bSpaceFlag)//��һ���ַ�Ϊ*
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
                || * lpStack == '{' || * lpStack == '}' /*����: {&a=b;*/)
                && (*lpIn != *(lpIn + 1)) /*���ڿ������� a=(b||c)&&m �ġ����������� ************************* ʱ��������ѽ����������û��*�жϣ�*/
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
        //    } // ���� if(*(lpIn + 1) == '):')
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
			//���磺== && || **
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
��������ValidCCodeW
��  ����ȥ�������еĶ���ո��Ʊ�������з���ע�͡����ӷ�����\������ǰ���󵼿ո�
ע  �⣺�����в������ַ����˴������ս��������
��  ����
        BSTR* lpbszCode���������
		CComBSTR* lpbszOut ����Ч����Ĵ���
		BOOL bQutation     ���Ƿ������ź�����֮������ݣ�Ĭ��Ϊ TRUE��������FALSE��������
		BOOL bComment      ����û�н�����ע�ͷ���ʱ���Ƿ���ע��
����ֵ��long
��  ����2005.6.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��29�� 10:36:48
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
��������ValidCCodeA
��  �ܣ�ȥ�������еĶ���ո��Ʊ�������з���ע�͡����ӷ�����\������ǰ���󵼿ո�
ע  �⣺�����в������ַ����˴������ս��������
��  ����
         LPCTSTR lpszCode���������
         LPTSTR lpszOut  ����Ч����Ĵ���
         BOOL bQutation  ���Ƿ������ź�����֮������ݣ�Ĭ��Ϊ TRUE��������FALSE��������
		 BOOL bComment      ����û�н�����ע�ͷ���ʱ���Ƿ���ע��
����ֵ����Ч�������ĳ���
��  �ߣ���  ��
��  ����4.0.0.0
��  �ڣ�2005-7-9
ʱ  �䣺6:03:00
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
			//�����ӷ�ʱ
            if(*(lpIn + 1) == CR && *(lpIn + 2) == LF)
            {
                if(*(lpOut - 1) != _T(' '))
                {
                    *lpOut = _T(' ');
                    lpOut++;
                } // ���� if(*(lpOut - 1) != _T(' '))
                lpIn += 3;
                break;
            } // ���� if(*(lpIn + 1) == CR && *(lpIn + 2) == LF)
            if(*(lpIn + 1) == _T('\'') || *(lpIn + 1) == _T('\"') || *(lpIn + 1) == _T('\\'))
            {
               *lpOut = *lpIn;
               *(lpOut + 1) = *(lpIn + 1);
               lpOut += 2;
               lpIn += 2;
               break;
            } // ���� if(*(lpIn + 1) == _T('\'') || *(lpIn + 1) == _T('\"') || *(lpIn + 1) == _T('\\'))
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
                } // ���� if(*(lpOut - 1) == _T('\\'))
                if(*(lpOut - 1) == _T(' ') && *(lpOut - 2) == _T('\\'))
                {
                    lpOut -= 2;
                } // ���� if(*(lpOut - 1) == _T(' ') && *(lpOut - 2) == _T('\\'))
                if(*(lpOut-1) != _T(' '))
                {
                    *lpOut = _T(' ');
                    lpOut++;
                } // ���� if(*lpOut != _T(' '))
                lpIn += 2;
                break;
            } // ���� if(*(lpIn + 1) == LF)
			lpIn++;
            *lpOut = *lpIn;
            lpOut++;
            lpIn++;
            TRACE(_T("%s(%d) : �﷨����CR ����û�� LF��������linux�¸�ʽ��\n"), __FILE__, __LINE__);
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
        } // ���� switch(*lpIn)
    } // ���� while(lpIn != NULL)
    if(*(lpOut - 1) == ' ')
    {
        lpOut--;
    } // ���� if(*(lpOut - 1) == ' ')
    *lpOut =(TCHAR) NULL;
	
    delete []lppIn;
    return _tcslen(lpszOut);
}

/*******************************************************************************************************
��������SpaceC
��  ����ȥ������Ŀո�
��  ����
         LPTSTR* lppIn �������ַ���ָ��
         LPTSTR* lppOut������ַ���ָ��
         LPTSTR lppCode������ַ���ָ��
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-21 13:33:47
*******************************************************************************************************/
void SpaceC(LPTSTR* lppIn, LPTSTR* lppOut, LPTSTR lppCode)
{
    LPTSTR lpIn = *lppIn;
    LPTSTR lpOut = *lppOut;
    if(*(lpOut - 1) != ' ' && lppCode != (lpOut - 1))
    {
        *lpOut = *lpIn;
        lpOut++;
    } // ���� if(*(lpOut - 1) != ' ' && lppCode != (lpOut - 1))
    lpIn++;
    *lppIn = lpIn;
    *lppOut = lpOut;
    return;
}

/*******************************************************************************************************
��������QuotationC
��  �������������е��ַ�
��  ����
         LPTSTR* lppIn �������ַ���ָ��
         LPTSTR* lppOut������ַ���ָ��
		 BOOL bQutation���Ƿ������ź�����֮������ݣ�Ĭ��Ϊ TRUE��������FALSE��������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-21 13:35:14
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
			} // ���� if(bQutation)			
            lpIn += 2;
            continue;
        } // ���� if(*lpIn == _T('\\') && (*(lpIn + 1) == _T('\'') || *(lpIn + 1) == _T('\"') || *(lpIn + 1) == _T('\\')))
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
        } // ���� if(*lpIn == ch)
		if(bQutation)
		{
			*lpOut = *lpIn;
			lpOut++;
		}
        lpIn++;
    } // ���� while(*lpIn != NULL)
    *lppIn = lpIn;
    *lppOut = lpOut;
    TRACE(_T("%s(%d) : �﷨����ȱ��������\n"), __FILE__, __LINE__);
}

/*******************************************************************************************************
��������CommentC
��  ����ȥ���ַ����е�ע��
��  ����
         LPTSTR* lppIn �������ַ���ָ��
         LPTSTR* lppOut������ַ���ָ��
		 BOOL bComment ����û��ע�ͽ�������ʱ���Ƿ���ע�͡�TRUE��������FALSE����������Ĭ�ϣ���
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-21 13:35:40
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
    } // ���� if(*(lpIn + 1) == _T('*'))

    lpIn += 2;
    while(*lpIn != NULL)
    {
		//����WINDOWS(CRLF)��LINUX(LF)�µĻ��з���ͬ��
        if(((*lpIn == end[0] && *(lpIn + 1) == end[1]) && end[0] == _T('*'))
			|| (*(lpIn + 1) == end[1] && end[1] == LF))
        {
            *lppIn = lpIn + 2;
            return;
        } // ���� if(*lpIn == end[0] && *(lpIn + 1) == end[1])
        lpIn++;
    } // ���� while(*lpIn != NULL)
	if(bComment)
	{
		TRACE(_T("%s(%d) : ����,ȱ��ע�ͽ�������%c%c������ע�͡�\n"), __FILE__, __LINE__, end[0], end[1]);
		while(*p != NULL)
		{
			*lpOut = *p;
			p++;
			lpOut++;
		}
	}
	else
	{
		TRACE(_T("%s(%d) : ����,ȱ��ע�ͽ�������%c%c��������ע�͡�\n"), __FILE__, __LINE__, end[0], end[1]);
	}
    *lppIn = lpIn;
    *lppOut = lpOut;    
}
