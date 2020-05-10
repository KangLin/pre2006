/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    SystemCommand.h
\brief   用于处理系统信息的命令
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年9月10日  15:52:05
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/
#pragma once

#ifdef SYSTEMINFO_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

class DllExport CSystemCommand
{
public:
	CSystemCommand(CCommand * pCmd = NULL);
	virtual ~CSystemCommand(void);

	int QueryWMIWin32OperationSystemInformaion(CCommand * pCmd);
	int QueryWMIComputerSystemInformation(CCommand * pCmd);
	int QueryWMIServiceInformation(CCommand * pCmd);


private:
	CCommand *m_pCmd;
};
