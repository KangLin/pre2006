#pragma once
#include "..\TestTemplet\NET\TFTP\TFTP.h"

class C6608TFTP : public CTFTP
{
public:
	C6608TFTP(void);
	~C6608TFTP(void);
	virtual int DoTest(void);
};
