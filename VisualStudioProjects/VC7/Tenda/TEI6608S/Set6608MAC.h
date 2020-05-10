#pragma once
#include "..\TestTemplet\WriteMAC\SetMAC.h"
#include "..\TestTemplet\NET\SetTestSock.h"

class CSet6608MAC :	public CSetMAC
{
public:
	CSet6608MAC(void);
	~CSet6608MAC(void);

protected:
	CString m_szIP;
	UINT m_nPort;
	UINT m_nLocatePort;

	CTestSocket m_Sock;

	virtual int WriteMAC(void);

	struct TFTP
	{
		unsigned short op;
		char buf[1];
	};
};
