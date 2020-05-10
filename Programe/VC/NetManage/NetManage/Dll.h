#pragma once
#include "..\Platform\Platform\dll.h"
#include "..\Commonality\EnumConfig.h"
#include <list>

using namespace std;

/*!
\class   CDll
\brief   ���� Dll ��ļ��غ͹���
\version 1.0
\author  ��  ��
\date    2007-8-14 16:40:42
*/
class CDll
{
public:
	CDll(void);
	~CDll(void);

	//��ʼ����
	typedef INT (*PDOINITALIZE)();
	//����ִ�к���
	typedef INT (_stdcall *PDOCOMMAND)(DWORD dwCmd, CCommand* pCmd);
	//��������
	typedef INT (*PDOEND)();
	//����һ�������ģ���Ҫ���ڸ�DLL������صĲ���
	typedef INT (_stdcall *PSETCONTEXT)(void* pContext);

	typedef struct _DLL_STRUCT
	{
		_tstring szName;            //!< DLL ��
		dll_t hDll;                 //!< DLL ���
		PDOINITALIZE pDoInitalize;  //!< ��ʼ������ָ��
		PDOCOMMAND pDoCommand;      //!< �����ָ�룬�˺������ڷ������
		PDOEND pDoEnd;              //!< ��������ָ��
		PSETCONTEXT pSetContext;    //!< ���������ĺ���ָ�룬��Ҫ��DLL��һ������ָ��
	} DLL_STRUCT, *PDLL_STRUCT;

	INT Load();
	INT UnLoad();

	static INT EnumOperate(LPCTSTR pszValue);

private:
	CEnumConfig m_ConfigFile;

public:
	list <PDLL_STRUCT> m_lstDll;

};
