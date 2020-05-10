#pragma once

class CTException
{
public:
	CTException();
	CTException(LPCTSTR lpErr);
	CTException(LPCTSTR lpErr, int nErr);
	CTException(CTException & e);
	virtual ~CTException();
	LPCTSTR what();
	int GetErr(){return m_nErr;}

private:
	TCHAR * m_pErr;
	int m_nErr;
};
