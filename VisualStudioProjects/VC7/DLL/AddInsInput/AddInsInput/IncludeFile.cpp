/*******************************************************************************************************
版权所有 (C) 2006 康林工作室；保留所有权利。
文件名：IncludeFile.cpp
描  述：完成头文件提示框。包括三个类
        1、CIncludeTiShi
		2、CSystemIncludeTiShi
		3、CLocalIncludeTiShi
版  本：1.0.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2006年9月6日
时  间：13:04:58
编译器：Microsoft Visual Studio 8.0 —— C/C++ 8.0
*******************************************************************************************************/
#include "stdafx.h"
#include "IncludeFile.h"
#include ".\ComFun\ComFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CIncludeTiShi
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CIncludeTiShi, CTiShi)

CIncludeTiShi::CIncludeTiShi(void)
{
	/*注意:应用程序启动时，在UNICODE模式下，本地化区域设置默认为_tsetlocale(LC_ALL, _T("C"))，
	按C进行转换（C转换假设所有字符类型是在1-256之间）。
	如果CFile用typeText，则调用 mbtowc 时会用C进行转换。所以要设置区域。如果用typeBinary，则不存在此问题。
	TRACE也存在这种情况。
	要使程序用系统设置的区域，则用：
	//设置区域为系统设置的区域
	_tsetlocale(LC_ALL, _T(""));
	TRACE(_T("%s\n"), _tsetlocale(LC_ALL, NULL));
	/*解决办法：
	1、CFile不用typeText类型，而用typeBinary类型。
	2、设置区域为操作系统默认的区域。用：_tsetlocale(LC_ALL, _T(""));
	*/
	_tsetlocale(LC_ALL, _T(""));
	TRACE(_T("%s\n"), _tsetlocale(LC_ALL, NULL));
	ShowCopyRight();
	m_bRelativePath = TRUE;
}

CIncludeTiShi::~CIncludeTiShi(void)
{
	Clean();
}

BEGIN_MESSAGE_MAP(CIncludeTiShi, CTiShi)
END_MESSAGE_MAP()

// CIncludeTiShi message handlers

/*******************************************************************************************************
函数名：OnShowTip
描  述：重载显示条目帮助提示框的显示内容。
参  数：
        UINT nIndex        ：当前选择的条目。
		LPCTSTR lpcszText  ：当前选择条目的内容。
		LPTSTR * lpszInText：返回给条目帮助提示框要显示的内容。这里分配的空间在父类中释放。
							 ShowTip 会负责释放内存的。
返回值：类型为 int 。成功返回0，否则返回非零。
版  本：1.0.0.1
作  者：康  林
时  间：2006年9月8日 11:19:43
*******************************************************************************************************/
int CIncludeTiShi::OnShowTip(UINT nIndex, LPCTSTR lpcszText, /*[out]*/ LPTSTR * lpszInText)
{
	ASSERT(nIndex >= 0 && nIndex < m_arrFile.GetSize());
	if(!((nIndex >= 0 && nIndex < m_arrFile.GetSize())))
	{
		return 1;
	} // 结束 if(!((nIndex >= 0 && nIndex < m_arrFile.GetSize())))

	LPTSTR pszRet = NULL;
	CString szTemp = m_arrFile [nIndex];
	int nLen = 0;
	nLen = szTemp.GetLength() + sizeof(TCHAR);
	pszRet = new TCHAR[nLen]; //此处空间由调用者释放
	if(NULL == pszRet)
	{
		return 2;
	} // 结束 if(NULL == pszRet)
	_tcscpy(pszRet, szTemp);
	*lpszInText = pszRet;
	return 0;
}

