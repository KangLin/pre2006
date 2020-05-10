/*******************************************************************************************************
��Ȩ���� (C) 2006 ���ֹ����ң���������Ȩ����
�ļ�����IncludeFile.cpp
��  �������ͷ�ļ���ʾ�򡣰���������
        1��CIncludeTiShi
		2��CSystemIncludeTiShi
		3��CLocalIncludeTiShi
��  ����1.0.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2006��9��6��
ʱ  �䣺13:04:58
��������Microsoft Visual Studio 8.0 ���� C/C++ 8.0
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
	/*ע��:Ӧ�ó�������ʱ����UNICODEģʽ�£����ػ���������Ĭ��Ϊ_tsetlocale(LC_ALL, _T("C"))��
	��C����ת����Cת�����������ַ���������1-256֮�䣩��
	���CFile��typeText������� mbtowc ʱ����C����ת��������Ҫ�������������typeBinary���򲻴��ڴ����⡣
	TRACEҲ�������������
	Ҫʹ������ϵͳ���õ��������ã�
	//��������Ϊϵͳ���õ�����
	_tsetlocale(LC_ALL, _T(""));
	TRACE(_T("%s\n"), _tsetlocale(LC_ALL, NULL));
	/*����취��
	1��CFile����typeText���ͣ�����typeBinary���͡�
	2����������Ϊ����ϵͳĬ�ϵ������ã�_tsetlocale(LC_ALL, _T(""));
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
��������OnShowTip
��  ����������ʾ��Ŀ������ʾ�����ʾ���ݡ�
��  ����
        UINT nIndex        ����ǰѡ�����Ŀ��
		LPCTSTR lpcszText  ����ǰѡ����Ŀ�����ݡ�
		LPTSTR * lpszInText�����ظ���Ŀ������ʾ��Ҫ��ʾ�����ݡ��������Ŀռ��ڸ������ͷš�
							 ShowTip �Ḻ���ͷ��ڴ�ġ�
����ֵ������Ϊ int ���ɹ�����0�����򷵻ط��㡣
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��9��8�� 11:19:43
*******************************************************************************************************/
int CIncludeTiShi::OnShowTip(UINT nIndex, LPCTSTR lpcszText, /*[out]*/ LPTSTR * lpszInText)
{
	ASSERT(nIndex >= 0 && nIndex < m_arrFile.GetSize());
	if(!((nIndex >= 0 && nIndex < m_arrFile.GetSize())))
	{
		return 1;
	} // ���� if(!((nIndex >= 0 && nIndex < m_arrFile.GetSize())))

	LPTSTR pszRet = NULL;
	CString szTemp = m_arrFile [nIndex];
	int nLen = 0;
	nLen = szTemp.GetLength() + sizeof(TCHAR);
	pszRet = new TCHAR[nLen]; //�˴��ռ��ɵ������ͷ�
	if(NULL == pszRet)
	{
		return 2;
	} // ���� if(NULL == pszRet)
	_tcscpy(pszRet, szTemp);
	*lpszInText = pszRet;
	return 0;
}

/*******************************************************************************************************
��������WriteSelection
��  ����������ͷ�ļ���
        1����ѡ�е���д�� TextSelection �С�
		2��������ʾ��
��  ����
        DWORD dwFlags����־��
����ֵ������Ϊ int ���ɹ����� 0�����򷵻ط��㡣
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��10��20�� 14:29:44
*******************************************************************************************************/
int CIncludeTiShi::WriteSelection(DWORD dwFlags)
{
	if(!m_bShow) //�����ʾ��û����ʾ�����˳�
	{
		return - 1;
	}// ���� if(!m_bShow)

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
		} // ���� if(dwFlags & ONENTER)
		return 1;
	}// ���� if(LB_ERR == nIndex)

	if(!(dwFlags & ONENTER)) //������ʾ����˫��
	{
		CString szTmp;
		szTmp = GetString();
		if(m_szInput.GetLength() > 0)
		{
			if(_tcsnicmp(szTmp, m_szInput, m_szInput.GetLength()))
			{
				// �����ַ�������ʾ�ַ�����ͬ�����û�������
				Show(FALSE);
				return 2;
			} // ���� if(_tcsnicmp(szTmp, m_szInput, m_szInput.GetLength()))
		}
		else
		{
			Show(FALSE);
			return 2;
		}
	}// ���� if(!(dwFlags & ONENTER))

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

		// ת�������·��
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
			} // ���� if(PathRelativePathTo(szPath, szDocPath, FILE_ATTRIBUTE_NORMAL, m_arrFile[nIndex], FILE_ATTRIBUTE_NORMAL))
		}
		else
		{
			szText += m_arrFile[nIndex];
		}// ���� if(m_bRelativePath)

		szText += _T("\"");
	} // ���� if(dwFlags & LOCAL)

	IfFailGoCheck(GetTextSelect(&pSel), pSel);
	IfFailGo(pSel->StartOfLine(EnvDTE::vsStartOfLineOptionsFirstText, VARIANT_TRUE));
	//IfFailGo(pSel->put_Text(CComBSTR(szText)));//���������½���˺���
	IfFailGo(pSel->Insert(CComBSTR(szText), EnvDTE::vsInsertFlagsCollapseToEnd));

	if(dwFlags & ONENTER)
	{
		Show(m_hParent, FALSE); 
	}
	else
	{
		Show(FALSE);
	}// ���� if(dwFlags & ONENTER)

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
	}// ���� if(dwFlags & ONENTER)

	return 1;
}

