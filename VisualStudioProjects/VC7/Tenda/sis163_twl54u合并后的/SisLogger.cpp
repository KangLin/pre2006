// SisLogger.cpp: implementation of the SisLogger class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sis163.h"
#include "SisLogger.h"
#include <fstream.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using std::endl;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SisLogger * SisLogger::m_pInstance = NULL;

SisLogger * SisLogger::GetInstance()
{
    if (m_pInstance == NULL)
    {
        m_pInstance = new SisLogger();
        m_pInstance->os.open("sis163.log", ios::out | ios::app);
        
    }
    return m_pInstance;
}

SisLogger::~SisLogger()
{
    
}

SisLogger::SisLogger()
{
    
}

void SisLogger::LogFail()
{
    cout << "****Failed!!!!****" << endl;
    os << "****Failed!!!!****" << endl;
}

void SisLogger::LogSucc()
{
    cout << "****Pass....****" << endl;
    os << "****Pass....****" << endl;
}

void SisLogger::LogMsg(const char * msg)
{
	if (msg != NULL)
    {
        cout << msg << flush;
		os << msg;
		os.flush();
    }
}

void SisLogger::LogEndl()
{
    cout << endl;
    os << endl;
}