/*******************************************************************************************************
函数名：WriteSelection
描  述：完成添加头文件。
        1、把选中的项写到 TextSelection 中。
		2、隐藏提示框。
参  数：
        DWORD dwFlags：标志。
返回值：类型为 int 。成功返回 0，否则返回非零。
版  本：1.0.0.1
作  者：康  林
时  间：2006年10月20日 14:29:44
*******************************************************************************************************/
int CIncludeTiShi::WriteSelection(DWORD dwFlags)
{
	if(!m_bShow) //如果提示框没有显示，则退出
	{
		return - 1;
	}// 结束 if(!m_bShow)

	HRESULT hr;
	CComPtr < EnvDTE::TextSelection > pSel;
	int nIndex = GetCurSel();
	if(LB_ERR == nIndex)
	{
		if(dwFlags & ONENTER)
		{
			Show(m_hParent, FALSE); 
		}
		else
		{
			Show(FALSE);
		} // 结束 if(dwFlags & ONENTER)
		return 1;
	}// 结束 if(LB_ERR == nIndex)

	if(!(dwFlags & ONENTER)) //非在提示框上双击
	{
		CString szTmp;
		szTmp = GetString();
		if(m_szInput.GetLength() > 0)
		{
			if(_tcsnicmp(szTmp, m_szInput, m_szInput.GetLength()))
			{
				// 输入字符串与显示字符串不同，按用户的输入
				Show(FALSE);
				return 2;
			} // 结束 if(_tcsnicmp(szTmp, m_szInput, m_szInput.GetLength()))
		}
		else
		{
			Show(FALSE);
			return 2;
		}
	}// 结束 if(!(dwFlags & ONENTER))

	CString szText(_T("#include "));
	if(dwFlags & SYSTEM)
	{
		CString szTmp;
		szText += _T("<");
		GetText(nIndex, szTmp);
		szText += szTmp;
		szText += _T(">");
	}
	if(dwFlags & LOCAL)
	{
		szText += _T("\"");

		// 转换成相对路径
		if(m_bRelativePath)
		{
			TCHAR szPath[MAX_PATH];
			CComBSTR bstrDocName;
			CString szDocPath;
			CComPtr < EnvDTE::Document > pDoc;

			IfFailGoCheck(GetDocument(&pDoc), pDoc);
			IfFailGo(pDoc->get_FullName(&bstrDocName));
			szDocPath = bstrDocName;

			if(PathRelativePathTo(szPath, szDocPath, FILE_ATTRIBUTE_NORMAL, m_arrFile[nIndex], FILE_ATTRIBUTE_NORMAL))
			{
				szText += szPath;
			}
			else
			{
				szText += m_arrFile[nIndex];
			} // 结束 if(PathRelativePathTo(szPath, szDocPath, FILE_ATTRIBUTE_NORMAL, m_arrFile[nIndex], FILE_ATTRIBUTE_NORMAL))
		}
		else
		{
			szText += m_arrFile[nIndex];
		}// 结束 if(m_bRelativePath)

		szText += _T("\"");
	} // 结束 if(dwFlags & LOCAL)

	IfFailGoCheck(GetTextSelect(&pSel), pSel);
	IfFailGo(pSel->StartOfLine(EnvDTE::vsStartOfLineOptionsFirstText, VARIANT_TRUE));
	//IfFailGo(pSel->put_Text(CComBSTR(szText)));//会引起重新进入此函数
	IfFailGo(pSel->Insert(CComBSTR(szText), EnvDTE::vsInsertFlagsCollapseToEnd));

	if(dwFlags & ONENTER)
	{
		Show(m_hParent, FALSE); 
	}
	else
	{
		Show(FALSE);
	}// 结束 if(dwFlags & ONENTER)

	return 0;

Error:
	ASSERT(0);

	if(dwFlags & ONENTER)
	{
		Show(m_hParent, FALSE); 
	}
	else
	{
		Show(FALSE);
	}// 结束 if(dwFlags & ONENTER)

	return 1;
}

/*******************************************************************************************************
函数名：SetRelativePath
描  述：是否转换头文件为相对路径标志。
参  数：
        BOOL bRelative：TRUE，转换成相对路径（默认）；FALSE，不转换。
返回值：类型为 BOOL 。
版  本：1.0.0.1
作  者：康  林
时  间：2006年10月20日 19:01:23
*******************************************************************************************************/
BOOL CIncludeTiShi::SetRelativePath(BOOL bRelative)
{
	BOOL old = m_bRelativePath;
	m_bRelativePath = bRelative;
	return old;
}

