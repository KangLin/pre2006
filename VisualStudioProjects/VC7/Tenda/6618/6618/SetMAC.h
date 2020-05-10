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
	int m_Num; //���д�벻�ɹ�,�ظ����ʹ���
	int m_Increate; //MAC��ַ������ֵ
	BOOL m_bSet;
	CString m_szIP;
	UINT m_nPort;
	UINT m_TimeOut;

	DWORD HexStrToDWORD(char * str, int nSize);
	int WriteMAC(void);
};
