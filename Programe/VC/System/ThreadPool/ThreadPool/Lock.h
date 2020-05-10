#pragma once

class CLock
{
public:
	CLock(void);
	virtual ~CLock(void);

	int Lock();
	int UnLock();

private:
	CRITICAL_SECTION m_CriticalSection;
};
