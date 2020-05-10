#pragma once

#include "checkport.h"
#include <afxmt.h>

struct _CombineCheckParam
{
	void * pInstance;
	int nPort;
};

class CCombineCheckPort:public CCheckPort
{
public:
	CCombineCheckPort(void);
	~CCombineCheckPort(void);

	virtual int DoTest(void);

	CTestSocket * GetSocket();
	CLogon * GetLogon();
	int GetTimeOut();	
	int GetPingNum();
	int GetPort();
	int SetRecive(int nPort, int nNum); //���ý��յ���������
	int GetRecive(int nPort);
	CString GetIP(int nPort);
	int GetRate();
	UINT GetID();
	HANDLE GetEvent(int nPort);
	static DWORD _stdcall SendPing(void * para);
	
private:
	_CombineCheckParam m_para;
	vector < int > m_nRecive; //������
	int m_nRate; //PING �Ľ�����
	UINT m_nID;
	HANDLE * m_phEvent;

public:
	HANDLE m_hSendEvent;

};
