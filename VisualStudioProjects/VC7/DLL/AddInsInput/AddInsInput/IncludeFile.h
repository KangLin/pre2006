/*******************************************************************************************************
版权所有 (C) 2006 康林工作室；保留所有权利。
文件名：IncludeFile.h
描  述：完成头文件提示框。包括三个类
        1、CIncludeTiShi
		2、CSystemIncludeTiShi
		3、CLocalIncludeTiShi

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

用  法：
		1、建立对象：CSystemIncludeTiShi t;
		2、建立窗口：t.CreateEx();
		3、设置保存系统头文件数据的文件名：SetIncludeFileDatabase(szFile);
		   如果不设置文件名，则默认为当前模块目录下的 SystemIncludeDatabase.txt
		   注意：由于默认设置是在OnCreate中设置的，所以这步一定要在CreateEx后。
	    4、装载头文件到内存和提示框：Load();
		5、在要显示的地方调用 Show(TRUE)
		6、移动提示框 Move()
		7、完成后写入到 Selection 中并隐藏提示框 WriteSelection()
版  本：1.0.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2006年10月19日
时  间：15:56:55
编译器：Microsoft Visual Studio 8.0 —— C/C++ 8.0
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
函数名：CIncludeTiShi
描  述：头文件提示框的基类。
        1、完成了折半插入到数组中。
		2、加载文件中的数据到数组中。
版  本：1.0.0.1
作  者：康  林
时  间：2006年9月8日 15:44:06
*******************************************************************************************************/
class CIncludeTiShi : public CTiShi
{
	DECLARE_DYNAMIC(CIncludeTiShi)

public:
	enum
	{
		SYSTEM = 1,  //得到系统头文件调用
		LOCAL = 2,   //得到本地头文件调用
		ONENTER = 4  //在提示框上双击鼠标事件
	};
	CIncludeTiShi(void);
	~CIncludeTiShi(void);

	// 设置保存数据的文件名
	BOOL SetIncludeFileDatabase(LPCTSTR pszFile = NULL);
	virtual int Load();
	BOOL SetDTE(EnvDTE::_DTE * pDTE);
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
	int WriteSelection(DWORD dwFlags);
	// 头文件是否用相对路径
	BOOL SetRelativePath(BOOL bRelative = TRUE);
	// 把数组中的头文件保存到文件数据库中，并加到提示框架中
	int SaveDatabase(BOOL bAddListCtr = TRUE);
	BOOL Clean();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	CString m_szIncludeFileDatabase;      // 用于存储头文件数据的文件名
	CArray < LPTSTR, LPTSTR > m_arrFile;  // 存取头文件名
	BOOL m_bRelativePath;

	virtual int OnShowTip(UINT nIndex, LPCTSTR lpcszText, LPTSTR * lpszInText);

	// 释放数组 m_arrFile
	int FreeArray();
	// 拆半插入
	INT BinInsertArray(LPCTSTR pszFile);

	// 得到头文件
	virtual BOOL GetIncludeFile();

public:
	CComPtr < EnvDTE::_DTE > m_pDTE;
};

/*******************************************************************************************************
类  名：CSystemIncludeTiShi
描  述：VC++的系统头文件提示框。
用  法：
		1、建立对象：CSystemIncludeTiShi t;
		2、建立窗口：t.CreateEx();
		3、设置保存系统头文件数据的文件名：SetIncludeFileDatabase(szFile);
		   如果不设置文件名，则默认为当前模块目录下的 SystemIncludeDatabase.txt
		   注意：由于默认设置是在OnCreate中设置的，所以这步一定要在CreateEx后。
	    4、装载头文件到内存和提示框：Load();
版  本：1.0.0.1
作  者：康  林
时  间：2006年9月8日 15:37:51
*******************************************************************************************************/
class CSystemIncludeTiShi : public CIncludeTiShi
{
	DECLARE_DYNAMIC(CSystemIncludeTiShi)

public:
	CSystemIncludeTiShi();
	virtual ~CSystemIncludeTiShi();

protected:
	virtual BOOL GetIncludeFile();

	// Enter 键事件。响应列表控件的确定消息。
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
类  名：CLocalIncludeTiShi
描  述：VC++的系统头文件提示框。
用  法：
版  本：1.0.0.1
作  者：康  林
时  间：2006年9月8日 16:46:51
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

	// Enter 键事件。响应列表控件的确定消息。
	virtual int OnEnter(LPCTSTR pszText);

	INT ListProjectItem(EnvDTE::ProjectItems * pProjItems);
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};