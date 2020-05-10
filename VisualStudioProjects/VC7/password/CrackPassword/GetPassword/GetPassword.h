// GetPassword1.h: interface for the CGetPassword class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GETPASSWORD1_H__A9AE4CA0_268D_4003_8969_D071D89B27D4__INCLUDED_)
#define AFX_GETPASSWORD1_H__A9AE4CA0_268D_4003_8969_D071D89B27D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGetPassword
{
public:
	CGetPassword();
	virtual ~CGetPassword();

	//得到密码
	CString GetPassword();
	//设置得到密码规则
	int SetRule(LPCTSTR lpszRule);

};

#endif // !defined(AFX_GETPASSWORD1_H__A9AE4CA0_268D_4003_8969_D071D89B27D4__INCLUDED_)
