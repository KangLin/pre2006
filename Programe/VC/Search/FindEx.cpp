/*******************************************************************************************************
�ļ�����FindEx.cpp
��  �ܣ�implementation of the CFindEx class.
             ||�ⲿ����
            \\//
             \/
		SearchDirectory
		     ||
			\\//
			 \/
    SearchFileAndDirectory
             ||
	���ļ�	 ||  ��Ŀ¼
     ==================
	||                ||
   \\//              \\//
    \/                \/
  OnFile	      OnDirectory
��������Visual C++ 6.0
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-30
ʱ  �䣺12:20:12
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
//��������� ===�ļ���Ŀ¼�Ĳ���=== ���ܵĺ�����
//

/*******************************************************************************************************
��������SearchDirectory
��  �ܣ���ָ����Ŀ¼���в���
��  ����
         LPCSTR szDir��Ҫ���ҵ�Ŀ¼
         BOOL bStop�����ΪTRUE,��ֹͣ���ҡ�Ĭ��ΪFALSE��
����ֵ������ɹ����أ�TRUE�����򣬷���FALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-30
ʱ  �䣺12:20:53
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
		if(bStop)//ֹͣ����
			return false;
		szFileName = szDir;
		szFileName += _T("\\");
		szFileName += wfd.cFileName;
		SearchFileAndDirectory(szFileName, &bStop);
		//��Ŀ¼,�ݹ����
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
��������SearchFileAndDirectory
��  �ܣ��ҵ����ļ���Ŀ¼����SearchDirectory���á�
        ��������Լ������Լ��Ĵ���
��  ����
         LPCSTR szFile�����ҵ���Ŀ¼���ļ�
         BOOL *bpStop�����ΪTRUE,��ֹͣ���ҡ�Ĭ��ΪFALSE��
����ֵ������ɹ����أ�TRUE�����򣬷���FALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-30
ʱ  �䣺12:22:48
*******************************************************************************************************/
BOOL CFindEx::SearchFileAndDirectory(LPCSTR szFile, BOOL *bpStop)
{
	TRACE("%s\n", szFile);
	if(::GetFileAttributes(szFile) & FILE_ATTRIBUTE_DIRECTORY)
	{//Ŀ¼
		OnDirectory(szFile);
	}
	else//�ļ�
	{
		OnFile(szFile);
	}
	return true;
}

/*******************************************************************************************************
��������OnFile
��  �ܣ��ҵ����ļ�����SearchFileAndDirectory���á�
        ��������Լ�����Ҫ����Ĵ��롣
��  ����
         LPCSTR szFile�����ҵ����ļ���
����ֵ������ɹ����أ�TRUE�����򣬷���FALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-30
ʱ  �䣺12:24:19
*******************************************************************************************************/
BOOL CFindEx::OnFile(LPCSTR szFile)
{
	TRACE(_T("�ļ�:%s\n"), szFile);
	CMDIFrameWnd* MWnd = (CMDIFrameWnd*)AfxGetMainWnd();
	CMDIChildWnd* ChildWnd = MWnd->MDIGetActive();
	CSearchView* SearchView =(CSearchView*)ChildWnd->GetActiveView();
	ASSERT(SearchView->IsKindOf(RUNTIME_CLASS(CSearchView)));
	CString str;
    SearchView->m_ctrBtSearch.GetWindowText(str);
	//�����ļ�
    if(!_tcsicmp(str, _T("�����ļ�(&S)")))
	{
		if(!_tcsicmp(GetFileName(szFile), SearchView->m_szFileName))
			SearchView->m_lstFile.AddString(szFile);
	}
	//�����ı�
	if(!_tcsicmp(str, _T("��������(&T)")))
	{
		if(FindWordInFile(szFile, SearchView->m_szFileName))
			SearchView->m_lstFile.AddString(szFile);
	}
	return true;
}

/*******************************************************************************************************
��������OnDirectory
��  �ܣ����ҵ���Ŀ¼����SearchFileAndDirectory���á�
        ��������Լ�����Ҫ����Ĵ��롣
��  ����
         LPCSTR szDir�����ҵ���Ŀ¼
����ֵ������ɹ����أ�TRUE�����򣬷���FALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-30
ʱ  �䣺12:26:06
*******************************************************************************************************/
BOOL CFindEx::OnDirectory(LPCSTR szDir)
{
	TRACE(_T("Ŀ¼:%s\n"), szDir);
	return true;
}

//
//��������� ===�ļ���Ŀ¼�Ĳ���=== ���ܵĺ�����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/*******************************************************************************************************
��������GetFileName
��  �ܣ��õ�ָ���ļ��е��ļ�����
��  ����
         LPCSTR szFileName��ָ�����ļ���������·������
����ֵ��ָ���ļ��е��ļ�����������·������
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-30
ʱ  �䣺12:26:38
*******************************************************************************************************/
CString CFindEx::GetFileName(LPCSTR szFileName)
{
	CString szFile;
	szFile = szFileName;
	szFile = szFile.Right(szFile.GetLength() - szFile.ReverseFind('\\') -1);
	return szFile;
}

/*******************************************************************************************************
��������FindWordInFile
��  �ܣ����ļ����Ҳ���ָ�����ı�
��  ����
         LPCSTR FileName���ļ�
         LPCSTR Word��Ҫ���ҵ��ı�
����ֵ������ҵ�����TRUE,���򷵻�FALSE.
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-30
ʱ  �䣺12:57:54
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