// Cracker.h: interface for the CCracker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRACKER_H__BB9890C6_F7B8_48EE_8FB5_5AA25D05E6E1__INCLUDED_)
#define AFX_CRACKER_H__BB9890C6_F7B8_48EE_8FB5_5AA25D05E6E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GetPassword.h"

class CCracker  
{
public:
	CCracker();
	virtual ~CCracker();

	//����0��ʾ�õ�����,������ʾû�еõ�����
	typedef DWORD (*CRACKERFUN)(LPCTSTR pszPassword);
	enum STATUS{STOP, START, PAUSE, GETPASSWORD};

	//�õ�����
	CString GetPassword();
	int SetPassword(LPCTSTR pszPassword);
	
	//���õõ��ƽ���������ָ��
	int SetGetPassword(CGetPassword* pGetPassword);
	//�����̸߳���
	int SetThreadNumber(int nNum);

	//��ʼ�ƽ�
	int StartCrack();
	int StopCrack();
	int PauseCrack();
	
	//�õ�״̬
	int GetStatus();
	int SetStatus(int nStatus);	
	
	//�����ƽ⺯��ָ��
	int SetCrackFun(CRACKERFUN pFun);
	CRACKERFUN GetCrackFun();
	
private:
	int m_nStatus; //����״̬
	int m_nThread; //�ƽ��̸߳���
	CGetPassword* m_pPassword;//�õ�������ָ��
	CRACKERFUN m_pCracker;//�ƽ⺯��ָ��
	CString m_szPassword; //�õ�������
	
	HANDLE m_hMutex_Password;

	//�ƽ��߳�
	static DWORD pCrackerThread(void* pPara);

};

#endif // !defined(AFX_CRACKER_H__BB9890C6_F7B8_48EE_8FB5_5AA25D05E6E1__INCLUDED_)