/*******************************************************************************************************
��������SetRelativePath
��  �����Ƿ�ת��ͷ�ļ�Ϊ���·����־��
��  ����
        BOOL bRelative��TRUE��ת�������·����Ĭ�ϣ���FALSE����ת����
����ֵ������Ϊ BOOL ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��10��20�� 19:01:23
*******************************************************************************************************/
BOOL CIncludeTiShi::SetRelativePath(BOOL bRelative)
{
	BOOL old = m_bRelativePath;
	m_bRelativePath = bRelative;
	return old;
}

/*******************************************************************************************************
��������SetDTE
��  ��������DTE
��  ����
        EnvDTE::_DTE pDTE��
����ֵ������Ϊ BOOL ��
��  ����1.0.0.1
��  �ߣ���  ��
*******************************************************************************************************/
BOOL CIncludeTiShi::SetDTE(EnvDTE::_DTE* pDTE)
{
	if(pDTE == NULL)
	{
		return FALSE;
	}// ���� if(pDTE == NULL)
	m_pDTE = pDTE;
	return TRUE;
}

/*******************************************************************************************************
��������SetIncludeFileDatabase
��  �������ô洢ͷ�ļ����ݵ��ļ�
ע  �⣺�˺��������ڹ��캯���е��á�
��  ����
        LPCTSTR pszFile���ļ�����ȫ·����
����ֵ������Ϊ BOOL ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��9��6�� 16:16:09
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
	} // ���� if(pszFile == NULL || _tcslen(pszFile) == 0)
	
	return TRUE;
}

/*******************************************************************************************************
��������Clean
��  ��������������ʾ�������
��  ������
����ֵ������Ϊ BOOL ���ɹ�����TRUE�����򷵻�FALSE��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��10��25�� 9:02:15
*******************************************************************************************************/
BOOL CIncludeTiShi::Clean()
{
	FreeArray();
	ResetContent();
	return TRUE;
}

/*******************************************************************************************************
��������FreeArray
��  ����������� m_arrFile
��  ������
����ֵ������Ϊ int ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��9��8�� 14:07:06
*******************************************************************************************************/
int CIncludeTiShi::FreeArray()
{
	for(int i = 0; i < m_arrFile.GetSize(); i++)
	{
		delete []m_arrFile [i];
	}// ���� for(int i = 0; i < m_arrFile.GetSize(); i++)
	m_arrFile.RemoveAll();
	return 0;
}

