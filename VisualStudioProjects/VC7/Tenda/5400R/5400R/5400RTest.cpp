#include "StdAfx.h"
#include "5400rtest.h"
#include "PowerTest.h"

C5400RTest::C5400RTest(void)
{
}

C5400RTest::~C5400RTest(void)
{
}

int C5400RTest::DoPrepare(void)
{
	CPowerTest * pPower = new CPowerTest;
	if(!pPower)
	{
		m_log.Message(_T("���ʲ����ཨ������"));
		return 1;
	} // ���� if(!pPower)
	AddItem(pPower);

	return 0;
}
