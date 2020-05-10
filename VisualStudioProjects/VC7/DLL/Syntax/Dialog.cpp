/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：Dialog.cpp
描  述：调用对话框资源的函数
函数例表：
    MatchSplitSymbol    ;匹配指定的符号对
    PathRelativePath    ;转路径为相对路径
    GetRelativePath     ;得到相对路径,并复制到剪切板中
版  本：2005.6.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年7月6日
时  间：14:01:47
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/

#include "stdafx.h"
#include "Dialog.h"
#include "IncludefIle.h"

///*******************************************************************************************************
//函数名：ShowLicense
//描  述：显示许可证
//参  数：无
//返回值：
//版  本：2005.6.0.1
//作  者：康  林
//时  间：2005年7月6日 13:36:34
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
函数名：GetRelativePath
描  述：得到相对路径
参  数：
         LPTSTR lpszDes ：相对路径
         LPCTSTR lpszSou：源路径
         BOOL bClipboard：是否复制到剪切板,默认为TRUE
返回值：路径的长度
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-9 10:09:39
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
	} // 结束 if(f.DoModal() == IDOK)
	return 0;
}