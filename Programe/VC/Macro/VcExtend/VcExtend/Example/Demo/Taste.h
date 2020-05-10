#ifndef __TASTE_HPP__
#define __TASTE_HPP__
#pragma once

#include "Show.h"
/////////////////////////////////////////////////////////////////////////////

class CTaste : public CShow
{
public: 
    CTaste();
    virtual ~CTaste();

public:
    virtual void Serialize(CArchive& ar);


protected:


private:


/////////////////////////////////////////////////////////////////////////////
DECLARE_SERIAL(CTaste)

#ifdef _DEBUG
public:
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

//!begin get/set
};

#include "Taste.inl"
#endif