/*******************************************************************************************************
函数名：SetDTE
描  述：设置DTE
参  数：
        EnvDTE::_DTE pDTE：
返回值：类型为 BOOL 。
版  本：1.0.0.1
作  者：康  林
*******************************************************************************************************/
BOOL CIncludeTiShi::SetDTE(EnvDTE::_DTE* pDTE)
{
	if(pDTE == NULL)
	{
		return FALSE;
	}// 结束 if(pDTE == NULL)
	m_pDTE = pDTE;
	return TRUE;
}

/*******************************************************************************************************
函数名：SetIncludeFileDatabase
描  述：设置存储头文件数据的文件
注  意：此函数不能在构造函数中调用。
参  数：
        LPCTSTR pszFile：文件名。全路径。
返回值：类型为 BOOL 。
版  本：1.0.0.1
作  者：康  林
时  间：2006年9月6日 16:16:09
*******************************************************************************************************/
BOOL CIncludeTiShi::SetIncludeFileDatabase(LPCTSTR pszFile)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(pszFile == NULL || _tcslen(pszFile) == 0)
	{
		CFileEx fe;
		m_szIncludeFileDatabase = fe.GetFilePath() + _T("\\IncludeDatabase.txt");
	}
	else
	{
		m_szIncludeFileDatabase = pszFile;
	} // 结束 if(pszFile == NULL || _tcslen(pszFile) == 0)
	
	return TRUE;
}

/*******************************************************************************************************
函数名：Clean
描  述：清除数组和提示框的内容
参  数：无
返回值：类型为 BOOL 。成功返回TRUE，否则返回FALSE。
版  本：1.0.0.1
作  者：康  林
时  间：2006年10月25日 9:02:15
*******************************************************************************************************/
BOOL CIncludeTiShi::Clean()
{
	FreeArray();
	ResetContent();
	return TRUE;
}

/*******************************************************************************************************
函数名：FreeArray
描  述：清空数组 m_arrFile
参  数：无
返回值：类型为 int 。
版  本：1.0.0.1
作  者：康  林
时  间：2006年9月8日 14:07:06
*******************************************************************************************************/
int CIncludeTiShi::FreeArray()
{
	for(int i = 0; i < m_arrFile.GetSize(); i++)
	{
		delete []m_arrFile [i];
	}// 结束 for(int i = 0; i < m_arrFile.GetSize(); i++)
	m_arrFile.RemoveAll();
	return 0;
}

/*******************************************************************************************************
函数名：Load
描  述：从文件中加载头文件名。如果文件不存在，则抛出异常。
参  数：无
返回值：类型为 int 。成功返回0，否则返回非零。
版  本：1.0.0.1
作  者：康  林
时  间：2006年9月8日 14:40:38
*******************************************************************************************************/
int CIncludeTiShi::Load()
{
	ResetContent();
	FreeArray();
	TRY
	{
		LPTSTR pszTmp = NULL;
		CString szTmp;
		CFileEx fe;
		CStdioFile stdFile(m_szIncludeFileDatabase, CFile::modeReadWrite);
		while(stdFile.ReadString(szTmp))
		{
			//去掉最后的换行符
			szTmp = szTmp.Left(szTmp.GetLength() - 1);
			//这里分配的内存在 FreeArrary 中释放。
			pszTmp = new TCHAR[szTmp.GetLength() + sizeof(TCHAR)];
			if(pszTmp)
			{
				_tcscpy(pszTmp, szTmp);
				//加载到内存（数组）中
				m_arrFile.Add(pszTmp);
			}
			else
			{
				return 1;
			}// 结束 if(pszTmp)
			//加入到提示框中
			fe.SetFile(szTmp);
			AddString(fe.GetFileName());
		} // 结束 (m_szIncludeFileDatabase, CFile::modeReadWrite)
		stdFile.Close();
	}
	CATCH(CFileException, e)
	{
		if(e->m_cause = CFileException::fileNotFound)
		{
			if(GetIncludeFile())
			{
				return SaveDatabase(TRUE);
			}
			else
			{
				return 2;
			}// 结束 if(GetIncludeFile())
		}
		else
		{
			TRACE(_T("%s(%d):错误号：%d"), __FILE__, __LINE__, e->m_cause);
			return 3;
		} // 结束 if(e->m_cause = CFileException::fileNotFound)
	}
	END_CATCH

	return 0;
}

