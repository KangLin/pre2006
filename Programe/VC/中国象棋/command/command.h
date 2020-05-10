/*******************************************************************************************************
文件名：command.h
功  能：实现命令
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-12-29
时  间：19:45:23

FileName：command.h
Function：
Compiler：Visual C++ 6.0
Author：  KangLin
          Copyright 2004 KangLin
Date：    2004-12-29
Time：    19:45:23
*******************************************************************************************************/

#if !defined(AFX_DATA_H__79E1A59E_06FD_4AB9_9479_CFB68CD584D8__INCLUDED_)
#define AFX_DATA_H__79E1A59E_06FD_4AB9_9479_CFB68CD584D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCommand  
{
public:	
	CCommand(LPVOID lpBuf, int iLen);
	CCommand(const CCommand& cmd);

    long GetLongPara();
    CString GetPara();
    
	BOOL AddPara(long lPara);
	BOOL AddPara(CString szPara);
    BOOL AddPara(G_COMMAND command);

    const CCommand& operator +=(CString szPara);
    const CCommand& operator +=(long lPara);
    const CCommand& operator +=(G_COMMAND cmd);

    const CCommand& operator =(const CCommand& cmd);
    const CCommand& operator =(long command);

	long GetCommand();
	void SetCommand(long command);

	CCommand();
	virtual ~CCommand();

    //操作
    int GetLength();
    LPVOID GetDataRef();

private:
    void Free();
    BYTE m_Data[g_MAXBUFLEN];//数据指针
    UINT m_uLen;             //数据的长度
    
    int GetCommandHeadLen();
};

#endif // !defined(AFX_DATA_H__79E1A59E_06FD_4AB9_9479_CFB68CD584D8__INCLUDED_)
