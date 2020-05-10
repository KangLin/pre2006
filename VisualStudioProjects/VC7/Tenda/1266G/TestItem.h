/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����TestItem.h
��  ����������Ŀ����
��  ����1.0
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��11��9��
ʱ  �䣺10:43:38
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
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
	CString m_szName; //��Ŀ��

protected:
	CLogon* m_plog;
};
