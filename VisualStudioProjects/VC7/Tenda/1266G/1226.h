#pragma once
#include "testitem.h"
#include "afxinet.h"

class C1226 : public CTestItem
{
public:
	C1226(void);
	~C1226(void);
	virtual DoTest();

private:
	CInternetSession m_intSession;
	CHttpConnection * m_pHttpConn;

};
