// T.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TiShiTest.h"
#include "TiShi.h"
#include "T.h"
#include ".\t.h"


// CT

IMPLEMENT_DYNAMIC(CT, CTiShi)
CT::CT()
{
	
}

CT::~CT()
{
}


BEGIN_MESSAGE_MAP(CT, CTiShi)
END_MESSAGE_MAP()

// CT ��Ϣ�������

void CT::OnLeftButtonEvents(int nIndex, LPCTSTR lpszText)
{
	TRACE("CT::OnLeftButton");
	return;
}