/*******************************************************************************************************
函数名：SaveDatabase
描  述：把数据中的头文件名保存到文件数据库中，并加载到提示框中。
参  数：
        BOOL bAddListCtr：是否加载到提示框中。TRUE，加载(默认)；FALSE，不加载。
返回值：类型为 int 。成功返回0，否则返回非零。
版  本：1.0.0.1
作  者：康  林
时  间：2006年10月23日 19:06:55
*******************************************************************************************************/
int CIncludeTiShi::SaveDatabase(BOOL bAddListCtr)
{
	if(bAddListCtr)
	{
		ResetContent();
	} // 结束 if(bAddListCtr)
	TRY
	{
		/*注意:应用程序启动时，在UNICODE模式下，本地化区域设置默认为_tsetlocale(LC_ALL, _T("C"))，
		按C进行转换（C转换假设所有字符类型是在1-256之间）。
		如果CFile用typeText，则调用 mbtowc 时会用C进行转换（以ASCII格式保存）。所以要设置区域。
		如果用typeBinary，则不存在此问题。

		要使程序用系统设置的区域，则用：*/
		/*/ / 设置区域为系统设置的区域
		_tsetlocale(LC_ALL, _T(""));
		TRACE(_T("%s\n"), _tsetlocale(LC_ALL, NULL));

		/*解决办法：
		1、CFile不用typeText类型，而用typeBinary类型。但是它保存的是 UNICODE 码。
		2、设置区域为操作系统默认的区域。用：_tsetlocale(LC_ALL, _T(""));
		*/
		CFileEx fe;
		CString szTmp;
		CStdioFile f(m_szIncludeFileDatabase, CFile::modeCreate | CFile::modeReadWrite); // | CFile::typeBinary);
		//保存到文件中
		for(int i = 0; i < m_arrFile.GetSize(); i++)
		{
			TRACE(_T("%s\n"), m_arrFile [i]);
			szTmp = m_arrFile[i];

			//保存到文件
			f.WriteString(szTmp + _T("\r\n"));

			if(bAddListCtr)
			{
				//加入到提示框中
				fe.SetFile(szTmp);
				AddString(fe.GetFileName());
			}// 结束 if(bAddListCtr)
		}// 结束 (LC_ALL, _T(""))
		f.Close();
	}
	CATCH(CFileException, e)
	{
		TRACE(_T("%s(%d):错误号：%d"), __FILE__, __LINE__, e->m_cause);
		return 1;
	}
	END_CATCH

	return 0;
}

BOOL CIncludeTiShi::GetIncludeFile()
{
	return TRUE;
}

