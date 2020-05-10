#pragma once
#include "Tishi.h"

// CT

class CT : public CTiShi
{
	DECLARE_DYNAMIC(CT)

public:
	CT();
	virtual ~CT();
	virtual void OnLeftButtonEvents(int nIndex, LPCTSTR lpszText);
protected:
	DECLARE_MESSAGE_MAP()
};


