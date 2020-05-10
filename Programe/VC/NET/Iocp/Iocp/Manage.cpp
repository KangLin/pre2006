#include "StdAfx.h"
#include "Manage.h"

CManage::CManage(void)
{
	m_pExit = NULL;
}

CManage::~CManage(void)
{
	if(m_pExit)
	{
		*m_pExit = TRUE;
		m_pExit = NULL;
	} // ½áÊø if(pExit)
}