/*******************************************************************************************************
函数名：BinInsertArray
描  述：用折半插入法插入到数组中。
参  数：
        LPCTSTR pszFile：要插入的文件名。
返回值：类型为 INT 。成功返回0，否则返回非零。
版  本：1.0.0.1
作  者：康  林
时  间：2006年9月8日 11:37:37
*******************************************************************************************************/
INT CIncludeTiShi::BinInsertArray(LPCTSTR pszFile)
{
	ASSERT(pszFile);
	if(!pszFile)
	{
		return 1;
	}// 结束 if(pszFile)

	CFileEx fe(pszFile);
	CString szInFile = fe.GetFileName();
	CString sztmp;
	int nHight, nLow, nMid, nCmp;

	nLow = nMid = 0;
	nHight = m_arrFile.GetSize() - 1;

	//折半查找
	while(nHight >= nLow)
	{
		nMid = (nLow + nHight) / 2;
		fe.SetFile(m_arrFile [nMid]);
		sztmp = fe.GetFileName();
		nCmp = _tcsicmp(sztmp, szInFile);
		if(0 == nCmp)
		{
			//检查是否有重复的项
			if(!_tcsicmp(m_arrFile[nMid], pszFile))
			{
				return 0;
			}// 结束 if(arrFile[nMid] == pszFile)

			break;
		} // 结束 if(0 == nCmp)
		if(0 > nCmp)
		{
			nLow = nMid + 1;
			nMid = nLow;
		}
		else
		{
			nHight = nMid - 1;
		} // 结束 if(0 > nCmp)
	}// 结束 while(nHight >= nLow)

	//移动
	m_arrFile.Add(NULL);
	for(int i = m_arrFile.GetSize() - 1; i > nMid; i--)
	{
		m_arrFile [i] = m_arrFile [i - 1];
	}// 结束 for(int i = m_arrFile.GetSize() - 1; i > nMid; i--)
	LPTSTR pBuf = NULL;
	pBuf = new TCHAR[_tcslen(pszFile) + sizeof(TCHAR)];//这里分配的内存在 FreeArrary 中释放。
	if(pBuf)
	{
		//插入
		_tcscpy(pBuf, pszFile);
		m_arrFile [nMid] = pBuf; 
	}
	else
	{
		return 2;
	} // 结束 if(pBuf)
	
	return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CSystemIncludeTiShi
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CSystemIncludeTiShi, CTiShi)

CSystemIncludeTiShi::CSystemIncludeTiShi()
{
	TRACE(_T("CSystemIncludeTiShi::CSystemIncludeTiShi\n"));
}

CSystemIncludeTiShi::~CSystemIncludeTiShi()
{
	TRACE(_T("CSystemIncludeTiShi::~CSystemIncludeTiShi\n"));
}


BEGIN_MESSAGE_MAP(CSystemIncludeTiShi, CIncludeTiShi)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CSystemIncludeTiShi message handlers

int CSystemIncludeTiShi::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTiShi::OnCreate(lpCreateStruct) == -1)
		return -1;

	//此处会覆盖SetIncludeFileDatabase设置的文件，
	//所以要用它设置保存数据的文件名，要在调用了CreateEx以后再调用SetIncludeFileDatabase。
	CFileEx fe;
	CString szFile = fe.GetFilePath() + _T("\\IncludeSystemDatabase.txt");
	SetIncludeFileDatabase(szFile);

	return 0;
}

/*******************************************************************************************************
函数名：OnEnter
描  述：响应在提示框上双击鼠标事件。
参  数：
        LPCTSTR pszText：
返回值：类型为 int 。
版  本：1.0.0.1
作  者：康  林
时  间：2006年10月20日 19:10:20
*******************************************************************************************************/
int CSystemIncludeTiShi::OnEnter(LPCTSTR pszText)
{
	return !WriteSelection(SYSTEM | ONENTER);
}

/*******************************************************************************************************
函数名：GetIncludeFile
描  述：从VS配置中得到Include头文件名
参  数：无
返回值：类型为 BOOL 。
版  本：1.0.0.1
作  者：康  林
时  间：2006年9月8日 9:25:03
*******************************************************************************************************/
BOOL CSystemIncludeTiShi::GetIncludeFile()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString szIncludeDir;
	CString szPlatform;
	CString szPath;

	szPlatform = _T("Win32");
	szIncludeDir = GetVcIncludeFolders(m_pDTE, szPlatform);
	if(_T("") == szIncludeDir)
	{
		return FALSE;
	} // 结束 if(_T("") == szIncludeDir)

	LPTSTR pTmp;

	pTmp = NULL;
	pTmp = _tcstok((LPTSTR)(LPCTSTR)szIncludeDir, _T(";"));
	while(pTmp)
	{
		GetFile(pTmp);
		pTmp = _tcstok(NULL, _T(";"));
	} // 结束 while(pTmp)

	return TRUE;
}

