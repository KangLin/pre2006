/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    ProcessCommand.h
\brief   ���ڽ��������
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��8��15��  15:46:11
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/
#ifndef __PROCESSCOMMAND_H_KL_2008_08_15__
#define __PROCESSCOMMAND_H_KL_2008_08_15__

#pragma once
#include <vector>
#include ".\ProcessInformation.h"
using namespace std;

#ifdef PROCESS_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

class DllExport CProcessCommand
{
public:
	CProcessCommand(CCommand* pCmd);
	~CProcessCommand(void);

	int QueryAllProcess(CCommand * pCmd);
	int QueryProcess(CCommand * pCmd);
	int QueryAllProcessModule(CCommand * pCmd);
	int QueryProcessModule(CCommand * pCmd);
	int QueryProcessName(CCommand * pCmd);
	int QueryProcessPath(CCommand * pCmd);

	int AnswerAllProcess(vector<CProcessInformation::PROCESS_INFO> *pInfo);
	int AnswerProcess(CProcessInformation::PROCESS_INFO * pInfo);
	int AnswerAllProcessModule(vector<CProcessInformation::PROCESS_MODULE_INFO> *pInfo);
	int AnswerProcessModule(CProcessInformation::PPROCESS_MODULE_INFO pInfo);

private:
	CProcessCommand(void);
	CCommand* m_pCmd;
};


#endif //__PROCESSCOMMAND_H_KL_2008_08_15__