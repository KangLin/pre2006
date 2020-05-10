#include "StdAfx.h"
#include "SockTask.h"
#include <iostream>
#include <string>
#include <sstream>

int i = 0;
CSockTask::CSockTask(void)
{
	i++;
}

CSockTask::~CSockTask(void)
{
}

int CSockTask::Run()
{
	int nRet = EXIT;
	TRACE(_T("%s : %d\n"), _T("run sock task"), i);
	std::ostringstream os;
	os << "run sock task" << i << std::endl;
	std::cout << os.str().c_str();
	return nRet;
}