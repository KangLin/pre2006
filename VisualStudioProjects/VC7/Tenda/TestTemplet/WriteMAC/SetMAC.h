#pragma once
#include "..\TestItem.h"
#include "..\Logon.h"

class CSetMAC : public CTestItem
{
public:
	CSetMAC(void);
	virtual ~CSetMAC(void);
	int DoPrepare(void);

protected:
	CString m_szMAC;
	int m_Num;      //���д�벻�ɹ�,�ظ�д�Ĵ���
	int m_Increate; //MAC��ַ������ֵ
	UINT m_TimeOut;

	DWORD HexStrToDWORD(char * str, int nSize);
	int MACStrToHex(char * pstrMAX, char * pHex);

	virtual int WriteMAC(void);
};
