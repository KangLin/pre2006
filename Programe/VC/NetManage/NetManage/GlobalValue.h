#ifndef __GLOBALVALUE_H_KL_2007_07_02__
#define __GLOBALVALUE_H_KL_2007_07_02__

#pragma once

#include ".\Dll.h"
#include <list>

using namespace std;

class CGlobalValue
{
public:
	CGlobalValue();
	~CGlobalValue();

	INT Initalize();
	INT GetDllConfig(_tstring & szFile);

	CDll m_Dll;

};

#endif //__GLOBALVALUE_H_KL_2007_07_02__
