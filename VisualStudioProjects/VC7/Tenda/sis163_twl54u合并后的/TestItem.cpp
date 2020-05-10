// TestItem.cpp: implementation of the TestItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sis163.h"
#include "TestItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TestItem::TestItem()
{

}

TestItem::~TestItem()
{

}

void TestItem::DoPrepare()
{
}

void TestItem::DoEndWord(bool result)
{
}

void TestItem::SetGPIBDevice(GPIBDevice * pGPIB)
{
	m_pGPIB = pGPIB;
}