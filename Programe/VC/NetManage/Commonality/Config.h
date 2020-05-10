#pragma once

class CConfig
{
public:
	CConfig(void);
	~CConfig(void);

	int SetFileName(LPCTSTR lpszFileName);
	int SetConfig(LPCTSTR pszItem, LPCTSTR pszKey, LPCTSTR pszValue);
	int GetConfig(LPCTSTR pszItem, LPCTSTR pszKey, _tstring & szRetValue, LPCTSTR lpDefault);

private:
	_tstring m_szFileName; //≈‰÷√Œƒº˛√˚
};