/*******************************************************************************************************
函数名：GetVcIncludeFolders
描  述：得到VC++头文件目录
参  数：
        const EnvDTE::_DTE * pDTE：
		const BSTR bstrPlatform  ：平台
返回值：类型为 CComBSTR 。VC++头文件目录。以";"为分隔符。
版  本：1.0.0.1
作  者：康  林
时  间：2006年9月6日 12:32:10
*******************************************************************************************************/
CComBSTR CSystemIncludeTiShi::GetVcIncludeFolders(EnvDTE::_DTE * pDTE, const BSTR bstrPlatform /*= _T("Win32")*/)
{
	CComBSTR bstrIncludeFolders;
	HRESULT hr;

	if(pDTE != NULL)
	{
		CComPtr < EnvDTE::Projects > pProjects;
		CComPtr < EnvDTE::Properties > pProperties;
		CComPtr < EnvDTE::Property > pProperty;
		CComPtr < VCProjectEngineLibrary::VCProjectEngine > pProjectEngine;

		IfFailGoCheck(pDTE->GetObject(CComBSTR(_T("VCProjects")), (IDispatch ** )&pProjects), pProjects);
		IfFailGoCheck(pProjects->get_Properties(&pProperties), pProperties);

		CComVariant v;
		v = _T("VCProjectEngine");
		IfFailGoCheck(pProperties->Item(v, &pProperty), pProperty);
		IfFailGoCheck(pProperty->get_Object((IDispatch ** )&pProjectEngine), pProjectEngine);
		CComPtr < VCProjectEngineLibrary::IVCCollection > pVCPlatforms;
		CComPtr < VCProjectEngineLibrary::VCPlatform > pVCPlatform;

		IfFailGoCheck(pProjectEngine->get_Platforms((IDispatch ** )&pVCPlatforms), pVCPlatforms);
		v = bstrPlatform;
		IfFailGoCheck(pVCPlatforms->Item(v, (IDispatch ** )&pVCPlatform), pVCPlatform);
		CComBSTR bstDir;
		IfFailGoCheck(pVCPlatform->get_IncludeDirectories(&bstDir), bstDir);
		pVCPlatform->Evaluate(bstDir, &bstrIncludeFolders);
	} // 结束 if(pDTE != NULL)

	return bstrIncludeFolders;

Error:
	return CComBSTR();
}

/*******************************************************************************************************
函数名：GetVcIncludeFolders
描  述：得到VC++头文件目录
参  数：
        EnvDTE::_DTE * pDTE ：
		LPCTSTR lpszPlatform：平台
返回值：类型为 CString 。VC++头文件目录。以";"为分隔符。
版  本：1.0.0.1
作  者：康  林
时  间：2006年9月6日 13:05:38
*******************************************************************************************************/
CString CSystemIncludeTiShi::GetVcIncludeFolders(EnvDTE::_DTE * pDTE, LPCTSTR lpszPlatform /*= _T("Win32")*/)
{
	USES_CONVERSION;
	CComBSTR bstrRe;
	bstrRe = GetVcIncludeFolders(pDTE, CComBSTR(lpszPlatform));
	return CString(OLE2T(bstrRe));
}

/*******************************************************************************************************
函数名：GetFile
描  述：查找给定目录下的文件，并把它保存到数组中。
参  数：
        LPCTSTR lpcszPath：目录
返回值：类型为 INT 。
版  本：1.0.0.1
作  者：康  林
时  间：2006年9月6日 14:07:34
*******************************************************************************************************/
INT CSystemIncludeTiShi::GetFile(LPCTSTR lpcszPath)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	BOOL bFind;
	CString szFile(lpcszPath);
	CFileFind ff;

	szFile += _T("\\*.*");
	bFind = ff.FindFile(szFile);
	while(bFind)
	{
		bFind = ff.FindNextFile();
		if(ff.IsDirectory() || ff.IsDots())
		{
			continue;
		} // 结束 if(e->m_cause = CFileException::fileNotFound)
		CString sztmp = ff.GetFilePath();
		BinInsertArray(sztmp);
	}// 结束 while(bFind)

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CLocalIncludeTiShi
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CLocalIncludeTiShi, CTiShi)

