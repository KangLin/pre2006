// Cracker.cpp: implementation of the CCracker class.
//
//////////////////////////////////////////////////////////////////////

/*  ���ߣ�����
    ʱ�䣺2006-12-22
 *	�÷�:
		1������һ���ƽ����CCracker m_Cracker;
		2������һ���������ɶ���CGetPassword m_GetPassword;
		3�������������ɶ���m_Cracker.SetGetPassword(&m_GetPassword);
		4�������̸߳�������ѡ����m_Cracker.SetThreadNumber(50);
		5�������ƽ⺯����m_Cracker.SetCrackFun(pFun); 
		   �ƽ⺯������Ϊ CRACKERFUN �͵ĺ���
		6����ʼ�ƽ⣺m_Cracker.StartCrack();
		7��ֹͣ����ͣ�ƽ⣺m_Cracker.StopCrack(); 
						   m_Cracker.PauseCrack();
		8������ƽ��õ����룺m_Cracker.GetPassword();
		   ����õ���Ϊ_T("")����û�еõ����룬����Ϊ���롣
 */
#include "stdafx.h"
#include "GetPassword.h"
#include "Cracker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCracker::CCracker()
{
	m_nStatus = STOP;
	m_nThread = 50;
	m_pCracker = NULL;
	m_pPassword = NULL;
	
	m_hMutex_Password = CreateMutex(NULL, FALSE, NULL);
}

CCracker::~CCracker()
{
}

int CCracker::SetStatus(int nStatus)
{
	int old;
	old = m_nStatus;
	m_nStatus = nStatus;
	return old;
}

int CCracker::GetStatus()
{
	return m_nStatus;
}

int CCracker::StartCrack()
{
	if(m_nStatus != START)
	{
		m_nStatus = START;
		SetPassword(_T(""));

		int i;
		for(i = 0; i < m_nThread; i++)
		{
			//�����߳�
			::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)pCrackerThread, this, NULL, NULL);
		}
	}
	return 0;
}

int CCracker::StopCrack()
{
	m_nStatus = STOP;
	return 0;
}

int CCracker::PauseCrack()
{
	m_nStatus = PAUSE;
	return 0;
}

int CCracker::SetPassword(LPCTSTR pszPassword)
{
	int nRet;
	nRet = 0;
	ASSERT(pszPassword);
	if(WAIT_OBJECT_0 == WaitForSingleObject(m_hMutex_Password, INFINITE))
	{
		m_szPassword = pszPassword;
	}
	else
	{
		nRet = 1;
	}
	ReleaseMutex(m_hMutex_Password);
	return nRet;
}

CString CCracker::GetPassword()
{
	return m_szPassword;
}

int CCracker::SetGetPassword(CGetPassword* pGetPassword)
{
	m_pPassword = pGetPassword;
	return 0;
}

int CCracker::SetThreadNumber(int nNum)
{
	int old = m_nThread;
	m_nThread = nNum;
	return old;
}

int CCracker::SetCrackFun(CRACKERFUN pFun)
{
	ASSERT(pFun);
	m_pCracker = pFun;
	return !pFun;
}

CCracker::CRACKERFUN CCracker::GetCrackFun()
{
	return m_pCracker;
}

DWORD CCracker::pCrackerThread(void* pPara)
{
	ASSERT(pPara);

	CCracker* pThis = (CCracker*)pPara;
	CCracker::CRACKERFUN pCracker = pThis->GetCrackFun();

	int nRet = 0;
	while (1)
	{
		if(pThis->GetStatus() == CCracker::STOP 
			|| CCracker::GETPASSWORD == pThis->GetStatus())
		{
			return 1;
		}
		
		while(pThis->GetStatus() == CCracker::PAUSE)
		{
			;
		}

		CString szPassword = pThis->m_pPassword->GetPassword();
		if(szPassword != _T("") && pCracker != NULL)
		{
			if(0 == pCracker(szPassword))
			{
				//�������
				pThis->SetPassword(szPassword);
				pThis->SetStatus(CCracker::GETPASSWORD);
				return 0;			
			}
		}
		else
		{
			nRet = 2;
			break;
		}
	}
	
	pThis->SetStatus(CCracker::STOP);
	return nRet;
}
