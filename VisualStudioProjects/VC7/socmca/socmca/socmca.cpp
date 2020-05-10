// socmca.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "socmca.h"
#include ".\WMI\WMI.h"

#ifdef _WIN32
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#endif

using namespace std;

#ifdef _WIN32
int _tmain(int argc, TCHAR * argv[], TCHAR * envp[])
#endif
#ifdef __LINUX__
int main(int argc, char * argv[], char * envp[])
#endif // ½áÊø #ifdef __LINUX__
{
	int nRetCode = 0;

#ifdef _WIN32
	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		return 1;
	}

	_tsetlocale(LC_ALL, _T(""));
#endif

	return nRetCode;
}
