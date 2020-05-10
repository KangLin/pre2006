#pragma once
#include <map>
#include "typedef.h"
#include "Encrypter.h"

class CEncrypterManager
{
public:
	CEncrypterManager(void);
	~CEncrypterManager(void);

	int RegisterEncrypter(const tstring & szName, CEncrypter * pEncrypter);
	CEncrypter * GetEncrypter(const tstring & szName);
	int RemoveEncrypter(const tstring & szName);

private:
	std::map < tstring, CEncrypter * > m_Encrypter;
	CEncrypter * m_pDefault;

};