CLocalIncludeTiShi::CLocalIncludeTiShi()
{
	TRACE(_T("CLocalIncludeTiShi::CLocalIncludeTiShi\n"));
}

CLocalIncludeTiShi::~CLocalIncludeTiShi()
{
	TRACE(_T("CLocalIncludeTiShi::~CLocalIncludeTiShi\n"));
}

BEGIN_MESSAGE_MAP(CLocalIncludeTiShi, CTiShi)
	ON_WM_CREATE()
END_MESSAGE_MAP()

int CLocalIncludeTiShi::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CIncludeTiShi::OnCreate(lpCreateStruct) == -1)
		return -1;

	//此处会覆盖SetIncludeFileDatabase设置的文件，
	//所以要用它设置保存数据的文件名，要在调用了CreateEx以后再调用SetIncludeFileDatabase。
	CFileEx fe;
	CString szFile = fe.GetFilePath() + _T("\\IncludeLocalDatabase.txt");
	SetIncludeFileDatabase(szFile);

	return 0;
}

/*******************************************************************************************************
函数名：OnEnter
描  述：响应在提示框上双击鼠标事件。
参  数：
        LPCTSTR pszText：
返回值：类型为 int 。
版  本：1.0.0.1
作  者：康  林
时  间：2006年10月20日 19:12:18
*******************************************************************************************************/
int CLocalIncludeTiShi::OnEnter(LPCTSTR pszText)
{
	return !WriteSelection(LOCAL | ONENTER);
}

/*******************************************************************************************************
函数名：Load
描  述：加载头文件
		如果已保存在数据库文件中，就从数据库文件中读取。如果还没有数据库文件，则遍历得到。
		修改:在新建立一个解决方案时，得不到解决方案的名称。
参  数：无
返回值：类型为 int 。
版  本：1.0.0.1
作  者：康  林
时  间：2006年10月31日 19:54:34
*******************************************************************************************************/
int CLocalIncludeTiShi::Load()
{
	HRESULT hr;
	CString szFile;
	CComBSTR bstrFileName;
	CFileEx fe;
	int nRet = 1;

	CComPtr < EnvDTE::_Solution > pSol;
	IfFailGoCheck(m_pDTE->get_Solution(&pSol), pSol);
	IfFailGo(pSol->get_FullName(&bstrFileName));

	szFile = bstrFileName;
	if(!szFile.IsEmpty())
	{
		fe.SetFile(szFile);
		szFile = fe.GetFilePath() + _T("\\IncludeLocalDatabase.txt");
	}
	else
	{
		//修改:在新建立一个解决方案时，得不到解决方案的名称。
		TRACE(_T("项目为空。\n"));
	}// 结束 if(szFile.IsEmpty())
	
	SetIncludeFileDatabase(szFile);

	return CIncludeTiShi::Load();

Error:
	return nRet;
}

/*******************************************************************************************************
函数名：GetIncludeFile
描  述：从解决方案得到头文件
参  数：无
返回值：类型为 BOOL 。
版  本：1.0.0.1
作  者：康  林
时  间：2006年9月11日 10:35:09
*******************************************************************************************************/
BOOL CLocalIncludeTiShi::GetIncludeFile()
{
	BOOL bRet = FALSE;
	HRESULT hr;
	CComPtr < EnvDTE::_Solution > pSol;
	CComPtr < EnvDTE::Projects > pPrjs;

	CComPtr < EnvDTE::ProjectItem > pPrjItem;
	CComPtr < EnvDTE::ProjectItems > pPrjItems;
	CComBSTR bstrName;

	IfFailGoCheck(m_pDTE->get_Solution(&pSol), pSol);
	IfFailGoCheck(pSol->get_Projects(&pPrjs), pPrjs);
	long lgCount;
	pPrjs->get_Count(&lgCount);
	for(long i = 1; i <= lgCount; i++)
	{
		CComPtr < EnvDTE::Project > pPrj;
		pPrjs->Item(CComVariant(i), &pPrj);
#ifdef _DEBUG
		pPrj->get_Name(&bstrName);
		TRACE(_T("工程：%s\n"), bstrName);
#endif
		GetFile(pPrj);
	} // 结束 for(long i = 1; i <= lgCount; i++)
	bRet = TRUE;
Error:
	return bRet;
}

