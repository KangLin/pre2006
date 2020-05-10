#pragma once
#include "..\Platform\Platform\dll.h"
#include "..\Commonality\EnumConfig.h"
#include <list>

using namespace std;

/*!
\class   CDll
\brief   用于 Dll 库的加载和管理
\version 1.0
\author  康  林
\date    2007-8-14 16:40:42
*/
class CDll
{
public:
	CDll(void);
	~CDll(void);

	//初始函数
	typedef INT (*PDOINITALIZE)();
	//命令执行函数
	typedef INT (_stdcall *PDOCOMMAND)(DWORD dwCmd, CCommand* pCmd);
	//结束函数
	typedef INT (*PDOEND)();
	//设置一个上下文，主要用于给DLL传递相关的参数
	typedef INT (_stdcall *PSETCONTEXT)(void* pContext);

	typedef struct _DLL_STRUCT
	{
		_tstring szName;            //!< DLL 名
		dll_t hDll;                 //!< DLL 句柄
		PDOINITALIZE pDoInitalize;  //!< 初始化函数指针
		PDOCOMMAND pDoCommand;      //!< 命令函数指针，此函数用于分派命令。
		PDOEND pDoEnd;              //!< 结束函数指针
		PSETCONTEXT pSetContext;    //!< 设置上下文函数指针，主要向DLL传一个参数指针
	} DLL_STRUCT, *PDLL_STRUCT;

	INT Load();
	INT UnLoad();

	static INT EnumOperate(LPCTSTR pszValue);

private:
	CEnumConfig m_ConfigFile;

public:
	list <PDLL_STRUCT> m_lstDll;

};
