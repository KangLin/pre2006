/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����Dialog.cpp
��  �������öԻ�����Դ�ĺ���
��������
    MatchSplitSymbol    ;ƥ��ָ���ķ��Ŷ�
    PathRelativePath    ;ת·��Ϊ���·��
    GetRelativePath     ;�õ����·��,�����Ƶ����а���
��  ����2005.6.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��7��6��
ʱ  �䣺14:01:47
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
*******************************************************************************************************/

#include "stdafx.h"
#include "Dialog.h"
#include "IncludefIle.h"

///*******************************************************************************************************
//��������ShowLicense
//��  ������ʾ���֤
//��  ������
//����ֵ��
//��  ����2005.6.0.1
//��  �ߣ���  ��
//ʱ  �䣺2005��7��6�� 13:36:34
//*******************************************************************************************************/
//extern "C" BOOL WINAPI ShowLicense()
//{
//    AFX_MANAGE_STATE(AfxGetStaticModuleState());
//    AfxEnableControlContainer();
//    //MessageBox(NULL, "ok", NULL, MB_OK);
//    CLicense licens;
//    if(IDOK == licens.DoModal())
//    {
//        if(licens.m_bShow)
//            return TRUE;
//        else
//            return FALSE;
//    }
//    return TRUE;
//}

/*******************************************************************************************************
��������GetRelativePath
��  �����õ����·��
��  ����
         LPTSTR lpszDes �����·��
         LPCTSTR lpszSou��Դ·��
         BOOL bClipboard���Ƿ��Ƶ����а�,Ĭ��ΪTRUE
����ֵ��·���ĳ���
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-9 10:09:39
*******************************************************************************************************/
extern "C" int WINAPI GetRelativePath(/*in*/BSTR* lpszDes, /*in*/BSTR lpszSou, /*in*/BOOL bClipboard)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CRelativePath rel;
    USES_CONVERSION;
    rel.m_bClipboard = bClipboard;
    if(W2T(lpszSou))
    {
        rel.m_szSource = W2T(lpszSou);
    }

    if(rel.DoModal() == IDOK)
    {
        if(lpszDes)
        {
			LPTSTR lpOut = new TCHAR[MAX_PATH];
            _tcscpy(lpOut, rel.m_szRelative);
			::SysFreeString(*lpszDes);
			*lpszDes = T2BSTR(lpOut);
			delete []lpOut;
			return ::SysStringByteLen(*lpszDes);
        }
    }
    return 0;
}

extern "C" LONG GetIncludeFile(LPTSTR lpszFile,LPCTSTR lpszInFile)
{
	ASSERT(lpszFile != NULL);
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CIncludeFile f;
	f.m_szDocument = lpszInFile;
	if(f.DoModal() == IDOK)
	{
		_tcscpy(lpszFile, f.m_szRelative);
		return _tcslen(lpszFile);
	} // ���� if(f.DoModal() == IDOK)
	return 0;
}