#pragma once

#include "..\TestItem.h"

class CBuildRule :
	public CTestItem
{
public:
	CBuildRule(void);
	~CBuildRule(void);

	virtual int DoTest();
private:
	CString m_szInFile;
	CString m_szOutFile;
};
