#include "StdAfx.h"

#include "ActiveDesktop.h"

CActiveDesktop::CActiveDesktop(void)
{
	m_hResult = m_ActiveDesktop.CoCreateInstance(CLSID_ActiveDesktop);
	ASSERT(SUCCEEDED(m_hResult)); 	
}

CActiveDesktop::~CActiveDesktop(void)
{
}

BOOL CActiveDesktop::SetDesktop(LPCTSTR szFile)
{
	ASSERT(m_ActiveDesktop);
	m_hResult = m_ActiveDesktop->SetWallpaper(szFile, NULL);
	if(SUCCEEDED(m_hResult))
	{
		return TRUE; 
	}
	else
	{
		return FALSE;
	} // ½áÊø if(SUCCEEDED(m_hResult))
}