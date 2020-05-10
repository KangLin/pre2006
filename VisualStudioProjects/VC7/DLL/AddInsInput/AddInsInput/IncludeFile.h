/*******************************************************************************************************
��Ȩ���� (C) 2006 ���ֹ����ң���������Ȩ����
�ļ�����IncludeFile.h
��  �������ͷ�ļ���ʾ�򡣰���������
        1��CIncludeTiShi
		2��CSystemIncludeTiShi
		3��CLocalIncludeTiShi

						CTiShi
						  |
						  |
					CIncludeTiShi
						  |
						  |
				 --------------------
				 |                  |
				 |                  |
		 CSystemIncludeTiShi   CLocalIncludeTiShi

��  ����
		1����������CSystemIncludeTiShi t;
		2���������ڣ�t.CreateEx();
		3�����ñ���ϵͳͷ�ļ����ݵ��ļ�����SetIncludeFileDatabase(szFile);
		   ����������ļ�������Ĭ��Ϊ��ǰģ��Ŀ¼�µ� SystemIncludeDatabase.txt
		   ע�⣺����Ĭ����������OnCreate�����õģ������ⲽһ��Ҫ��CreateEx��
	    4��װ��ͷ�ļ����ڴ����ʾ��Load();
		5����Ҫ��ʾ�ĵط����� Show(TRUE)
		6���ƶ���ʾ�� Move()
		7����ɺ�д�뵽 Selection �в�������ʾ�� WriteSelection()
��  ����1.0.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2006��10��19��
ʱ  �䣺15:56:55
��������Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*******************************************************************************************************/
#pragma once

#include "..\..\..\TiShi\TiShi.h"
#include "..\..\..\..\..\Programe\VC\File\FileEx.h"
#include <locale.h>
#include <afxtempl.h>
#include "..\..\..\TiShi\TiShi.h"

using namespace EnvDTE;
using namespace EnvDTE80;
using namespace VCProjectEngineLibrary;


/*******************************************************************************************************
��������CIncludeTiShi
��  ����ͷ�ļ���ʾ��Ļ��ࡣ
        1��������۰���뵽�����С�
		2�������ļ��е����ݵ������С�
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��9��8�� 15:44:06
*******************************************************************************************************/
class CIncludeTiShi : public CTiShi
{
	DECLARE_DYNAMIC(CIncludeTiShi)

public:
	enum
	{
		SYSTEM = 1,  //�õ�ϵͳͷ�ļ�����
		LOCAL = 2,   //�õ�����ͷ�ļ�����
		ONENTER = 4  //����ʾ����˫������¼�
	};
	CIncludeTiShi(void);
	~CIncludeTiShi(void);

	// ���ñ������ݵ��ļ���
	BOOL SetIncludeFileDatabase(LPCTSTR pszFile = NULL);
	virtual int Load();
	BOOL SetDTE(EnvDTE::_DTE * pDTE);
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
	int WriteSelection(DWORD dwFlags);
	// ͷ�ļ��Ƿ������·��
	BOOL SetRelativePath(BOOL bRelative = TRUE);
	// �������е�ͷ�ļ����浽�ļ����ݿ��У����ӵ���ʾ�����
	int SaveDatabase(BOOL bAddListCtr = TRUE);
	BOOL Clean();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	CString m_szIncludeFileDatabase;      // ���ڴ洢ͷ�ļ����ݵ��ļ���
	CArray < LPTSTR, LPTSTR > m_arrFile;  // ��ȡͷ�ļ���
	BOOL m_bRelativePath;

	virtual int OnShowTip(UINT nIndex, LPCTSTR lpcszText, LPTSTR * lpszInText);

	// �ͷ����� m_arrFile
	int FreeArray();
	// ������
	INT BinInsertArray(LPCTSTR pszFile);

	// �õ�ͷ�ļ�
	virtual BOOL GetIncludeFile();

public:
	CComPtr < EnvDTE::_DTE > m_pDTE;
};

/*******************************************************************************************************
��  ����CSystemIncludeTiShi
��  ����VC++��ϵͳͷ�ļ���ʾ��
��  ����
		1����������CSystemIncludeTiShi t;
		2���������ڣ�t.CreateEx();
		3�����ñ���ϵͳͷ�ļ����ݵ��ļ�����SetIncludeFileDatabase(szFile);
		   ����������ļ�������Ĭ��Ϊ��ǰģ��Ŀ¼�µ� SystemIncludeDatabase.txt
		   ע�⣺����Ĭ����������OnCreate�����õģ������ⲽһ��Ҫ��CreateEx��
	    4��װ��ͷ�ļ����ڴ����ʾ��Load();
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��9��8�� 15:37:51
*******************************************************************************************************/
class CSystemIncludeTiShi : public CIncludeTiShi
{
	DECLARE_DYNAMIC(CSystemIncludeTiShi)

public:
	CSystemIncludeTiShi();
	virtual ~CSystemIncludeTiShi();

protected:
	virtual BOOL GetIncludeFile();

	// Enter ���¼�����Ӧ�б�ؼ���ȷ����Ϣ��
	virtual int OnEnter(LPCTSTR pszText);

private:	
	CComBSTR GetVcIncludeFolders(EnvDTE::_DTE * pDTE, BSTR bstrPlatform /*= _T("Win32")*/);
	CString GetVcIncludeFolders(EnvDTE::_DTE * pDTE, LPCTSTR lpszPlatform /*= _T("Win32")*/);
	INT GetFile(LPCTSTR lpcszPath);

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

/*******************************************************************************************************
��  ����CLocalIncludeTiShi
��  ����VC++��ϵͳͷ�ļ���ʾ��
��  ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��9��8�� 16:46:51
*******************************************************************************************************/
class CLocalIncludeTiShi : public CIncludeTiShi
{
	DECLARE_DYNAMIC(CLocalIncludeTiShi)

public:
	CLocalIncludeTiShi();
	virtual ~CLocalIncludeTiShi();

	virtual int Load();
	INT GetFile(EnvDTE::Project * pPro);
	BOOL IsIncludeFile(EnvDTE::ProjectItem * pProjItem);

protected:
	virtual BOOL GetIncludeFile();

	// Enter ���¼�����Ӧ�б�ؼ���ȷ����Ϣ��
	virtual int OnEnter(LPCTSTR pszText);

	INT ListProjectItem(EnvDTE::ProjectItems * pProjItems);
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};