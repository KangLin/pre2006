// common.cpp: implementation of the common class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "中国象棋控件.h"
#include "common.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*******************************************************************************************************
函数名：sig
功  能：符号函数
参  数：
         int x：整数
返回值：大于0，返回 1。等于0，返回0。小于0，返回-1。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-5
时  间：10:05:22
*******************************************************************************************************/
int sig(int x)
{
	if(x > 0)
		return 1;
	if(x < 0)
		return -1;
	return 0;
}