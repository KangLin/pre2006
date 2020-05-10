#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "stdafx.h"
#include "Show.h"

/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CShow, CObject, 1)

/////////////////////////////////////////////////////////////////////////////


CShow::CShow()
{

}

CShow::~CShow()
{

}

void CShow::Serialize(CArchive& ar)
{
    CObject::Serialize(ar);
    if (ar.IsStoring())
    {
    }
    else
    {
    }
}

CString CShow::CreateNewObj(CString Name, int Age)
{
    return "";
}

#ifdef _DEBUG
void CShow::AssertValid() const
{
	CObject::AssertValid();
}

void CShow::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif
