#pragma once
#include "Encrypter.h"

class CDESEncrypter : public CEncrypter
{
public:
	CDESEncrypter(void);
	~CDESEncrypter(void);

	virtual int EncryptData(const char * inBuf, const int & inLen, char * outBuf, int & outLen);
	virtual int DecryptData(const char * inBuf, const int & inLen, char * outBuf, int & outLen);
};
