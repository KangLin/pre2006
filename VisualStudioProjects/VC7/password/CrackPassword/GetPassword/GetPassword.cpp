// GetPassword1.cpp: implementation of the CGetPassword class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GetPassword.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGetPassword::CGetPassword()
{

}

CGetPassword::~CGetPassword()
{

}

CString CGetPassword::GetPassword()
{
	return CString(_T(""));
}

int CGetPassword::SetRule(LPCTSTR lpszRule)
{
	return 0;
}