/*******************************************************************************************************
函数名：GetFile
描  述：从给定的工程得到头文件
参  数：
        EnvDTE::Project * pPrj：工程
返回值：类型为 INT 。
版  本：1.0.0.1
作  者：康  林
时  间：2006年9月11日 13:00:31
*******************************************************************************************************/
INT CLocalIncludeTiShi::GetFile(EnvDTE::Project * pPrj)
{
	INT nRet = 1;
	HRESULT hr;
	long lgCount;
	CComPtr < EnvDTE::ProjectItems > pProItems;
	CComPtr < EnvDTE::ProjectItem > pProjItem;
	CComBSTR bstrName;

	//增加:检查工程是否是VC工程

	IfFailGoCheck(pPrj->get_ProjectItems(&pProItems), pProItems);
	ListProjectItem(pProItems);
	nRet = 0;
Error:
	return nRet;
}

/*******************************************************************************************************
函数名：ListProjectItem
描  述：枚举工程项目
参  数：
        EnvDTE::ProjectItems * pProjItems：工程项目
返回值：类型为 INT 。
版  本：1.0.0.1
作  者：康  林
时  间：2006年9月11日 12:59:44
*******************************************************************************************************/
INT CLocalIncludeTiShi::ListProjectItem(EnvDTE::ProjectItems * pProjItems)
{
	ASSERT(pProjItems);
	if(!pProjItems)
	{
		return 1;
	}// 结束 if(!pProjItems)

	HRESULT hr;
	long lgCount;
	INT nRet = 1;

	IfFailGo(pProjItems->get_Count(&lgCount));
	for(long i = 1; i <= lgCount; i++)
	{
		CComPtr < EnvDTE::ProjectItem > pProItem;
		IfFailGoCheck(pProjItems->Item(CComVariant(i), &pProItem), pProItem);
#ifdef _DEBUG
		CComBSTR bstrName;
		pProItem->get_Name(&bstrName);
		TRACE(_T("工程项目：%s\n"), bstrName);
#endif
		CComPtr < EnvDTE::ProjectItems > pProItems;
		hr = pProItem->get_ProjectItems(&pProItems);
		if(SUCCEEDED(hr) && pProItems)
		{
			long lgCount;
			hr = pProItems->get_Count(&lgCount);
			if(SUCCEEDED(hr) && lgCount > 0)
			{
				ListProjectItem(pProItems);
			}
			else
			{
				IsIncludeFile(pProItem);
			} // 结束 if(SUCCEEDED(hr) && lgCount > 0)
		}
		else
		{
			IsIncludeFile(pProItem);
		}// 结束 if(SUCCEEDED(hr) && pProItems)
	}// 结束 for(long i = 1; i <= lgCount; i++)

	nRet = 0;
Error:
	return nRet;
}

/*******************************************************************************************************
函数名：IsIncludeFile
描  述：判断是否是头文件
参  数：
        EnvDTE::ProjectItem * pProjItem：项目
返回值：类型为 BOOL 。
版  本：1.0.0.1
作  者：康  林
时  间：2006年9月11日 12:57:57
*******************************************************************************************************/
BOOL CLocalIncludeTiShi::IsIncludeFile(EnvDTE::ProjectItem * pProjItem)
{
	HRESULT hr;
	CComBSTR bstrFileName;
	CString szTmp, szExt;

	if(FAILED(pProjItem->get_FileNames(1, &bstrFileName)))
	{
		return FALSE;
	} // 结束 if(FAILED(pProjItem->get_FileNames(1, &bstrFileName)))
	szTmp = bstrFileName;

	CFileEx fe(szTmp);
	szExt = fe.GetFileExt().MakeUpper();
	if(szExt == _T(".H"))
	{
		BinInsertArray(szTmp);
	} // 结束 if(szExt == _T("H"))

	return TRUE;
}