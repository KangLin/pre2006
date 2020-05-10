// SisLogger.h: interface for the SisLogger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SISLOGGER_H__1C924B7C_ED7C_4017_8383_9206EBF39CAC__INCLUDED_)
#define AFX_SISLOGGER_H__1C924B7C_ED7C_4017_8383_9206EBF39CAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Logger.h"
#include <fstream>


class SisLogger : public Logger  
{
public:
	static SisLogger * GetInstance();
	virtual ~SisLogger();

	void LogEndl();
    void LogFail();
    void LogSucc();
	void LogMsg (const char * msg);
protected:
    SisLogger();
    static SisLogger * m_pInstance;
    std::ofstream  os;

};

#endif // !defined(AFX_SISLOGGER_H__1C924B7C_ED7C_4017_8383_9206EBF39CAC__INCLUDED_)
