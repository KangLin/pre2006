/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：TestItem.h
描  述：测试项目基类
版  本：1.0
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年11月9日
时  间：10:43:38
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/
#pragma once

#include "Logon.h"

class CTestItem
{
public:
	CTestItem(void);
	virtual ~CTestItem(void);

	virtual int SetLog(CLogon * pLog);

	virtual int DoPrepare(void);
	virtual int DoTest(void);	
	virtual int DoEnd(void);
	virtual int SetName(LPCTSTR lpszName);
	virtual CString GetName(void);

private:
	CString m_szName; //项目名

protected:
	CLogon* m_plog;
};
