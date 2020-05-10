#pragma once

class CEncrypter
{
public:
	CEncrypter(void);
	~CEncrypter(void);

	virtual int EncryptData(const char * inBuf, const int & inLen, char * outBuf, int & outLen) = 0;
	virtual int DecryptData(const char * inBuf, const int & inLen, char * outBuf, int & outLen) = 0;
};
