#pragma once

#include "..\..\TestTemplet\TestItem.h"
#include "..\..\TestTemplet\Logon.h"
#include "..\..\TestTemplet\NET\SetTestSock.h"

class CSetMAC : public CTestItem
{
public:
	CSetMAC(void);
	virtual ~CSetMAC(void);
	int DoPrepare(void);

private:
	CString m_szMAC;
	//CSocket m_Sock;
	//CAsyncSocket m_Sock;
	CTestSocket m_Sock;
	int m_Num; //如果写入不成功,重复发送次数
	int m_Increate; //MAC地址的增加值
	BOOL m_bSet;
	CString m_szIP;
	UINT m_nPort;
	UINT m_TimeOut;

	DWORD HexStrToDWORD(char * str, int nSize);
	int WriteMAC(void);
};
