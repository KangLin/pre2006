#pragma once
#include "data.h"

class CRecvData : public CData
{
public:
	CRecvData(void);
	virtual ~CRecvData(void);

	//Çå³ýÊý¾Ý
	virtual int Clear();

private:
	int m_nRecvLength;
};
