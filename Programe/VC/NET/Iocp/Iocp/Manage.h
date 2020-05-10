#pragma once

class CManage
{
public:
	CManage(void);
	virtual ~CManage(void);

	//用于工作线程退出
	BOOL * m_pExit;
};
