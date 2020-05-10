/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    command.h
\brief   ������ͷ�ļ�
\note
<pre>
�������ĸ�ʽ��ʽ��
___________________________________________________________________________________________________________________
| WORD       |     DWORD     | DWORD | DWORD |  DWORD   |..............|   DWORD  |...........|  DWORD  |.........|
|------------|---------------|-------|-------|----------|--------------|----------|-----------|---------|---------|
|��־(kl)    |�������ݵĳ��� |�汾�� |  ���� | �������� |      ����    | �������� |     ����  | ��������|   ����  | 
-------------------------------------------------------------------------------------------------------------------
�����ʽ��
______________________________________________________________________________
| DWORD |  DWORD   |..............|   DWORD  |...........|  DWORD  |.........|
|-------|----------|--------------|----------|-----------|---------|---------|
|  ���� | �������� |      ����    | �������� |     ����  | ��������|   ����  | 
------------------------------------------------------------------------------
</pre>
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��7��13��  17:19:40
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/


#ifndef __COMMAND_H_KL_2007_07_13__
#define __COMMAND_H_KL_2007_07_13__

#pragma once
#include ".\type.h"

/*!
\class   CCommand
\brief   �����ࡣ���ڴ�������Э��
\version 1.0
\author  ��  ��
\date    2007-8-14 15:13:30
*/
class CCommand
{
public:
	CCommand();
	~CCommand();

	//�õ�����
	DWORD GetCommand();
	//�õ�����
	DWORD GetPara();
	int GetPara(void ** pPara, DWORD* pLength);
	int GetPara(DWORD * dwPara);
	int GetPara(LONG * lgPara);
	int GetPara(_tstring * pPara);
	//�õ�ָ��λ�õĲ���
	int GetPara(int nPos, const void ** pBuf, DWORD* dwLength);

	//��������
	int SetCommand(DWORD dwCmd);
	int SetCommand(DWORD dwCmd, const void * pPara, DWORD dwLength);
	int SetCommand(const void * pBuf, DWORD dwLength);

	//���Ӳ���
	int AddPara(const void * pBuf, DWORD dwLength);
	int AddPara(DWORD dwPara);
	int AddPara(LONG lgPara);
	int AddPara(LPCTSTR lpszPara);
	int AddPara(UINT32 lpdwPara);
	int AddPara(BOOL bPara);
	//�޸�ָ��λ�õĲ���
	int ModifyPara(int nPos, const void * pBuf, DWORD dwLength);

	//�õ�����ָ��
	void * GetBuffer();
	//�õ����泤��
	int GetLength();

private:
	char * m_pBuffer;  //!<����ָ��
	int m_nLength;     //!<���ݵĳ���
	int m_nMaxLength;  //!<��󻺴�

	int m_nNextPara;   //!<��һ������λ��

	int Clear();
};


#endif //__COMMAND_H_KL_2007_07_13__