#ifndef __ACTIVEDESKTOP_H_KL__
#define __ACTIVEDESKTOP_H_KL__

#pragma once

#include <atlbase.h>
#include <WinInet.h>
#include <shlobj.h>

class CActiveDesktop
{
public:
	CActiveDesktop(void);
	~CActiveDesktop(void);

	BOOL SetDesktop(LPCTSTR szFile);

private:
	CComQIPtr<IActiveDesktop>  m_ActiveDesktop;
	HRESULT m_hResult;
};

#endif __ACTIVEDESKTOP_H_KL__