/*******************************************************************************************************
�ļ�����command.h
��  �ܣ�ʵ������
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-12-29
ʱ  �䣺19:45:23

FileName��command.h
Function��
Compiler��Visual C++ 6.0
Author��  KangLin
          Copyright 2004 KangLin
Date��    2004-12-29
Time��    19:45:23
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

    //����
    int GetLength();
    LPVOID GetDataRef();

private:
    void Free();
    BYTE m_Data[g_MAXBUFLEN];//����ָ��
    UINT m_uLen;             //���ݵĳ���
    
    int GetCommandHeadLen();
};

#endif // !defined(AFX_DATA_H__79E1A59E_06FD_4AB9_9479_CFB68CD584D8__INCLUDED_)
