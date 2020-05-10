#ifndef __PASSWORD_MANAGER_H_KL_2008_01_13__
#define __PASSWORD_MANAGER_H_KL_2008_01_13__

#pragma once

#include <string>
#include <vector>
#include "typedef.h"
#include <time.h>
#include "EncrypterManager.h"
#include <map>

class CPasswordManager
{
public:
	CPasswordManager(void);
	~CPasswordManager(void);

	typedef struct _PASSWORD_DATA
	{
		tstring szTitle;
		tstring szPassword;
		tstring szDescription;
		tstring szKey;
		time_t time;
	}PASSWORD_DATA, *PPASSWORD_DATA;

	typedef std::map<tstring, PASSWORD_DATA>::iterator POSITION;

	//����������
	int InsertPassword(const tstring & szTitle, const PASSWORD_DATA & data);
	//�õ�ָ��������
	int GetPassword(const tstring & szTitle, PASSWORD_DATA & data);
	//��������
	int GetFirstPassword(POSITION & pos);
	int GetNextPassword(PASSWORD_DATA &data, POSITION & pos);
	//ɾ������
	int DeletePassword(const tstring & szTitle);

	//����
	int Sort();

	//IO����
	int LoadFile(LPCTSTR lpszFile);
	int OutFile(LPCTSTR lpszFiel);

	int SetEncrypterManager(CEncrypterManager * pMng);

	//����ڴ��е�����
	int ClearData();


private:
	typedef struct _FILE_HEAD
	{
		int MajorVerson;  //���汾��
		int MinorVerson;  //�ΰ汾��
		int nUnicode;     //UNICODE��
		long Extend;      //��չ
	}FILE_HEAD, *PFILE_HEAD;

	FILE_HEAD m_Head;
	tstring m_szFile;

	std::map<tstring, PASSWORD_DATA> m_Passwords;

	CEncrypterManager * m_pEncrypterManager;

	int WriterFile(char * pBuf, const int nLen, std::ofstream * pOut);
	int ReadFile(char ** pBuf, std::ifstream * pIn);
};

#endif// __PASSWORD_MANAGER_H_KL_2008_01_13__
