#include "StdAfx.h"
#include "Dll.h"
#include ".\Global.h"

extern CGlobal g_GV;

CDll::CDll(void)
{
	INT nRet = S_OK;
	_tstring szFileName;
	//�޸�:
	if(S_FALSE == g_GV.GetDllConfig(szFileName))
	{
		TRACE(_T("Get Dll Config error.\n"));
	} // ���� if(S_FALSE == g_GV.GetDllConfig(szFileName))
	nRet = m_ConfigFile.SetFileName(szFileName.c_str());
	if(S_FALSE == nRet)
	{
		TRACE(_T("config initalize error.\n"));
	}// ���� if(S_FALSE == nRet)
}

CDll::~CDll(void)
{
	UnLoad();
}

/*!
\brief   Load
\param   ��
\return  ����Ϊ INT ��
\version 1.0
\author  ��  ��
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
					TRACE(_T("��̬�� %s ��ʼ�� DoEnd ��������\n"), p->szName.c_str());
				} // ���� if(S_FALSE == nRet)
			}// ���� if(p->pDoEnd)

			if(0 == free_library(p->hDll))
			{
				TRACE(_T("�ͷŶ�̬�� %s �ɹ���\n"), p->szName.c_str()); 
			}
			else
			{
				TRACE(_T("�ͷŶ�̬�� %s ʧ�ܡ�\n"), p->szName.c_str());
			} // ���� if(0 == free_library(p->hDll))
			delete p;
		} // ���� if(*iterator)
	}// ���� for(iterator = m_lstDll.begin(); iterator != m_lstDll.end(); iterator++)
	m_lstDll.clear();
	return S_OK;
}

INT CDll::EnumOperate(LPCTSTR pszValue)
{
	INT nRet = S_OK;
	dll_t hDll = NULL;
	//���ض�̬��
	hDll = load_library(pszValue);
	if(NULL == hDll)
	{
		TRACE(_T("���ض�̬�� %s ����\n"), pszValue);
		return S_FALSE;
	}// ���� if(NULL == hdll)

	TRACE(_T("���ض�̬�� %s �ɹ�\n"), pszValue);

	//��̬���ؿ⺯��
	// - ���س�ʼ������
	PDOINITALIZE pInitalize = (PDOINITALIZE)get_function(hDll, "DoInitalize");
	if(NULL == pInitalize)
	{
		TRACE(_T("���ض�̬�� %s �� DoInitalize ��������\n"), pszValue);
	}// ���� if(NULL == pInitalize)
	// - ��������ַ�����
	PDOCOMMAND pDoCommand = (PDOCOMMAND)get_function(hDll, "DoCommand");
	if(NULL == pDoCommand)
	{
		TRACE(_T("���ض�̬�� %s �� DoCommand ��������\n"), pszValue);
	}// ���� if(NULL == pDoCommand)
	// - ���ؽ�������
	PDOEND pDoEnd = (PDOEND)get_function(hDll, "DoEnd");
	if(NULL == pDoEnd)
	{
		TRACE(_T("���ض�̬�� %s �� DoEnd ��������\n"), pszValue);
	}// ���� if(NULL == pInital)

	PSETCONTEXT pSetContext = (PSETCONTEXT)get_function(hDll, "SetContext");
	if(NULL == pSetContext)
	{
		TRACE(_T("���ض�̬�� %s �� SetContext ��������\n"), pszValue);
	}

	PDLL_STRUCT pDllStruct = NULL;
	pDllStruct = new DLL_STRUCT;
	if(NULL == pDllStruct)
	{
		TRACE(_T("���ض�̬�� %s ʱ�����ڴ����\n"), pszValue);
		return S_FALSE;
	}// ���� if(NULL == pDllStruct)

	memset(pDllStruct, 0, sizeof(DLL_STRUCT));
	pDllStruct->szName = pszValue;
	pDllStruct->hDll = hDll;
	pDllStruct->pDoInitalize = pInitalize;
	pDllStruct->pDoCommand = pDoCommand;
	pDllStruct->pDoEnd = pDoEnd;
	pDllStruct->pSetContext = pSetContext;

	//���浽��̬������
	g_GV.m_Dll.m_lstDll.push_back(pDllStruct);

	// ִ�г�ʼ������
	if(pInitalize)
	{
		nRet = pInitalize();
		if(S_FALSE == nRet)
		{
			TRACE(_T("��̬�� %s ��ʼ�� DoInitalize ��������\n"), pszValue);
		} // ���� if(S_FALSE == nRet)
	} // ���� if(pInitalize)

	return nRet;
}