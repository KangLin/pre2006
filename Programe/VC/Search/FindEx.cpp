/*******************************************************************************************************
文件名：FindEx.cpp
功  能：implementation of the CFindEx class.
             ||外部调用
            \\//
             \/
		SearchDirectory
		     ||
			\\//
			 \/
    SearchFileAndDirectory
             ||
	是文件	 ||  是目录
     ==================
	||                ||
   \\//              \\//
    \/                \/
  OnFile	      OnDirectory
编译器：Visual C++ 6.0
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-30
时  间：12:20:12
*******************************************************************************************************/

#include "stdafx.h"
#include "Search.h"
#include "FindEx.h"
#include "SearchDoc.h"
#include "SearchView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFindEx::CFindEx()
{

}

CFindEx::~CFindEx()
{

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//以下是完成 ===文件或目录的查找=== 功能的函数块
//

/*******************************************************************************************************
函数名：SearchDirectory
功  能：对指定的目录进行查找
参  数：
         LPCSTR szDir：要查找的目录
         BOOL bStop：如查为TRUE,则停止查找。默认为FALSE。
返回值：如果成功返回，TRUE，否则，返回FALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-30
时  间：12:20:53
*******************************************************************************************************/
BOOL CFindEx::SearchDirectory(LPCSTR szDir, BOOL bStop)
{
	CString szFileName;
	szFileName = szDir;
	if(szFileName.Right(1) != _T("\\"))
		szFileName += _T("\\");
	szFileName += _T("*.*");
	WIN32_FIND_DATA wfd;
	HANDLE hd = FindFirstFile(szFileName, &wfd);
	if(hd)
	{
		szFileName = szDir;
		szFileName += _T("\\");
		szFileName += wfd.cFileName;
		SearchFileAndDirectory(szFileName, &bStop);
	}
	while(FindNextFile(hd, &wfd))
	{
		if(bStop)//停止查找
			return false;
		szFileName = szDir;
		szFileName += _T("\\");
		szFileName += wfd.cFileName;
		SearchFileAndDirectory(szFileName, &bStop);
		//是目录,递归查找
		if((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			&& (_tcscmp(wfd.cFileName, ".") && _tcscmp(wfd.cFileName, "..")))
		{
			SearchDirectory((LPCSTR)szFileName, bStop);
		}

	}
	FindClose(hd);
	return true;
}

/*******************************************************************************************************
函数名：SearchFileAndDirectory
功  能：找到的文件和目录，由SearchDirectory调用。
        在这里可以加入你自己的代码
参  数：
         LPCSTR szFile：查找到的目录或文件
         BOOL *bpStop：如查为TRUE,则停止查找。默认为FALSE。
返回值：如果成功返回，TRUE，否则，返回FALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-30
时  间：12:22:48
*******************************************************************************************************/
BOOL CFindEx::SearchFileAndDirectory(LPCSTR szFile, BOOL *bpStop)
{
	TRACE("%s\n", szFile);
	if(::GetFileAttributes(szFile) & FILE_ATTRIBUTE_DIRECTORY)
	{//目录
		OnDirectory(szFile);
	}
	else//文件
	{
		OnFile(szFile);
	}
	return true;
}

/*******************************************************************************************************
函数名：OnFile
功  能：找到的文件，由SearchFileAndDirectory调用。
        在这里可以加入你要处理的代码。
参  数：
         LPCSTR szFile：查找到的文件名
返回值：如果成功返回，TRUE，否则，返回FALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-30
时  间：12:24:19
*******************************************************************************************************/
BOOL CFindEx::OnFile(LPCSTR szFile)
{
	TRACE(_T("文件:%s\n"), szFile);
	CMDIFrameWnd* MWnd = (CMDIFrameWnd*)AfxGetMainWnd();
	CMDIChildWnd* ChildWnd = MWnd->MDIGetActive();
	CSearchView* SearchView =(CSearchView*)ChildWnd->GetActiveView();
	ASSERT(SearchView->IsKindOf(RUNTIME_CLASS(CSearchView)));
	CString str;
    SearchView->m_ctrBtSearch.GetWindowText(str);
	//查找文件
    if(!_tcsicmp(str, _T("查找文件(&S)")))
	{
		if(!_tcsicmp(GetFileName(szFile), SearchView->m_szFileName))
			SearchView->m_lstFile.AddString(szFile);
	}
	//查找文本
	if(!_tcsicmp(str, _T("查找文字(&T)")))
	{
		if(FindWordInFile(szFile, SearchView->m_szFileName))
			SearchView->m_lstFile.AddString(szFile);
	}
	return true;
}

/*******************************************************************************************************
函数名：OnDirectory
功  能：查找到的目录。由SearchFileAndDirectory调用。
        在这里可以加入你要处理的代码。
参  数：
         LPCSTR szDir：查找到的目录
返回值：如果成功返回，TRUE，否则，返回FALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-30
时  间：12:26:06
*******************************************************************************************************/
BOOL CFindEx::OnDirectory(LPCSTR szDir)
{
	TRACE(_T("目录:%s\n"), szDir);
	return true;
}

//
//以上是完成 ===文件或目录的查找=== 功能的函数块
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/*******************************************************************************************************
函数名：GetFileName
功  能：得到指定文件夹的文件名。
参  数：
         LPCSTR szFileName：指定的文件（包含有路径）。
返回值：指定文件夹的文件名（不包含路径）。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-30
时  间：12:26:38
*******************************************************************************************************/
CString CFindEx::GetFileName(LPCSTR szFileName)
{
	CString szFile;
	szFile = szFileName;
	szFile = szFile.Right(szFile.GetLength() - szFile.ReverseFind('\\') -1);
	return szFile;
}

/*******************************************************************************************************
函数名：FindWordInFile
功  能：在文件中找查找指定的文本
参  数：
         LPCSTR FileName：文件
         LPCSTR Word：要查找的文本
返回值：如果找到返回TRUE,否则返回FALSE.
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-30
时  间：12:57:54
*******************************************************************************************************/
BOOL CFindEx::FindWordInFile(LPCSTR FileName, LPCSTR Word)
{
	TRY
	{
		CFile cf(FileName,CFile::modeRead );
		int len = cf.GetLength();
		char* p = new char[len + 1];
		char* c = p;
		cf.Read(p,len);
		*(p+len)='\0';
		CString s(Word);
		s.MakeLower();
		_tcslwr(p);
		if(NULL != _tcsstr(p, s))
		{
			delete []p;
			return true;
		}
		else
		{
			delete []p;
			return false;
		}
	}
	CATCH(CFileException, e)
	{
	
		return false;
	}
	END_CATCH
	/*
	size_t i = 0;
    while(c<p+len-1)
	{
		i=0;
		while(i < _tcslen(Word) && ((c + i) <( p+ len - 1)))
		{
			if(*(s+i) != *(c+i))
			{
				c++;
				break;
			}
			i++;
		}
		if(i>=_tcslen(Word) )
		{
			TRACE("%s\n",FileName);
			delete p;
			return TRUE;
		}
	}
    if(i>=_tcslen(Word) )
	{
		TRACE("%s\n",FileName);
		delete p;
		return TRUE;
	}
	else
	{
	    delete p;
		return FALSE;
	}
    */
}