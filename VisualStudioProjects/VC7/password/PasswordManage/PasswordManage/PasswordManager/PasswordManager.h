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

	//增加新密码
	int InsertPassword(const tstring & szTitle, const PASSWORD_DATA & data);
	//得到指定的密码
	int GetPassword(const tstring & szTitle, PASSWORD_DATA & data);
	//遍历密码
	int GetFirstPassword(POSITION & pos);
	int GetNextPassword(PASSWORD_DATA &data, POSITION & pos);
	//删除密码
	int DeletePassword(const tstring & szTitle);

	//排序
	int Sort();

	//IO操作
	int LoadFile(LPCTSTR lpszFile);
	int OutFile(LPCTSTR lpszFiel);

	int SetEncrypterManager(CEncrypterManager * pMng);

	//清除内存中的数据
	int ClearData();


private:
	typedef struct _FILE_HEAD
	{
		int MajorVerson;  //主版本号
		int MinorVerson;  //次版本号
		int nUnicode;     //UNICODE码
		long Extend;      //扩展
	}FILE_HEAD, *PFILE_HEAD;

	FILE_HEAD m_Head;
	tstring m_szFile;

	std::map<tstring, PASSWORD_DATA> m_Passwords;

	CEncrypterManager * m_pEncrypterManager;

	int WriterFile(char * pBuf, const int nLen, std::ofstream * pOut);
	int ReadFile(char ** pBuf, std::ifstream * pIn);
};

#endif// __PASSWORD_MANAGER_H_KL_2008_01_13__
