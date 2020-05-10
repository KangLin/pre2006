#ifndef __SYSTEM_H_KL_2007_06_06__
#define __SYSTEM_H_KL_2007_06_06__

#pragma once

#include <string>
using namespace std;

#ifdef _UNICODE
#define _tstring wstring
#else
#define _tstring string
#endif // 结束 #ifdef


/*!
\brief   用于枚举目录时的回调处理函数
\param   LPCTSTR szFile：
\return  类型为 BOOL 。
\version 1.0
\author  康  林
\date    2007-6-6 21:04:16
*/
typedef BOOL(*OPERATORFILE)(LPCTSTR szFile);

class CSystem
{
public:
	CSystem();
	~CSystem();

	_tstring GetSystemDirectory();
	_tstring GetSystemRootDirectory();

	INT EnumRootDirectory(OPERATORFILE operat);

protected:
private:
};

#endif //__SYSTEM_H_KL_2007_06_06__