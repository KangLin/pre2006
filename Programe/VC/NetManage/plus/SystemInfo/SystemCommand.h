/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    SystemCommand.h
\brief   ���ڴ���ϵͳ��Ϣ������
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��9��10��  15:52:05
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
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