/*******************************************************************************************************
��������Load
��  �������ļ��м���ͷ�ļ���������ļ������ڣ����׳��쳣��
��  ������
����ֵ������Ϊ int ���ɹ�����0�����򷵻ط��㡣
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��9��8�� 14:40:38
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
			//ȥ�����Ļ��з�
			szTmp = szTmp.Left(szTmp.GetLength() - 1);
			//���������ڴ��� FreeArrary ���ͷš�
			pszTmp = new TCHAR[szTmp.GetLength() + sizeof(TCHAR)];
			if(pszTmp)
			{
				_tcscpy(pszTmp, szTmp);
				//���ص��ڴ棨���飩��
				m_arrFile.Add(pszTmp);
			}
			else
			{
				return 1;
			}// ���� if(pszTmp)
			//���뵽��ʾ����
			fe.SetFile(szTmp);
			AddString(fe.GetFileName());
		} // ���� (m_szIncludeFileDatabase, CFile::modeReadWrite)
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
			}// ���� if(GetIncludeFile())
		}
		else
		{
			TRACE(_T("%s(%d):����ţ�%d"), __FILE__, __LINE__, e->m_cause);
			return 3;
		} // ���� if(e->m_cause = CFileException::fileNotFound)
	}
	END_CATCH

	return 0;
}

/*******************************************************************************************************
��������SaveDatabase
��  �����������е�ͷ�ļ������浽�ļ����ݿ��У������ص���ʾ���С�
��  ����
        BOOL bAddListCtr���Ƿ���ص���ʾ���С�TRUE������(Ĭ��)��FALSE�������ء�
����ֵ������Ϊ int ���ɹ�����0�����򷵻ط��㡣
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��10��23�� 19:06:55
*******************************************************************************************************/
int CIncludeTiShi::SaveDatabase(BOOL bAddListCtr)
{
	if(bAddListCtr)
	{
		ResetContent();
	} // ���� if(bAddListCtr)
	TRY
	{
		/*ע��:Ӧ�ó�������ʱ����UNICODEģʽ�£����ػ���������Ĭ��Ϊ_tsetlocale(LC_ALL, _T("C"))��
		��C����ת����Cת�����������ַ���������1-256֮�䣩��
		���CFile��typeText������� mbtowc ʱ����C����ת������ASCII��ʽ���棩������Ҫ��������
		�����typeBinary���򲻴��ڴ����⡣

		Ҫʹ������ϵͳ���õ��������ã�*/
		/*/ / ��������Ϊϵͳ���õ�����
		_tsetlocale(LC_ALL, _T(""));
		TRACE(_T("%s\n"), _tsetlocale(LC_ALL, NULL));

		/*����취��
		1��CFile����typeText���ͣ�����typeBinary���͡�������������� UNICODE �롣
		2����������Ϊ����ϵͳĬ�ϵ������ã�_tsetlocale(LC_ALL, _T(""));
		*/
		CFileEx fe;
		CString szTmp;
		CStdioFile f(m_szIncludeFileDatabase, CFile::modeCreate | CFile::modeReadWrite); // | CFile::typeBinary);
		//���浽�ļ���
		for(int i = 0; i < m_arrFile.GetSize(); i++)
		{
			TRACE(_T("%s\n"), m_arrFile [i]);
			szTmp = m_arrFile[i];

			//���浽�ļ�
			f.WriteString(szTmp + _T("\r\n"));

			if(bAddListCtr)
			{
				//���뵽��ʾ����
				fe.SetFile(szTmp);
				AddString(fe.GetFileName());
			}// ���� if(bAddListCtr)
		}// ���� (LC_ALL, _T(""))
		f.Close();
	}
	CATCH(CFileException, e)
	{
		TRACE(_T("%s(%d):����ţ�%d"), __FILE__, __LINE__, e->m_cause);
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
��������BinInsertArray
��  �������۰���뷨���뵽�����С�
��  ����
        LPCTSTR pszFile��Ҫ������ļ�����
����ֵ������Ϊ INT ���ɹ�����0�����򷵻ط��㡣
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��9��8�� 11:37:37
*******************************************************************************************************/
INT CIncludeTiShi::BinInsertArray(LPCTSTR pszFile)
{
	ASSERT(pszFile);
	if(!pszFile)
	{
		return 1;
	}// ���� if(pszFile)

	CFileEx fe(pszFile);
	CString szInFile = fe.GetFileName();
	CString sztmp;
	int nHight, nLow, nMid, nCmp;

	nLow = nMid = 0;
	nHight = m_arrFile.GetSize() - 1;

	//�۰����
	while(nHight >= nLow)
	{
		nMid = (nLow + nHight) / 2;
		fe.SetFile(m_arrFile [nMid]);
		sztmp = fe.GetFileName();
		nCmp = _tcsicmp(sztmp, szInFile);
		if(0 == nCmp)
		{
			//����Ƿ����ظ�����
			if(!_tcsicmp(m_arrFile[nMid], pszFile))
			{
				return 0;
			}// ���� if(arrFile[nMid] == pszFile)

			break;
		} // ���� if(0 == nCmp)
		if(0 > nCmp)
		{
			nLow = nMid + 1;
			nMid = nLow;
		}
		else
		{
			nHight = nMid - 1;
		} // ���� if(0 > nCmp)
	}// ���� while(nHight >= nLow)

	//�ƶ�
	m_arrFile.Add(NULL);
	for(int i = m_arrFile.GetSize() - 1; i > nMid; i--)
	{
		m_arrFile [i] = m_arrFile [i - 1];
	}// ���� for(int i = m_arrFile.GetSize() - 1; i > nMid; i--)
	LPTSTR pBuf = NULL;
	pBuf = new TCHAR[_tcslen(pszFile) + sizeof(TCHAR)];//���������ڴ��� FreeArrary ���ͷš�
	if(pBuf)
	{
		//����
		_tcscpy(pBuf, pszFile);
		m_arrFile [nMid] = pBuf; 
	}
	else
	{
		return 2;
	} // ���� if(pBuf)
	
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

	//�˴��Ḳ��SetIncludeFileDatabase���õ��ļ���
	//����Ҫ�������ñ������ݵ��ļ�����Ҫ�ڵ�����CreateEx�Ժ��ٵ���SetIncludeFileDatabase��
	CFileEx fe;
	CString szFile = fe.GetFilePath() + _T("\\IncludeSystemDatabase.txt");
	SetIncludeFileDatabase(szFile);

	return 0;
}

/*******************************************************************************************************
��������OnEnter
��  ������Ӧ����ʾ����˫������¼���
��  ����
        LPCTSTR pszText��
����ֵ������Ϊ int ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��10��20�� 19:10:20
*******************************************************************************************************/
int CSystemIncludeTiShi::OnEnter(LPCTSTR pszText)
{
	return !WriteSelection(SYSTEM | ONENTER);
}

/*******************************************************************************************************
��������GetIncludeFile
��  ������VS�����еõ�Includeͷ�ļ���
��  ������
����ֵ������Ϊ BOOL ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��9��8�� 9:25:03
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
	} // ���� if(_T("") == szIncludeDir)

	LPTSTR pTmp;

	pTmp = NULL;
	pTmp = _tcstok((LPTSTR)(LPCTSTR)szIncludeDir, _T(";"));
	while(pTmp)
	{
		GetFile(pTmp);
		pTmp = _tcstok(NULL, _T(";"));
	} // ���� while(pTmp)

	return TRUE;
}

/*******************************************************************************************************
��������GetVcIncludeFolders
��  �����õ�VC++ͷ�ļ�Ŀ¼
��  ����
        const EnvDTE::_DTE * pDTE��
		const BSTR bstrPlatform  ��ƽ̨
����ֵ������Ϊ CComBSTR ��VC++ͷ�ļ�Ŀ¼����";"Ϊ�ָ�����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��9��6�� 12:32:10
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
	} // ���� if(pDTE != NULL)

	return bstrIncludeFolders;

Error:
	return CComBSTR();
}

/*******************************************************************************************************
��������GetVcIncludeFolders
��  �����õ�VC++ͷ�ļ�Ŀ¼
��  ����
        EnvDTE::_DTE * pDTE ��
		LPCTSTR lpszPlatform��ƽ̨
����ֵ������Ϊ CString ��VC++ͷ�ļ�Ŀ¼����";"Ϊ�ָ�����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��9��6�� 13:05:38
*******************************************************************************************************/
CString CSystemIncludeTiShi::GetVcIncludeFolders(EnvDTE::_DTE * pDTE, LPCTSTR lpszPlatform /*= _T("Win32")*/)
{
	USES_CONVERSION;
	CComBSTR bstrRe;
	bstrRe = GetVcIncludeFolders(pDTE, CComBSTR(lpszPlatform));
	return CString(OLE2T(bstrRe));
}

/*******************************************************************************************************
��������GetFile
��  �������Ҹ���Ŀ¼�µ��ļ������������浽�����С�
��  ����
        LPCTSTR lpcszPath��Ŀ¼
����ֵ������Ϊ INT ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��9��6�� 14:07:34
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
		} // ���� if(e->m_cause = CFileException::fileNotFound)
		CString sztmp = ff.GetFilePath();
		BinInsertArray(sztmp);
	}// ���� while(bFind)

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

	//�˴��Ḳ��SetIncludeFileDatabase���õ��ļ���
	//����Ҫ�������ñ������ݵ��ļ�����Ҫ�ڵ�����CreateEx�Ժ��ٵ���SetIncludeFileDatabase��
	CFileEx fe;
	CString szFile = fe.GetFilePath() + _T("\\IncludeLocalDatabase.txt");
	SetIncludeFileDatabase(szFile);

	return 0;
}

/*******************************************************************************************************
��������OnEnter
��  ������Ӧ����ʾ����˫������¼���
��  ����
        LPCTSTR pszText��
����ֵ������Ϊ int ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��10��20�� 19:12:18
*******************************************************************************************************/
int CLocalIncludeTiShi::OnEnter(LPCTSTR pszText)
{
	return !WriteSelection(LOCAL | ONENTER);
}

/*******************************************************************************************************
��������Load
��  ��������ͷ�ļ�
		����ѱ��������ݿ��ļ��У��ʹ����ݿ��ļ��ж�ȡ�������û�����ݿ��ļ���������õ���
		�޸�:���½���һ���������ʱ���ò���������������ơ�
��  ������
����ֵ������Ϊ int ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��10��31�� 19:54:34
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
		//�޸�:���½���һ���������ʱ���ò���������������ơ�
		TRACE(_T("��ĿΪ�ա�\n"));
	}// ���� if(szFile.IsEmpty())
	
	SetIncludeFileDatabase(szFile);

	return CIncludeTiShi::Load();

Error:
	return nRet;
}

/*******************************************************************************************************
��������GetIncludeFile
��  �����ӽ�������õ�ͷ�ļ�
��  ������
����ֵ������Ϊ BOOL ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��9��11�� 10:35:09
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
		TRACE(_T("���̣�%s\n"), bstrName);
#endif
		GetFile(pPrj);
	} // ���� for(long i = 1; i <= lgCount; i++)
	bRet = TRUE;
Error:
	return bRet;
}

/*******************************************************************************************************
��������GetFile
��  �����Ӹ����Ĺ��̵õ�ͷ�ļ�
��  ����
        EnvDTE::Project * pPrj������
����ֵ������Ϊ INT ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��9��11�� 13:00:31
*******************************************************************************************************/
INT CLocalIncludeTiShi::GetFile(EnvDTE::Project * pPrj)
{
	INT nRet = 1;
	HRESULT hr;
	long lgCount;
	CComPtr < EnvDTE::ProjectItems > pProItems;
	CComPtr < EnvDTE::ProjectItem > pProjItem;
	CComBSTR bstrName;

	//����:��鹤���Ƿ���VC����

	IfFailGoCheck(pPrj->get_ProjectItems(&pProItems), pProItems);
	ListProjectItem(pProItems);
	nRet = 0;
Error:
	return nRet;
}

/*******************************************************************************************************
��������ListProjectItem
��  ����ö�ٹ�����Ŀ
��  ����
        EnvDTE::ProjectItems * pProjItems��������Ŀ
����ֵ������Ϊ INT ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��9��11�� 12:59:44
*******************************************************************************************************/
INT CLocalIncludeTiShi::ListProjectItem(EnvDTE::ProjectItems * pProjItems)
{
	ASSERT(pProjItems);
	if(!pProjItems)
	{
		return 1;
	}// ���� if(!pProjItems)

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
		TRACE(_T("������Ŀ��%s\n"), bstrName);
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
			} // ���� if(SUCCEEDED(hr) && lgCount > 0)
		}
		else
		{
			IsIncludeFile(pProItem);
		}// ���� if(SUCCEEDED(hr) && pProItems)
	}// ���� for(long i = 1; i <= lgCount; i++)

	nRet = 0;
Error:
	return nRet;
}

/*******************************************************************************************************
��������IsIncludeFile
��  �����ж��Ƿ���ͷ�ļ�
��  ����
        EnvDTE::ProjectItem * pProjItem����Ŀ
����ֵ������Ϊ BOOL ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��9��11�� 12:57:57
*******************************************************************************************************/
BOOL CLocalIncludeTiShi::IsIncludeFile(EnvDTE::ProjectItem * pProjItem)
{
	HRESULT hr;
	CComBSTR bstrFileName;
	CString szTmp, szExt;

	if(FAILED(pProjItem->get_FileNames(1, &bstrFileName)))
	{
		return FALSE;
	} // ���� if(FAILED(pProjItem->get_FileNames(1, &bstrFileName)))
	szTmp = bstrFileName;

	CFileEx fe(szTmp);
	szExt = fe.GetFileExt().MakeUpper();
	if(szExt == _T(".H"))
	{
		BinInsertArray(szTmp);
	} // ���� if(szExt == _T("H"))

	return TRUE;
}