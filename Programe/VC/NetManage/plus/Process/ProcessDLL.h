/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    ProcessDLL.h
\brief   ����DLL�ĵ�������ͷ�ļ�
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��8��14��  17:16:25
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/

#ifndef __PROCESSDLL_H_KL_2008_08_14__
#define __PROCESSDLL_H_KL_2008_08_14__

#pragma once

extern "C" _stdcall INT DoInitalize();
extern "C" _stdcall INT DoCommand(DWORD dwCmd, CCommand * pCmd);
extern "C" _stdcall INT DoEnd();

extern "C" _stdcall INT SetContext(void* pContext);

#endif //__PROCESSDLL_H_KL_2008_08_14__
