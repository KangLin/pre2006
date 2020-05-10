#ifndef __GLOBALVALUE_H_KL_2007_07_02__
#define __GLOBALVALUE_H_KL_2007_07_02__

#pragma once

#include ".\Dll.h"
#include "..\..\System\Communicate\ManageSocket.h"
#include ".\NetManageServer.h"
#include <list>

using namespace std;

class CGlobal
{
public:
	CGlobal();
	~CGlobal();

	INT GetDllConfig(_tstring & szFile);
	INT OnDo();
	INT LoadDLL();
	INT Communicate();

	CDll m_Dll;
	CNetManageServer* m_pServer;
	CManageSocket * m_pMagSocket;

private:
	int m_nPort;

};

#endif //__GLOBALVALUE_H_KL_2007_07_02__
