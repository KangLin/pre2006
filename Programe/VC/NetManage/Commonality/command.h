/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    command.h
\brief   命令类头文件
\note
<pre>
整个包的格式格式：
___________________________________________________________________________________________________________________
| WORD       |     DWORD     | DWORD | DWORD |  DWORD   |..............|   DWORD  |...........|  DWORD  |.........|
|------------|---------------|-------|-------|----------|--------------|----------|-----------|---------|---------|
|标志(kl)    |报文内容的长度 |版本号 |  命令 | 参数长度 |      参数    | 参数长度 |     参数  | 参数长度|   参数  | 
-------------------------------------------------------------------------------------------------------------------
命令格式：
______________________________________________________________________________
| DWORD |  DWORD   |..............|   DWORD  |...........|  DWORD  |.........|
|-------|----------|--------------|----------|-----------|---------|---------|
|  命令 | 参数长度 |      参数    | 参数长度 |     参数  | 参数长度|   参数  | 
------------------------------------------------------------------------------
</pre>
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年7月13日  17:19:40
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/


#ifndef __COMMAND_H_KL_2007_07_13__
#define __COMMAND_H_KL_2007_07_13__

#pragma once
#include ".\type.h"

/*!
\class   CCommand
\brief   命令类。用于处理命令协议
\version 1.0
\author  康  林
\date    2007-8-14 15:13:30
*/
class CCommand
{
public:
	CCommand();
	~CCommand();

	//得到命令
	DWORD GetCommand();
	//得到参数
	DWORD GetPara();
	int GetPara(void ** pPara, DWORD* pLength);
	int GetPara(DWORD * dwPara);
	int GetPara(LONG * lgPara);
	int GetPara(_tstring * pPara);
	//得到指定位置的参数
	int GetPara(int nPos, const void ** pBuf, DWORD* dwLength);

	//设置命令
	int SetCommand(DWORD dwCmd);
	int SetCommand(DWORD dwCmd, const void * pPara, DWORD dwLength);
	int SetCommand(const void * pBuf, DWORD dwLength);

	//增加参数
	int AddPara(const void * pBuf, DWORD dwLength);
	int AddPara(DWORD dwPara);
	int AddPara(LONG lgPara);
	int AddPara(LPCTSTR lpszPara);
	int AddPara(UINT32 lpdwPara);
	int AddPara(BOOL bPara);
	//修改指定位置的参数
	int ModifyPara(int nPos, const void * pBuf, DWORD dwLength);

	//得到缓存指针
	void * GetBuffer();
	//得到缓存长度
	int GetLength();

private:
	char * m_pBuffer;  //!<缓存指针
	int m_nLength;     //!<内容的长度
	int m_nMaxLength;  //!<最大缓存

	int m_nNextPara;   //!<下一参数的位置

	int Clear();
};


#endif //__COMMAND_H_KL_2007_07_13__