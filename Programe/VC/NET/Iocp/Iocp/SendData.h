#pragma once
#include "data.h"

class CSendData : public CData
{
public:
	CSendData(void);
	virtual ~CSendData(void);

private:
	int m_nSendLength;
};
