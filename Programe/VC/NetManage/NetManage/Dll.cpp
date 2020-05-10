#include "StdAfx.h"
#include "Dll.h"
#include ".\Global.h"

extern CGlobal g_GV;

CDll::CDll(void)
{
	INT nRet = S_OK;
	_tstring szFileName;
	//修改:
	if(S_FALSE == g_GV.GetDllConfig(szFileName))
	{
		TRACE(_T("Get Dll Config error.\n"));
	} // 结束 if(S_FALSE == g_GV.GetDllConfig(szFileName))
	nRet = m_ConfigFile.SetFileName(szFileName.c_str());
	if(S_FALSE == nRet)
	{
		TRACE(_T("config initalize error.\n"));
	}// 结束 if(S_FALSE == nRet)
}

CDll::~CDll(void)
{
	UnLoad();
}

/*!
\brief   Load
\param   无
\return  类型为 INT 。
\version 1.0
\author  康  林
\date    2007-8-14 16:40:32
*/
INT CDll::Load()
{
	INT nRet = S_OK;
	nRet = m_ConfigFile.Enum(_T("DLL"), EnumOperate);
	return nRet;
}

INT CDll::UnLoad()
{
	list<PDLL_STRUCT>::iterator iterator;
	for(iterator = m_lstDll.begin(); iterator != m_lstDll.end(); iterator++)
	{
		if(*iterator)
		{
			PDLL_STRUCT p = *iterator;
			if(p->pDoEnd)
			{
				int nRet = p->pDoEnd();
				if(S_FALSE == nRet)
				{
					TRACE(_T("动态库 %s 初始化 DoEnd 函数错误。\n"), p->szName.c_str());
				} // 结束 if(S_FALSE == nRet)
			}// 结束 if(p->pDoEnd)

			if(0 == free_library(p->hDll))
			{
				TRACE(_T("释放动态库 %s 成功。\n"), p->szName.c_str()); 
			}
			else
			{
				TRACE(_T("释放动态库 %s 失败。\n"), p->szName.c_str());
			} // 结束 if(0 == free_library(p->hDll))
			delete p;
		} // 结束 if(*iterator)
	}// 结束 for(iterator = m_lstDll.begin(); iterator != m_lstDll.end(); iterator++)
	m_lstDll.clear();
	return S_OK;
}

INT CDll::EnumOperate(LPCTSTR pszValue)
{
	INT nRet = S_OK;
	dll_t hDll = NULL;
	//加载动态库
	hDll = load_library(pszValue);
	if(NULL == hDll)
	{
		TRACE(_T("加载动态库 %s 出错\n"), pszValue);
		return S_FALSE;
	}// 结束 if(NULL == hdll)

	TRACE(_T("加载动态库 %s 成功\n"), pszValue);

	//动态加载库函数
	// - 加载初始化函数
	PDOINITALIZE pInitalize = (PDOINITALIZE)get_function(hDll, "DoInitalize");
	if(NULL == pInitalize)
	{
		TRACE(_T("加载动态库 %s 的 DoInitalize 函数出错\n"), pszValue);
	}// 结束 if(NULL == pInitalize)
	// - 加载命令分发函数
	PDOCOMMAND pDoCommand = (PDOCOMMAND)get_function(hDll, "DoCommand");
	if(NULL == pDoCommand)
	{
		TRACE(_T("加载动态库 %s 的 DoCommand 函数出错\n"), pszValue);
	}// 结束 if(NULL == pDoCommand)
	// - 加载结束函数
	PDOEND pDoEnd = (PDOEND)get_function(hDll, "DoEnd");
	if(NULL == pDoEnd)
	{
		TRACE(_T("加载动态库 %s 的 DoEnd 函数出错\n"), pszValue);
	}// 结束 if(NULL == pInital)

	PSETCONTEXT pSetContext = (PSETCONTEXT)get_function(hDll, "SetContext");
	if(NULL == pSetContext)
	{
		TRACE(_T("加载动态库 %s 的 SetContext 函数出错\n"), pszValue);
	}

	PDLL_STRUCT pDllStruct = NULL;
	pDllStruct = new DLL_STRUCT;
	if(NULL == pDllStruct)
	{
		TRACE(_T("加载动态库 %s 时分配内存出错\n"), pszValue);
		return S_FALSE;
	}// 结束 if(NULL == pDllStruct)

	memset(pDllStruct, 0, sizeof(DLL_STRUCT));
	pDllStruct->szName = pszValue;
	pDllStruct->hDll = hDll;
	pDllStruct->pDoInitalize = pInitalize;
	pDllStruct->pDoCommand = pDoCommand;
	pDllStruct->pDoEnd = pDoEnd;
	pDllStruct->pSetContext = pSetContext;

	//保存到动态库链表
	g_GV.m_Dll.m_lstDll.push_back(pDllStruct);

	// 执行初始化函数
	if(pInitalize)
	{
		nRet = pInitalize();
		if(S_FALSE == nRet)
		{
			TRACE(_T("动态库 %s 初始化 DoInitalize 函数错误\n"), pszValue);
		} // 结束 if(S_FALSE == nRet)
	} // 结束 if(pInitalize)

	return nRet;
}