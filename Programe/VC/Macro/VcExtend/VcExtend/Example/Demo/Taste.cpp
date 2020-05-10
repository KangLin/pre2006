#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "stdafx.h"
#include "Taste.h"

/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CTaste, CShow, 1)

/////////////////////////////////////////////////////////////////////////////


CTaste::CTaste()
{

}

CTaste::~CTaste()
{

}

void CTaste::Serialize(CArchive& ar)
{
    CShow::Serialize(ar);
    if (ar.IsStoring())
    {
    }
    else
    {
    }
}

#ifdef _DEBUG
void CTaste::AssertValid() const
{
	CShow::AssertValid();
}

void CTaste::Dump(CDumpContext& dc) const
{
	CShow::Dump(dc);
}
#endif
