#include "stdafx.h"

#include "GlobalValue.h"

CGlobalValue::CGlobalValue()
{
}

CGlobalValue::~CGlobalValue()
{
}

INT CGlobalValue::GetDllConfig(_tstring & szName)
{
	CFileEx fe;
	_tstring szPath = fe.GetFilePath();
	_tstring szConfig = szPath + _T("\\Dll.INI");
	szName = szConfig;
	return S_OK;
}

INT CGlobalValue::Initalize()
{
	INT nRet = S_OK;

	nRet = m_Dll.Load();
	if(S_FALSE == nRet)
	{
		TRACE(_T("%S(%d):���ض�̬���ӿ����\n"), __FILE__, __LINE__);
	}// ���� if(S_FALSE == nRet)

	return nRet;
}