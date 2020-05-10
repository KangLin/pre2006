/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：Limit.h
描  述：
版  本：2005.6.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年7月12日
时  间：19:06:21
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/
#include < atlbase.h > 

#pragma once

class CLimit
{
public:
    CLimit(void);
    CLimit(LPCTSTR lpszKey);
	~CLimit(void);

    // 得到硬盘序号
	DWORD GetDiskNo(void);
	// 得到注册码
	DWORD GetRegistNo(DWORD dwMachine = 0);
	// 得到注册表中的注册码的值 
	DWORD GetRegistNoInRegedit();
	// 得机器码
	DWORD GetMachineNo();
    // 把注册值写入注册表
	BOOL WriteRegist(DWORD dwRegistNo = 0);
	// 得到指定的注册表中的值
	BOOL GetRegist(LPCTSTR lpszKey = NULL);
	// 写入日期
	BOOL WriteDate();
	// 得到剩下的使用期限
	DWORD GetDays();
	// 验证注册码
    BOOL ValidateRegistNo(DWORD dwRegistNo);
    
private:
    DWORD m_dwDiskSerialNumber;  //硬盘序列号
    DWORD m_dwMachineNo;         //机器码
    DWORD m_dwRegist;            //注册码
	DWORD m_dwRegVal;            //注册表中的加密的注册码值
    CString m_szSoftName;        //软件名

    DWORD m_dwXOR;
    DWORD m_dwXOR1;
    DWORD m_dwXOR2;
    DWORD m_dwXOR3;
    DWORD m_dwDay;
    DWORD m_dwMonth;
    DWORD m_dwYear;
    CRegKey m_reg;
    CString m_szRegKey;
};

extern "C" BOOL Regist(BOOL bShow = FALSE, LPCTSTR lpszKey = NULL, BOOL bTrueShow = FALSE);
