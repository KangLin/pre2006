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
	int m_Num;      //如果写入不成功,重复写的次数
	int m_Increate; //MAC地址的增加值
	UINT m_TimeOut;

	DWORD HexStrToDWORD(char * str, int nSize);
	int MACStrToHex(char * pstrMAX, char * pHex);

	virtual int WriteMAC(void);
};
